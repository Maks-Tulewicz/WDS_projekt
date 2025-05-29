#include "topview.h"
#include <QPainter>
#include <QtMath>

static constexpr float kBase[6] = {
    225, 270, 315,   // dół: –135°, –90°, –45°
    45,  90, 135    // góra:  45°,   90°,  135°
};



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

    // środek widgetu
    const int cx   = width()  / 2;
    const int cy   = height() / 2;
    // promień ciała (okrąg)
    const int bodyR  = qMin(width(), height()) / 6;
    // długość wystającej nogi poza obrys ciała
    const int legLen = bodyR ;

    // rysujemy ciało
    p.setBrush(Qt::gray);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPoint(cx, cy), bodyR, bodyR);

    // rysujemy nogi
    p.setPen(QPen(Qt::black, 3));
    for (int i = 0; i < 6; ++i) {
        // bazowa orientacja + odchylenie serwa (−90 aby 0° serwa = w górę)
        float finalDeg = kBase[i] + (hipAngles[i] - 90.f);
        float rad      = qDegreesToRadians(finalDeg);

        // punkt startu na krawędzi okręgu
        int x1 = cx + int(bodyR   * std::cos(rad));
        int y1 = cy + int(bodyR   * std::sin(rad));
        // punkt końca za obrysem
        int x2 = cx + int((bodyR + legLen) * std::cos(rad));
        int y2 = cy + int((bodyR + legLen) * std::sin(rad));

        p.drawLine(x1, y1, x2, y2);
    }
}

