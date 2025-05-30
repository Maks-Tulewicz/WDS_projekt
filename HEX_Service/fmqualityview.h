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
    /**
     * @brief Konstruktor widoku jakości
     * @param parent Wskaźnik na widget rodzica
     */

    explicit FmQualityView(QWidget *parent = nullptr);

public slots:
    /**
     * \brief Dodaje nową próbkę pomiaru do wykresu.
     * \param rssi  siła sygnału [dBm]
     * \param per   packet error rate [%]
     */
    void addMeasurement(float rssi, float per);

private:
    QSplineSeries *rssiSeries;  ///< Seria danych RSSI
    QLineSeries *perSeries;     ///< Seria danych PER
    QValueAxis *axisX;          ///< Oś czasu
    QValueAxis *axisY1;         ///< Oś wartości RSSI
    QValueAxis *axisY2;         ///< Oś wartości PER
    qreal t = 0;               ///< Aktualny czas w milisekundach
    const qreal windowSize = 200; ///< Szerokość okna wyświetlania w próbkach
};

#endif // FMQUALITYVIEW_H
