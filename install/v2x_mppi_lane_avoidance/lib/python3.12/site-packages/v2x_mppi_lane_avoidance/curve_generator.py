#!/usr/bin/env python3
"""
V2X Emergency Vehicle Project - Polynomial Curve Generation Layer
Author: Prathamesh Sathe

Purpose:
    - Receives raw, discrete path coordinates from Nav2 Hybrid A* or OpenCV.
    - Fits a smooth, continuous polynomial model (e.g., y = Ax^2 + Bx + C).
    - Outputs raw coefficients [A, B, C] directly into the MPPI cost function layer.
"""

import numpy as np

def fit_trajectory_polynomial(waypoints_x: list | np.ndarray, waypoints_y: list | np.ndarray, order: int = 2) -> np.ndarray:
    """
    Fits a mathematical polynomial curve of a specified order to discrete geometric points.
    
    Args:
        waypoints_x: X-coordinates of the path (independent variable).
        waypoints_y: Y-coordinates of the path (dependent variable).
        order: Polynomial degree (default=2 for quadratic curves, use 3 for cubic lanes).
        
    Returns:
        np.ndarray: Coefficients array [A, B, C...] where y = Ax^2 + Bx + C.
    """
    x_data = np.asarray(waypoints_x, dtype=float)
    y_data = np.asarray(waypoints_y, dtype=float)
    
    # Handle edge case: if there aren't enough data points to fit the requested order
    if len(x_data) <= order:
        # Fallback to a flat line [0, 0, 0] if data stream is corrupted or empty
        return np.zeros(order + 1)
        
    # np.polyfit calculates the least-squares fit optimization automatically
    coefficients = np.polyfit(x_data, y_data, order)
    return coefficients

def evaluate_polynomial(x_grid: np.ndarray, coefficients: np.ndarray) -> np.ndarray:
    """
    Evaluates a set of polynomial coefficients over an array of X positions.
    Useful for reconstructing paths and debugging tracking profiles.
    """
    return np.polyval(coefficients, x_grid)


# --- STANDALONE LAPTOP TEST RUNNER ---
if __name__ == "__main__":
    print("Initializing standalone validation check for curve_generator.py...")
    
    # 1. Simulate jagged, discrete path outputs mimicking a Nav2 detour route
    # Starting at y=0, swerving around an obstacle at x=15, returning to y=0
    mock_nav2_x = np.array([0.0, 4.0, 8.0, 12.0, 15.0, 18.0, 22.0, 26.0, 30.0])
    mock_nav2_y = np.array([0.0, 0.0, 0.1,  0.8,  1.2,  0.8,  0.1,  0.0,  0.0])
    
    # 2. Run the fitting engine (2nd-order / quadratic match)
    poly_coeffs = fit_trajectory_polynomial(mock_nav2_x, mock_nav2_y, order=2)
    print(f"\nOptimization Successful!")
    print(f"Generated Polynomial Formula: y = ({poly_coeffs[0]:.4f})x^2 + ({poly_coeffs[1]:.4f})x + ({poly_coeffs[2]:.4f})")
    
    # 3. Reconstruct a fine-resolution continuous path for visualization
    dense_x = np.linspace(0.0, 30.0, 100)
    smooth_y = evaluate_polynomial(dense_x, poly_coeffs)
    
    # 4. Save validation check plot to disk
    import matplotlib.pyplot as plt
    plt.figure(figsize=(10, 4))
    plt.scatter(mock_nav2_x, mock_nav2_y, color='red', zorder=5, label="Raw Waypoints (Nav2 / OpenCV)")
    plt.plot(dense_x, smooth_y, color='blue', linewidth=2, label="Fitted Analytical Polynomial Curve")
    plt.axhline(0, color='black', linestyle=':', alpha=0.3)
    plt.title("Middle-Layer Profile: Fitting Continuous Polynomial to Discrete Waypoints")
    plt.xlabel("X Position [meters]")
    plt.ylabel("Y Lateral Deviation [meters]")
    plt.legend()
    plt.grid(True, linestyle=':')
    plt.tight_layout()
    plt.savefig("curve_generator_test_profile.png", dpi=150)
    print("Validation chart saved successfully as 'curve_generator_test_profile.png'.")
    plt.show()