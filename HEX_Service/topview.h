
/**
 * @file topview.h
 * @brief Top-down view visualization of complete hexapod robot
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef TOPVIEW_H
#define TOPVIEW_H

#include <QWidget>

/**
 * @brief Top-down visualization widget showing complete hexapod robot posture
 *
 * TopView provides a bird's-eye view of the hexapod robot, displaying the
 * orientation of all six legs simultaneously. This visualization is essential
 * for understanding overall robot posture, gait patterns, and coordination
 * between legs during movement.
 *
 * ## Visualization Features:
 * - **Complete robot overview** with all 6 legs visible
 * - **Proportional body representation** as central circular body
 * - **Individual hip angle display** for each leg
 * - **Realistic leg positioning** based on actual hexapod geometry
 * - **Real-time updates** synchronized with servo feedback
 * - **High-quality rendering** with antialiasing and smooth lines
 *
 * ## Robot Geometry:
 * The hexapod uses a standard 6-leg configuration:
 * ```
 *     Front
 *   1 ----- 2
 *  /         \
 * 3           4
 *  \         /
 *   5 ----- 6
 *     Rear
 * ```
 *
 * ## Hip Angle Conventions:
 * - **Base orientations**: Each leg has a predefined base direction
 * - **Servo angles**: 0° to 180° typical servo range
 * - **Display angles**: Servo angle - 90° to center around base direction
 * - **Rotation**: Positive angles rotate clockwise from base position
 *
 * ## Base Orientations (in degrees):
 * - Leg 0 (Front-Left): 225° (SW)
 * - Leg 1 (Mid-Left): 270° (W)
 * - Leg 2 (Rear-Left): 315° (NW)
 * - Leg 3 (Rear-Right): 45° (NE)
 * - Leg 4 (Mid-Right): 90° (E)
 * - Leg 5 (Front-Right): 135° (SE)
 *
 * @see SideView
 * @see MainWindow::updateServoGUI()
 *
 * Example usage:
 * @code
 * TopView *topView = new TopView(parent);
 *
 * // Set hip angles for walking gait
 * for (int leg = 0; leg < 6; ++leg) {
 *     float angle = calculateWalkingAngle(leg, time);
 *     topView->setHipAngle(leg, angle);
 * }
 * @endcode
 */
class TopView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor - Initialize top view widget
     *
     * Creates the top view widget with all legs initialized to their
     * base orientations (90° servo position). Sets up the coordinate
     * system and rendering parameters.
     *
     * @param parent Parent widget for memory management
     */
    explicit TopView(QWidget *parent = nullptr);

    /**
     * @brief Set hip angle for individual leg
     *
     * Updates the hip angle for a specific leg and triggers a visual update.
     * The angle is interpreted as a servo position (0-180°) and converted
     * to the appropriate display orientation.
     *
     * @param legIndex Leg number (0-5)
     * @param angleDeg Hip servo angle in degrees (typical range: 0-180°)
     *
     * @note Invalid leg indices are ignored silently
     * @note Angle values outside 0-180° are accepted but may look unusual
     * @note Widget automatically repaints when angles change
     *
     * Angle interpretation:
     * - 0° = Maximum counter-clockwise rotation
     * - 90° = Neutral position (aligned with base orientation)
     * - 180° = Maximum clockwise rotation
     */
    void setHipAngle(int legIndex, float angleDeg);

protected:
    /**
     * @brief Render the complete robot visualization
     *
     * Custom paint implementation that draws the robot body and all six
     * legs with their current hip orientations. Uses adaptive sizing
     * based on widget dimensions.
     *
     * @param e Paint event (unused)
     *
     * @note Called automatically by Qt when widget needs repainting
     * @note Rendering scales automatically with widget size
     * @note Uses high-quality antialiased drawing for smooth appearance
     */
    void paintEvent(QPaintEvent *e) override;

private:
    float hipAngles[6];                                           /**< Current hip angles for all 6 legs */
    static constexpr float kBase[6] = {225, 270, 315, 45, 90, 135}; /**< Base orientations for each leg in degrees */
};

#endif // Multiple header files
