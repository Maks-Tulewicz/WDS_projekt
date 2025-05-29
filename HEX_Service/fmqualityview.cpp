#include "fmqualityview.h"
#include <QtCharts/QChart>
#include <QPen>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE

FmQualityView::FmQualityView(QWidget *parent)
    : QChartView(new QChart(), parent),
    rssiSeries(new QSplineSeries(this)),
    perSeries(new QLineSeries(this)),
    axisX(new QValueAxis(this)),
    axisY1(new QValueAxis(this)),
    axisY2(new QValueAxis(this))
{
    setRenderHint(QPainter::Antialiasing);
    setInteractive(true);

    auto *c = chart();
    c->setTitle("FM Link Quality");
    c->setAnimationOptions(QChart::SeriesAnimations);
    c->setTheme(QChart::ChartThemeBlueCerulean);

    // oś X
    axisX->setTitleText("Czas [ms]");
    axisX->setLabelFormat("%d");
    axisX->setRange(0, windowSize);
    axisX->setGridLineVisible(true);
    c->addAxis(axisX, Qt::AlignBottom);

    // oś Y1 (RSSI)
    axisY1->setTitleText("RSSI [dBm]");
    axisY1->setLabelFormat("%.1f");
    axisY1->setRange(-100, 0);
    axisY1->setGridLineVisible(true);
    c->addAxis(axisY1, Qt::AlignLeft);

    // oś Y2 (PER)
    axisY2->setTitleText("PER [%]");
    axisY2->setLabelFormat("%.1f");
    axisY2->setRange(0, 100);
    axisY2->setGridLineVisible(false);
    c->addAxis(axisY2, Qt::AlignRight);

    // serii
    rssiSeries->setName("RSSI");
    rssiSeries->setPen(QPen(QColor("#65D5C6"), 2));
    c->addSeries(rssiSeries);
    rssiSeries->attachAxis(axisX);
    rssiSeries->attachAxis(axisY1);

    perSeries->setName("PER");
    QPen dashPen(QColor("#F0822F"));
    dashPen.setStyle(Qt::DashLine);
    perSeries->setPen(dashPen);
    c->addSeries(perSeries);
    perSeries->attachAxis(axisX);
    perSeries->attachAxis(axisY2);

    c->legend()->setVisible(true);
    c->legend()->setAlignment(Qt::AlignBottom);
}

void FmQualityView::addMeasurement(float rssi, float per)
{
    // dopisanie nowego punktu w chwili t
    rssiSeries->append(t, rssi);
    perSeries->append(t, per);

    // przesunięcie okna osi X o jedną próbkę
    // utrzymujemy przedział [t-windowSize, t]
    if (t > windowSize) {
        axisX->setRange(t - windowSize, t);
    }

    t += 1;  // jeśli emitujesz co 1 ms, to t+=1
}
