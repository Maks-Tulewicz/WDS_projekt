#ifndef SIDEVIEW_H
#define SIDEVIEW_H

#include <QWidget>
#include <QPainter>

/**
 * @brief Klasa do wyświetlania jednej nogi robota w widoku z boku.
 *
 * Klasa ta rysuje jedną nogę robota, animując ruchy w obrębie kolana i kostki.
 * Umożliwia zmianę aktywnej nogi oraz animowanie jej w zależności od kątów stawów.
 */
class SideView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor widoku bocznego
     * @param parent Wskaźnik na widget rodzica
     */
    explicit SideView(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Wybiera, którą nogę rysować
     * @param leg Numer nogi (0-5)
     */
    void setActiveLeg(int leg);

    /**
     * @brief Ustawia kąty kolana i kostki dla aktywnej nogi
     * @param knee Kąt kolana [°]
     * @param ankle Kąt kostki [°]
     */
    void setJointAngles(float knee, float ankle);

protected:
    /**
     * @brief Obsługuje zdarzenie rysowania widgetu
     * @param event Obiekt zdarzenia
     */
    void paintEvent(QPaintEvent *event) override;

private:
    int activeLeg = 0;      ///< Indeks aktualnie wyświetlanej nogi (0-5)
    float kneeAngle = 0.f;  ///< Aktualny kąt kolana w stopniach
    float ankleAngle = 0.f; ///< Aktualny kąt kostki w stopniach
};

#endif // SIDEVIEW_H
