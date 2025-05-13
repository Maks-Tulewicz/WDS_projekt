#ifndef TOPVIEW_H
#define TOPVIEW_H

#include <QWidget>

/**
 * @brief Rzut z góry – wizualizacja ustawienia bioder wszystkich nóg.
 *
 * Każda z sześciu linii wychodzi z okręgu–ciała i odchyla się
 * o wartość kata serwa. 0° = linia w kierunku „prosto” dla danej nogi,
 * dodatnie kąty obracają w prawo (CW), ujemne w lewo (CCW).
 */
class TopView : public QWidget
{
    Q_OBJECT
public:
    explicit TopView(QWidget *parent = nullptr);

    /// Ustawia kąt biodra wybranej nogi (0-5) w zakresie 0–180 deg.
    void setHipAngle(int legIndex, float angleDeg);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    float hipAngles[6];               ///< aktualne kąty bioder
    static constexpr float kBase[6] = {225, 270, 315,  45,  90, 135};  ///< bazowe orientacje nóg
};

#endif // TOPVIEW_H
