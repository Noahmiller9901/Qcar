#!/usr/bin/env python3
"""
v2x_controller.py
─────────────────
Central coordinator node.
- Monitors all V2X topics
- Logs every message in a human-readable table
- Detects conflicts (two vehicles requesting same intersection)
- Publishes a system health heartbeat
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import json
from datetime import datetime


class V2XController(Node):

    def __init__(self):
        super().__init__("v2x_controller")

        # ── Subscribers — listen to every V2X topic ─────────
        self.create_subscription(String, "/v2x/priority_request", self.on_request, 10)
        self.create_subscription(String, "/v2x/signal_status",    self.on_status,  10)
        self.create_subscription(String, "/v2x/priority_grant",   self.on_grant,   10)

        # ── Publisher — system heartbeat ────────────────────
        self.health_pub = self.create_publisher(String, "/v2x/health", 10)
        self.create_timer(5.0, self.publish_health)

        # ── State tracking ───────────────────────────────────
        # intersection_id -> vehicle_id currently holding priority
        self.active_grants: dict[str, str] = {}

        # Stats
        self.total_requests = 0
        self.total_grants   = 0
        self.total_denials  = 0

        self.get_logger().info("=" * 55)
        self.get_logger().info("  V2X Controller started — monitoring all topics")
        self.get_logger().info("=" * 55)

    # ─────────────────────────────────────────────────────────
    def _ts(self) -> str:
        return datetime.now().strftime("%H:%M:%S")

    # ─────────────────────────────────────────────────────────
    def on_request(self, msg: String):
        data = json.loads(msg.data)
        self.total_requests += 1

        urgency_label = {0: "NORMAL", 1: "ELEVATED", 2: "CRITICAL"}.get(
            data["urgency_level"], "UNKNOWN"
        )

        self.get_logger().info(
            f"[{self._ts()}] REQUEST  | "
            f"vehicle={data['vehicle_id']} | "
            f"intersection={data['intersection_id']} | "
            f"urgency={urgency_label} | "
            f"dist={data['distance_to_intersection']:.1f} m | "
            f"ETA={data['estimated_arrival_time']:.1f} s"
        )

        # Conflict detection
        current_holder = self.active_grants.get(data["intersection_id"])
        if current_holder and current_holder != data["vehicle_id"]:
            self.get_logger().warn(
                f"[{self._ts()}] ⚠️  CONFLICT — {data['intersection_id']} already "
                f"held by {current_holder}, new request from {data['vehicle_id']}"
            )

    # ─────────────────────────────────────────────────────────
    def on_status(self, msg: String):
        data = json.loads(msg.data)

        phase_icon = {"GREEN": "🟢", "YELLOW": "🟡", "RED": "🔴"}.get(
            data["current_phase"], "⚪"
        )
        self.get_logger().debug(
            f"[{self._ts()}] STATUS   | "
            f"{data['intersection_id']} {phase_icon} {data['current_phase']} "
            f"| {data['time_remaining']:.1f} s remaining"
        )

    # ─────────────────────────────────────────────────────────
    def on_grant(self, msg: String):
        data = json.loads(msg.data)

        if data["granted"]:
            self.total_grants += 1
            self.active_grants[data["intersection_id"]] = data["vehicle_id"]
            self.get_logger().info(
                f"[{self._ts()}] ✅ GRANT  | "
                f"vehicle={data['vehicle_id']} | "
                f"intersection={data['intersection_id']} | "
                f"green={data['green_duration']:.1f} s | "
                f"reason: {data['reason']}"
            )
        else:
            self.total_denials += 1
            self.get_logger().info(
                f"[{self._ts()}] ❌ DENY   | "
                f"vehicle={data['vehicle_id']} | "
                f"intersection={data['intersection_id']} | "
                f"reason: {data['reason']}"
            )

    # ─────────────────────────────────────────────────────────
    def publish_health(self):
        payload = {
            "timestamp":        self._ts(),
            "total_requests":   self.total_requests,
            "total_grants":     self.total_grants,
            "total_denials":    self.total_denials,
            "active_grants":    self.active_grants,
        }
        msg = String()
        msg.data = json.dumps(payload)
        self.health_pub.publish(msg)

        self.get_logger().info(
            f"[{self._ts()}] HEALTH   | "
            f"requests={self.total_requests} | "
            f"grants={self.total_grants} | "
            f"denials={self.total_denials} | "
            f"active={self.active_grants}"
        )


# ─────────────────────────────────────────────────────────────
def main(args=None):
    rclpy.init(args=args)
    node = V2XController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
