#include "topview.h"
#include <QPainter>
#include <QtMath>

TopView::TopView(QWidget *parent) : QWidget(parent)
{
    std::fill(std::begin(hipAngles), std::end(hipAngles), 90.f); // start w osi bazowej
}

void TopView::setHipAngle(int legIndex, float angleDeg)
{
    if (legIndex < 0 || legIndex >= 6) return;
    hipAngles[legIndex] = angleDeg;   // 0-180° z kontrolera
    update();
}

void TopView::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int cx = width()/2;
    const int cy = height()/2;
    const int bodyR   = qMin(width(),height())/6;
    const int legLen  = bodyR*2;       // linie > promień

    // ciało
    p.setBrush(Qt::gray);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPoint(cx,cy), bodyR, bodyR);

    // nogi
    p.setPen(QPen(Qt::black, 3));
    for (int i=0;i<6;++i)
    {
        // odchylenie: bazowa orientacja + (serwo-90°)
        float finalDeg = kBase[i] + (hipAngles[i]-90.f);
        float rad = qDegreesToRadians(finalDeg);

        int x2 = cx + legLen*std::cos(rad);
        int y2 = cy + legLen*std::sin(rad);

        p.drawLine(cx, cy, x2, y2);
    }
}
