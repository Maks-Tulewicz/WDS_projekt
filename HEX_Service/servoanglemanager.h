/**
 * @file servoanglemanager.h
 * @brief System zarządzania etykietami wyświetlania kątów serwomechanizmów
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
 * @brief Manager do wyświetlania kątów serwomechanizmów i aktualizacji etykiet GUI
 *
 * ServoAngleManager zapewnia scentralizowany system do zarządzania wyświetlaniem
 * kątów serwomechanizmów w GUI. Utrzymuje mapowania między logicznymi pozycjami
 * serwomechanizmów (kombinacje noga/staw) a odpowiadającymi im etykietami wyświetlania,
 * umożliwiając efektywne aktualizacje gdy przychodzą nowe dane kątów.
 *
 * ## Organizacja serwomechanizmów:
 * Robot hexapod ma 18 serwomotorów zorganizowanych jako:
 * - **6 nóg** (numerowane 0-5, wyświetlane jako 1-6)
 * - **3 stawy na nogę**: Biodro (0), Kolano (1), Kostka (2)
 * - **Łącznie**: 6 nóg × 3 stawy = 18 serwomotorów
 *
 * ## System mapowania:
 * Każdy serwomechanizm jest identyfikowany przez unikalny klucz łańcuchowy w formacie "noga_staw":
 * - "0_0" = Noga 1, staw Biodra
 * - "0_1" = Noga 1, staw Kolana
 * - "0_2" = Noga 1, staw Kostki
 * - "5_2" = Noga 6, staw Kostki
 *
 * @see MainWindow::updateServoGUI()
 * @see ServoFrame
 *
 * Przykład użycia:
 * @code
 * ServoAngleManager manager;
 *
 * // Zarejestruj etykiety GUI
 * manager.registerLabel(0, 0, ui->servo_0_0_label);  // Noga 1, Biodro
 * manager.registerLabel(0, 1, ui->servo_0_1_label);  // Noga 1, Kolano
 *
 * // Aktualizuj kąty
 * manager.setAngle(0, 0, 45.5);  // Ustaw Biodro Nogi 1 na 45.5°
 * @endcode
 */
class ServoAngleManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Rodzic QObject do zarządzania pamięcią
     */
    explicit ServoAngleManager(QObject *parent = nullptr);

    /**
     * @brief Zarejestruj etykietę GUI dla wyświetlania kąta serwomechanizmu
     *
     * Kojarzy widget QLabel z określoną pozycją serwomechanizmu. Etykieta
     * będzie automatycznie aktualizowana gdy setAngle() jest wywoływana dla tej
     * pozycji serwomechanizmu.
     *
     * @param leg Numer nogi (0-5, odpowiadający nogom 1-6 w GUI)
     * @param joint Numer stawu (0=Biodro, 1=Kolano, 2=Kostka)
     * @param label Wskaźnik do widgetu QLabel który będzie wyświetlał kąt
     *
     * @note Etykieta musi pozostać ważna przez czas życia managera
     * @note Rejestracja tej samej kombinacji noga/staw nadpisuje poprzednią rejestrację
     *
     * @see setAngle()
     */
    void registerLabel(int leg, int joint, QLabel *label);

    /**
     * @brief Aktualizuj kąt serwomechanizmu i odśwież wyświetlacz GUI
     *
     * Ustawia kąt dla określonego serwomechanizmu i natychmiast aktualizuje
     * skojarzoną etykietę GUI. Kąt jest wyświetlany z dokładnością do jednego miejsca po przecinku
     * z symbolem stopnia (°).
     *
     * @param leg Numer nogi (0-5)
     * @param joint Numer stawu (0-2)
     * @param angle Kąt serwomechanizmu w stopniach
     *
     * @note Jeśli nie zarejestrowano etykiety dla tej kombinacji noga/staw, wywołanie jest ignorowane
     * @note Wartości kątów są wyświetlane jak są bez walidacji zakresu
     *
     * Format wyświetlania: "45.5°", "-12.3°", "0.0°"
     *
     * @see registerLabel()
     */
    void setAngle(int leg, int joint, float angle);

private:
    QMap<QString, QLabel*> servoLabels;  /**< Mapowanie łańcuchów "noga_staw" do wskaźników QLabel */
};

#endif // SERVOANGLEMANAGER_H
