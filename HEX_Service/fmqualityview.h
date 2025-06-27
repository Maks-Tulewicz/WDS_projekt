/**
 * @file fmqualityview.h
 * @brief Widget wizualizacji jakości łącza FM w czasie rzeczywistym
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef FMQUALITYVIEW_H
#define FMQUALITYVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

    /**
 * @brief Widget wykresu czasu rzeczywistego do monitorowania jakości łącza radiowego FM
 *
 * FmQualityView zapewnia profesjonalny wykres dwuosiowy do monitorowania
 * jakości komunikacji radiowej FM w czasie rzeczywistym. Wyświetla dwie kluczowe metryki:
 * - **RSSI** (Wskaźnik Siły Sygnału Odbieranego) w dBm jako płynną krzywą
 * - **PER** (Wskaźnik Błędów Pakietów) w procentach jako linię przerywaną
 *
 * ## Funkcje:
 * - **Projekt dwuosiowy** z niezależnym skalowaniem dla RSSI i PER
 * - **Płynna interpolacja krzywej** dla wartości RSSI
 * - **Przewijane okno czasowe** z konfigurowalną szerokością (domyślnie: 200 próbek)
 * - **Profesjonalne stylowanie** z motywem Blue Cerulean i antyaliasingiem
 * - **Automatyczne dopasowanie zakresu** na podstawie typowych wartości RF
 * - **Interaktywny wykres** z możliwościami powiększania i przesuwania
 *
 * ## Specyfikacje techniczne:
 * - **Zakres RSSI**: -100 do 0 dBm (lewa oś Y)
 * - **Zakres PER**: 0 do 100% (prawa oś Y)
 * - **Częstotliwość aktualizacji**: Do 1000 Hz (rozdzielczość 1ms)
 * - **Rozmiar okna**: 200 próbek (konfigurowalne)
 * - **Retencja danych**: Automatyczne czyszczenie starych punktów danych
 *
 * @see DataSimulator::qualitySample()
 * @see ServoFrame
 *
 * Przykład użycia:
 * @code
 * FmQualityView *wykres = new FmQualityView(parent);
 * connect(zrodloDanych, &ZrodloDanych::aktualizacjaJakosci,
 *         wykres, &FmQualityView::addMeasurement);
 * // Wykres automatycznie aktualizuje się z nowymi danymi
 * @endcode
 */
    class FmQualityView : public QChartView
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor - Inicjalizuje wykres jakości FM
     *
     * Tworzy profesjonalny wykres dwuosiowy z zoptymalizowanymi ustawieniami do
     * monitorowania jakości RF. Konfiguruje serie, osie, stylowanie i optymalizacje
     * wydajności dla wyświetlania danych w czasie rzeczywistym.
     *
     * @param parent Rodzic widget do zarządzania pamięcią
     */
    explicit FmQualityView(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Dodaj nowy pomiar jakości do wykresu
     *
     * Dodaje nowy punkt danych do serii RSSI i PER. Automatycznie
     * zarządza przewijanym oknem czasowym i aktualizuje zakresy osi w razie potrzeby.
     * Zoptymalizowane dla aktualizacji wysokiej częstotliwości (do 1000 Hz).
     *
     * @param rssi Siła sygnału w dBm (typowy zakres: -85 do -25 dBm)
     * @param per Wskaźnik błędów pakietów w procentach (typowy zakres: 0 do 50%)
     *
     * @note Wartości poza typowymi zakresami są akceptowane ale mogą wpłynąć na skalowanie
     * @note Wykres automatycznie przewija gdy rozmiar okna jest przekroczony
     *
     * Przykład:
     * @code
     * wykres->addMeasurement(-65.5, 2.3);  // Dobra jakość sygnału
     * wykres->addMeasurement(-82.1, 15.7); // Słaba jakość sygnału
     * @endcode
     */
    void addMeasurement(float rssi, float per);

private:
    QSplineSeries *rssiSeries;        /**< Płynna seria danych RSSI (lewa oś) */
    QLineSeries *perSeries;           /**< Przerywana seria danych PER (prawa oś) */
    QValueAxis *axisX;                /**< Oś czasu (dół) */
    QValueAxis *axisY1;               /**< Oś wartości RSSI (lewa) */
    QValueAxis *axisY2;               /**< Oś wartości PER (prawa) */
    qreal t = 0;                      /**< Aktualny licznik czasu */
    const qreal windowSize = 200;     /**< Widoczne okno czasowe w próbkach */
};

#endif // FMQUALITYVIEW_H
