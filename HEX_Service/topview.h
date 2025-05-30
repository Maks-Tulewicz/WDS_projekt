#ifndef TOPVIEW_H
#define TOPVIEW_H

#include <QWidget>

/**
 * @brief Rzut z góry – wizualizacja ustawienia bioder wszystkich nóg.
 *
 * Każda z sześciu linii wychodzi z okręgu–ciała i odchyla się
 * o wartość kąta serwa. 0° = linia w kierunku "prosto" dla danej nogi,
 * dodatnie kąty obracają w prawo (CW), ujemne w lewo (CCW).
 */
class TopView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor widoku z góry
     * @param parent Wskaźnik na widget rodzica
     */
    explicit TopView(QWidget *parent = nullptr);

    /**
     * @brief Ustawia kąt biodra dla danej nogi
     * @param legIndex Indeks nogi (0-5)
     * @param angleDeg Kąt w stopniach
     */
    void setHipAngle(int legIndex, float angleDeg);

protected:
    /**
     * @brief Obsługuje zdarzenie rysowania widgetu
     * @param e Obiekt zdarzenia
     */
    void paintEvent(QPaintEvent *e) override;

private:
    float hipAngles[6];              ///< Aktualne kąty bioder
    static constexpr float kBase[6] = {225, 270, 315, 45, 90, 135}; ///< Bazowe orientacje nóg
};

#endif // TOPVIEW_H
