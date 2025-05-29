#ifndef SIDEVIEW_H
#define SIDEVIEW_H

#include <QWidget>
#include <QPainter>  // Będzie używane do rysowania na widgetcie

/**
 * @brief Klasa do wyświetlania jednej nogi robota w widoku z boku.
 *
 * Klasa ta rysuje jedną nogę robota, animując ruchy w obrębie kolana i kostki.
 * Umożliwia zmianę aktywnej nogi oraz animowanie jej w zależności od kątów stawów.
 */
class SideView : public QWidget
{
    Q_OBJECT           // <-- musi być!

public:
    explicit SideView(QWidget *parent = nullptr);

public slots:          // <-- PRZENIEŚ TU!
    /**
 * @brief Wybiera, którą nogę rysować.
 * @param leg  Numer nogi (0–5).
 */
    void setActiveLeg(int leg);
public:
    /**
 * @brief Ustawia kąty kolana i kostki dla aktywnej nogi.
 * @param knee   Kąt kolana [°].
 * @param ankle  Kąt kostki [°].
 */
    void setJointAngles(float knee, float ankle);


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int   activeLeg  = 0;
    float kneeAngle  = 0.f;
    float ankleAngle = 0.f;
};

#endif // SIDEVIEW_H
