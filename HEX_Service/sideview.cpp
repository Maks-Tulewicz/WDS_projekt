#include "sideview.h"
#include <QPainter>
#include <QtMath>

SideView::SideView(QWidget *parent)
    : QWidget(parent),
    activeLeg(0),
    kneeAngle(60),
    ankleAngle(160)
{
    setFixedSize(400, 400);  // Stały rozmiar widgetu (do testów)
}

void SideView::setActiveLeg(int leg)
{
    if (leg >= 0 && leg < 6) {
        activeLeg = leg;
        update();  // Odświeżenie widoku
    }
}

void SideView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Centrum biodra (początek nogi)
    int centerX = width() / 2 - 100;
    int centerY = height() / 2;

    // Parametry długości kończyn (proporcja 2:1)
    int thighLength = 80;
    int legLength = 160;

    // Korekta kąta kolana (0° = góra, 180° = dół)
    float kneeRadians = qDegreesToRadians(90 - kneeAngle);

    // Pozycja kolana względem biodra
    int kneeX = centerX + thighLength * qCos(kneeRadians);
    int kneeY = centerY - thighLength * qSin(kneeRadians);

    // Kostka - obrót prostopadły do uda, obrót o (90 - ankle) względem uda
    float ankleRadians = kneeRadians + qDegreesToRadians(90 - ankleAngle);

    // Pozycja kostki względem kolana
    int ankleX = kneeX + legLength * qCos(ankleRadians);
    int ankleY = kneeY - legLength * qSin(ankleRadians);

    // Rysowanie ciała robota (biodro)
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(centerX - 50, centerY - 50, 100, 100);

    // Rysowanie kończyn
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(centerX, centerY, kneeX, kneeY);     // Udo
    painter.drawLine(kneeX, kneeY, ankleX, ankleY);       // Podudzie

    // Rysowanie stawów jako kół
    painter.setBrush(Qt::red);  // Kolano
    painter.drawEllipse(kneeX - 8, kneeY - 8, 16, 16);

    painter.setBrush(Qt::blue); // Kostka
    painter.drawEllipse(ankleX - 8, ankleY - 8, 16, 16);
}

void SideView::setJointAngles(float knee, float ankle)
{
    kneeAngle = knee;
    ankleAngle = ankle;
    update(); // Odśwież widok
}
