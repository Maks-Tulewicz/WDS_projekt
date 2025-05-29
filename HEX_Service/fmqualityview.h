#ifndef FMQUALITYVIEW_H
#define FMQUALITYVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

    /**
 * \brief Widget do wizualizacji jakości łącza FM.
 *
 * Rysuje dwie serie: RSSI w dBm (jako gładki spline)
 * oraz PER w \% (jako przerywana linia) z dwiema osiami Y.
 */
    class FmQualityView : public QChartView
{
    Q_OBJECT

public:
    explicit FmQualityView(QWidget *parent = nullptr);

public slots:
    /**
     * \brief Dodaje nową próbkę pomiaru do wykresu.
     * \param rssi  siła sygnału [dBm]
     * \param per   packet error rate [%]
     */
    void addMeasurement(float rssi, float per);

private:
    QSplineSeries*   rssiSeries;
    QLineSeries*     perSeries;
    QValueAxis*      axisX;
    QValueAxis*      axisY1;
    QValueAxis*      axisY2;
    qreal            t = 0;            // czas w ms
    const qreal      windowSize = 200; // szerokość okna czasowego
};

#endif // FMQUALITYVIEW_H
