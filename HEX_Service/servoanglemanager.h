#ifndef SERVOANGLEMANAGER_H
#define SERVOANGLEMANAGER_H

#include <QObject>
#include <QLabel>
#include <QMap>

/**
 * @brief Klasa do zarządzania kątami serwomechanizmów.
 *
 * Klasa odpowiada za przypisanie odpowiednich widżetów do serwomechanizmów i aktualizowanie ich kątów w GUI.
 */
class ServoAngleManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy ServoAngleManager.
     * @param parent Wskaźnik do obiektu rodzica (może być nullptr).
     */
    explicit ServoAngleManager(QObject *parent = nullptr);

    /**
     * @brief Podpina widżet z GUI do danego serwa.
     * @param leg Numer nogi (0-5).
     * @param joint Numer stawu (0-2).
     * @param label Wskaźnik na QLabel, który będzie wyświetlał kąt.
     */
    void registerLabel(int leg, int joint, QLabel *label);

    /**
     * @brief Ustawia kąt dla danego serwa i aktualizuje GUI.
     * @param leg Numer nogi (0-5).
     * @param joint Numer stawu (0-2).
     * @param angle Kąt serwa w stopniach.
     */
    void setAngle(int leg, int joint, float angle);

private:
    QMap<QString, QLabel*> servoLabels; ///< Mapa przechowująca przypisania (leg_joint -> QLabel)
};

#endif // SERVOANGLEMANAGER_H
