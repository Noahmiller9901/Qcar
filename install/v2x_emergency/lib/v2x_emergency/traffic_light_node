#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import json

# ─── Constants ───────────────────────────────────────────────
DEFAULT_GREEN_DURATION  = 10.0   # seconds
DEFAULT_YELLOW_DURATION =  3.0   # seconds (always respected)
DEFAULT_RED_DURATION    = 10.0   # seconds
MAX_GREEN_EXTENSION     = 30.0   # seconds — safety cap
CRITICAL_GREEN_DURATION = 20.0   # seconds for urgency level 2
ELEVATED_EXTENSION      = 10.0   # seconds added for urgency level 1


class TrafficLightNode(Node):

    def __init__(self, intersection_id: str = "intersection_1"):
        super().__init__(f"traffic_light_{intersection_id.split('_')[-1]}")

        self.intersection_id = intersection_id

        # ── Publishers ──────────────────────────────────────
        self.signal_pub = self.create_publisher(
            String, "/v2x/signal_status", 10
        )
        self.grant_pub = self.create_publisher(
            String, "/v2x/priority_grant", 10
        )

        # ── Subscribers ─────────────────────────────────────
        self.request_sub = self.create_subscription(
            String, "/v2x/priority_request", self.request_callback, 10
        )

        # ── Signal state ─────────────────────────────────────
        self.current_phase = "RED"          # RED | YELLOW | GREEN
        self.time_remaining = DEFAULT_RED_DURATION
        self.active_vehicle = None          # only one priority at a time

        # ── Timers ───────────────────────────────────────────
        self.phase_timer  = self.create_timer(1.0, self.tick_phase)   # every 1 s
        self.status_timer = self.create_timer(1.0, self.publish_status)

        self.get_logger().info(
            f"[TrafficLight] {self.intersection_id} started | phase={self.current_phase}"
        )

    # ─────────────────────────────────────────────────────────
    # Phase ticker — counts down and transitions phases
    # ─────────────────────────────────────────────────────────
    def tick_phase(self):
        self.time_remaining -= 1.0

        if self.time_remaining <= 0:
            self.transition_phase()

    def transition_phase(self):
        if self.current_phase == "GREEN":
            self.current_phase   = "YELLOW"
            self.time_remaining  = DEFAULT_YELLOW_DURATION
            self.active_vehicle  = None     # clear after green ends
        elif self.current_phase == "YELLOW":
            self.current_phase  = "RED"
            self.time_remaining = DEFAULT_RED_DURATION
        elif self.current_phase == "RED":
            self.current_phase  = "GREEN"
            self.time_remaining = DEFAULT_GREEN_DURATION

        self.get_logger().info(
            f"[TrafficLight] {self.intersection_id} → {self.current_phase} "
            f"({self.time_remaining:.0f} s)"
        )

    # ─────────────────────────────────────────────────────────
    # Publish current signal status
    # ─────────────────────────────────────────────────────────
    def publish_status(self):
        payload = {
            "intersection_id": self.intersection_id,
            "current_phase":   self.current_phase,
            "time_remaining":  round(self.time_remaining, 1),
        }
        msg = String()
        msg.data = json.dumps(payload)
        self.signal_pub.publish(msg)

    # ─────────────────────────────────────────────────────────
    # Handle incoming priority requests
    # ─────────────────────────────────────────────────────────
    def request_callback(self, msg: String):
        try:
            data = json.loads(msg.data)
        except json.JSONDecodeError:
            self.get_logger().warn(f"[TrafficLight] Ignored malformed request: {msg.data!r}")
            return

        # Only handle requests for this intersection
        if data.get("intersection_id") != self.intersection_id:
            return

        vehicle_id    = data["vehicle_id"]
        urgency_level = data["urgency_level"]

        self.get_logger().info(
            f"[TrafficLight] Request from {vehicle_id} "
            f"| urgency={urgency_level} | phase={self.current_phase}"
        )

        # ── Already serving another vehicle ─────────────────
        if self.active_vehicle and self.active_vehicle != vehicle_id:
            self.send_grant(
                vehicle_id,
                granted=False,
                reason="intersection busy with another vehicle",
                green_duration=0.0,
            )
            return

        # ── Decision logic ───────────────────────────────────
        if urgency_level == 2:
            self.handle_critical(vehicle_id)

        elif urgency_level == 1:
            self.handle_elevated(vehicle_id)

        else:
            # Level 0 — no priority
            self.send_grant(
                vehicle_id,
                granted=False,
                reason="no priority needed for urgency level 0",
                green_duration=0.0,
            )

    # ─────────────────────────────────────────────────────────
    # Urgency level 2 — force GREEN immediately
    # ─────────────────────────────────────────────────────────
    def handle_critical(self, vehicle_id: str):
        if self.current_phase == "YELLOW":
            # Respect minimum yellow — schedule green right after
            self.get_logger().warn(
                "[TrafficLight] YELLOW in progress — will switch to GREEN after yellow"
            )
            # Shorten remaining yellow to finish quickly, then force green
            self.time_remaining = min(self.time_remaining, DEFAULT_YELLOW_DURATION)
            # Override next phase
            self._pending_critical = vehicle_id
            self.create_timer(self.time_remaining + 0.5, lambda: self._apply_critical(vehicle_id))
        else:
            self._apply_critical(vehicle_id)

    def _apply_critical(self, vehicle_id: str):
        self.current_phase  = "GREEN"
        self.time_remaining = CRITICAL_GREEN_DURATION
        self.active_vehicle = vehicle_id

        self.get_logger().info(
            f"[TrafficLight] 🚨 CRITICAL — forced GREEN for {CRITICAL_GREEN_DURATION:.0f} s"
        )
        self.send_grant(
            vehicle_id,
            granted=True,
            reason="urgency level 2 — green forced immediately",
            green_duration=CRITICAL_GREEN_DURATION,
        )

    # ─────────────────────────────────────────────────────────
    # Urgency level 1 — extend or schedule early green
    # ─────────────────────────────────────────────────────────
    def handle_elevated(self, vehicle_id: str):
        if self.current_phase == "GREEN":
            extension = min(
                self.time_remaining + ELEVATED_EXTENSION, MAX_GREEN_EXTENSION
            ) - self.time_remaining
            self.time_remaining += extension
            self.active_vehicle  = vehicle_id

            self.get_logger().info(
                f"[TrafficLight] 🟡 ELEVATED — extended GREEN by {extension:.0f} s"
            )
            self.send_grant(
                vehicle_id,
                granted=True,
                reason=f"urgency level 1 — green extended by {extension:.0f} s",
                green_duration=self.time_remaining,
            )

        elif self.current_phase in ("RED", "YELLOW"):
            # Schedule an early green
            self.get_logger().info(
                "[TrafficLight] 🟡 ELEVATED — scheduling early GREEN after current phase"
            )
            self.active_vehicle = vehicle_id
            # Shorten remaining red/yellow
            self.time_remaining = min(self.time_remaining, 5.0)
            self.send_grant(
                vehicle_id,
                granted=True,
                reason="urgency level 1 — early green scheduled",
                green_duration=DEFAULT_GREEN_DURATION + ELEVATED_EXTENSION,
            )

    # ─────────────────────────────────────────────────────────
    # Publish a grant message
    # ─────────────────────────────────────────────────────────
    def send_grant(
        self,
        vehicle_id: str,
        granted: bool,
        reason: str,
        green_duration: float,
    ):
        payload = {
            "intersection_id": self.intersection_id,
            "vehicle_id":      vehicle_id,
            "granted":         granted,
            "reason":          reason,
            "green_duration":  green_duration,
        }
        msg = String()
        msg.data = json.dumps(payload)
        self.grant_pub.publish(msg)

        status = "✅ GRANTED" if granted else "❌ DENIED"
        self.get_logger().info(
            f"[TrafficLight] {status} → {vehicle_id} | {reason}"
        )


# ─────────────────────────────────────────────────────────────
def main(args=None):
    import sys
    rclpy.init(args=args)

    # Pass intersection ID as first CLI argument, default intersection_1
    intersection_id = sys.argv[1] if len(sys.argv) > 1 else "intersection_1"
    node = TrafficLightNode(intersection_id=intersection_id)

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
