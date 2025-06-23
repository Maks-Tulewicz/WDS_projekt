
/**
 * @file sideview.h
 * @brief Side view visualization of individual hexapod leg
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef SIDEVIEW_H
#define SIDEVIEW_H

#include <QWidget>
#include <QPainter>

/**
 * @brief Side view visualization widget for detailed leg examination
 *
 * SideView provides a detailed 2D visualization of a single hexapod leg
 * from the side perspective. It shows the leg's kinematic chain with
 * accurate joint positions and orientations based on servo angles.
 *
 * ## Visualization Features:
 * - **Anatomically correct proportions** with realistic segment lengths
 * - **Real-time joint animation** based on servo feedback
 * - **Color-coded joints** for easy identification (red=knee, blue=ankle)
 * - **Fixed body reference** showing leg attachment point
 * - **Smooth rendering** with antialiasing for professional appearance
 *
 * ## Kinematic Model:
 * The leg model uses a simplified 2-DOF (Degree of Freedom) representation:
 * - **Thigh segment**: From hip to knee (80 pixels length)
 * - **Shin segment**: From knee to ankle (160 pixels length, 2:1 ratio)
 * - **Hip joint**: Fixed attachment point (not visualized)
 * - **Knee joint**: Primary articulation point (red indicator)
 * - **Ankle joint**: End effector orientation (blue indicator)
 *
 * ## Coordinate System:
 * - **Origin**: Hip attachment point (center-left of widget)
 * - **Zero degrees**: Pointing upward (12 o'clock position)
 * - **Positive rotation**: Clockwise from zero position
 * - **Angle interpretation**: 90° = horizontal, 180° = downward
 *
 * @see TopView
 * @see MainWindow::onLegSelectionChanged()
 *
 * Example usage:
 * @code
 * SideView *sideView = new SideView(parent);
 * sideView->setActiveLeg(2);           // Select leg 3 for display
 * sideView->setJointAngles(45, 120);   // Set knee=45°, ankle=120°
 * @endcode
 */
class SideView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor - Initialize side view widget
     *
     * Creates the side view widget with default settings and initial
     * pose. Sets up fixed widget size optimized for leg visualization.
     *
     * @param parent Parent widget for memory management
     */
    explicit SideView(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Select which leg to display
     *
     * Changes the active leg being visualized. This allows the user to
     * examine each of the 6 legs individually for detailed analysis.
     *
     * @param leg Leg index (0-5, corresponding to legs 1-6)
     *
     * @note Leg selection affects only the display label, not the visualization
     * @note Joint angles remain unchanged when switching legs
     * @note Invalid leg numbers are ignored silently
     */
    void setActiveLeg(int leg);

    /**
     * @brief Update joint angles for real-time visualization
     *
     * Sets the knee and ankle joint angles for the currently active leg.
     * The visualization is immediately updated to reflect the new pose.
     * Joint angles are interpreted according to the robot's conventions.
     *
     * @param knee Knee joint angle in degrees (0° = straight up, 90° = horizontal)
     * @param ankle Ankle joint angle in degrees (relative to shin segment)
     *
     * @note Angles are not range-limited; extreme values may produce unusual poses
     * @note Widget automatically repaints when angles change
     *
     * Example typical ranges:
     * - Knee: 30° to 120° (bent to extended)
     * - Ankle: 90° to 270° (forward to backward)
     */
    void setJointAngles(float knee, float ankle);

protected:
    /**
     * @brief Render the leg visualization
     *
     * Custom paint implementation that draws the complete leg structure
     * including body attachment, thigh, shin, and joint indicators.
     * Uses high-quality rendering with antialiasing.
     *
     * @param event Paint event (unused)
     *
     * @note Called automatically by Qt when widget needs repainting
     * @note Drawing is optimized for smooth real-time updates
     */
    void paintEvent(QPaintEvent *event) override;

private:
    int activeLeg = 0;         /**< Currently selected leg index (0-5) */
    float kneeAngle = 0.f;     /**< Current knee joint angle in degrees */
    float ankleAngle = 0.f;    /**< Current ankle joint angle in degrees */
};

#endif
