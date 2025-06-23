
/**
 * @file servoanglemanager.h
 * @brief Management system for servo angle display labels
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef SERVOANGLEMANAGER_H
#define SERVOANGLEMANAGER_H

#include <QObject>
#include <QLabel>
#include <QMap>

/**
 * @brief Manager for servo angle display and GUI label updates
 *
 * ServoAngleManager provides a centralized system for managing the display
 * of servo angles in the GUI. It maintains mappings between logical servo
 * positions (leg/joint combinations) and their corresponding display labels,
 * enabling efficient updates when new angle data arrives.
 *
 * ## Servo Organization:
 * The hexapod robot has 18 servomotors organized as:
 * - **6 legs** (numbered 0-5, displayed as 1-6)
 * - **3 joints per leg**: Hip (0), Knee (1), Ankle (2)
 * - **Total**: 6 legs × 3 joints = 18 servomotors
 *
 * ## Mapping System:
 * Each servo is identified by a unique string key in the format "leg_joint":
 * - "0_0" = Leg 1, Hip joint
 * - "0_1" = Leg 1, Knee joint
 * - "0_2" = Leg 1, Ankle joint
 * - "5_2" = Leg 6, Ankle joint
 *
 * @see MainWindow::updateServoGUI()
 * @see ServoFrame
 *
 * Example usage:
 * @code
 * ServoAngleManager manager;
 *
 * // Register GUI labels
 * manager.registerLabel(0, 0, ui->servo_0_0_label);  // Leg 1, Hip
 * manager.registerLabel(0, 1, ui->servo_0_1_label);  // Leg 1, Knee
 *
 * // Update angles
 * manager.setAngle(0, 0, 45.5);  // Set Leg 1 Hip to 45.5°
 * @endcode
 */
class ServoAngleManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Parent QObject for memory management
     */
    explicit ServoAngleManager(QObject *parent = nullptr);

    /**
     * @brief Register a GUI label for servo angle display
     *
     * Associates a QLabel widget with a specific servo position. The label
     * will be automatically updated when setAngle() is called for this
     * servo position.
     *
     * @param leg Leg number (0-5, corresponding to legs 1-6 in GUI)
     * @param joint Joint number (0=Hip, 1=Knee, 2=Ankle)
     * @param label Pointer to QLabel widget that will display the angle
     *
     * @note Label must remain valid for the lifetime of the manager
     * @note Registering the same leg/joint combination overwrites previous registration
     *
     * @see setAngle()
     */
    void registerLabel(int leg, int joint, QLabel *label);

    /**
     * @brief Update servo angle and refresh GUI display
     *
     * Sets the angle for a specific servo and immediately updates the
     * associated GUI label. The angle is displayed with one decimal place
     * precision followed by the degree symbol (°).
     *
     * @param leg Leg number (0-5)
     * @param joint Joint number (0-2)
     * @param angle Servo angle in degrees
     *
     * @note If no label is registered for this leg/joint, the call is ignored
     * @note Angle values are displayed as-is without range validation
     *
     * Display format: "45.5°", "-12.3°", "0.0°"
     *
     * @see registerLabel()
     */
    void setAngle(int leg, int joint, float angle);

private:
    QMap<QString, QLabel*> servoLabels;  /**< Mapping from "leg_joint" strings to QLabel pointers */
};
#endif
