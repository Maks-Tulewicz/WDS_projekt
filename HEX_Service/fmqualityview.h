/**
 * @file fmqualityview.h
 * @brief Real-time FM link quality visualization widget
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
 * @brief Real-time chart widget for FM radio link quality monitoring
 *
 * FmQualityView provides a professional dual-axis chart for monitoring
 * FM radio communication quality in real-time. It displays two key metrics:
 * - **RSSI** (Received Signal Strength Indicator) in dBm as smooth spline
 * - **PER** (Packet Error Rate) in percentage as dashed line
 *
 * ## Features:
 * - **Dual Y-axis design** with independent scaling for RSSI and PER
 * - **Smooth spline interpolation** for RSSI values
 * - **Scrolling time window** with configurable width (default: 200 samples)
 * - **Professional styling** with Blue Cerulean theme and antialiasing
 * - **Automatic range adjustment** based on typical RF values
 * - **Interactive chart** with zoom and pan capabilities
 *
 * ## Technical Specifications:
 * - **RSSI Range**: -100 to 0 dBm (left Y-axis)
 * - **PER Range**: 0 to 100% (right Y-axis)
 * - **Update Rate**: Up to 1000 Hz (1ms resolution)
 * - **Window Size**: 200 samples (configurable)
 * - **Data Retention**: Automatic cleanup of old data points
 *
 * @see DataSimulator::qualitySample()
 * @see ServoFrame
 *
 * Example usage:
 * @code
 * FmQualityView *chart = new FmQualityView(parent);
 * connect(dataSource, &DataSource::qualityUpdate,
 *         chart, &FmQualityView::addMeasurement);
 * // Chart automatically updates with new data
 * @endcode
 */
    class FmQualityView : public QChartView
{
    Q_OBJECT

public:
    /**
     * @brief Constructor - Initialize FM quality chart
     *
     * Creates a professional dual-axis chart with optimized settings for
     * RF quality monitoring. Sets up series, axes, styling, and performance
     * optimizations for real-time data display.
     *
     * @param parent Parent widget for memory management
     */
    explicit FmQualityView(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Add new quality measurement to chart
     *
     * Adds a new data point to both RSSI and PER series. Automatically
     * manages the scrolling time window and updates axis ranges as needed.
     * Optimized for high-frequency updates (up to 1000 Hz).
     *
     * @param rssi Signal strength in dBm (typical range: -85 to -25 dBm)
     * @param per Packet error rate in percentage (typical range: 0 to 50%)
     *
     * @note Values outside typical ranges are accepted but may affect scaling
     * @note Chart automatically scrolls when window size is exceeded
     *
     * Example:
     * @code
     * chart->addMeasurement(-65.5, 2.3);  // Good signal quality
     * chart->addMeasurement(-82.1, 15.7); // Poor signal quality
     * @endcode
     */
    void addMeasurement(float rssi, float per);

private:
    QSplineSeries *rssiSeries;        /**< Smooth RSSI data series (left axis) */
    QLineSeries *perSeries;           /**< Dashed PER data series (right axis) */
    QValueAxis *axisX;                /**< Time axis (bottom) */
    QValueAxis *axisY1;               /**< RSSI value axis (left) */
    QValueAxis *axisY2;               /**< PER value axis (right) */
    qreal t = 0;                      /**< Current time counter */
    const qreal windowSize = 200;     /**< Visible time window in samples */
};
#endif
