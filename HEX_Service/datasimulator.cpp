#include "datasimulator.h"
#include <QRandomGenerator>
#include "qrandom.h"
#include <QtMath>
#include "datareader.h"

class MainWindow;

DataSimulator::DataSimulator(QObject *parent)
    : QObject(parent),
    timer(new QTimer(this)),
    reader(new DataReader(this)),
    interval(1000),
    frameCounter(0),
    angle(0.0f),
    simulateErrors(false),
    crcErrorCount(0),
    isReceivingData(false)
{
    connect(timer, &QTimer::timeout, this, &DataSimulator::onTimerTick, Qt::UniqueConnection);
}

bool DataSimulator::loadData(const QString &filePath)
{
    return reader->loadFromFile(filePath);
}

void DataSimulator::startSimulation(int intervalMs)
{
    if (timer->isActive()) {
        timer->stop(); // safety check
    }
    interval = intervalMs;
    timer->start(interval);
}

void DataSimulator::pauseSimulation()
{
    timer->stop();
}

void DataSimulator::resetSimulation()
{
    // Stop timer before reset
    if (timer->isActive()) {
        timer->stop();
    }

    // Reset counters (but DO NOT reset isReceivingData!)
    frameCounter = 0;
    angle = 0.0f;
    crcErrorCount = 0;

    // DO NOT reset isReceivingData - keep external data source!
    // isReceivingData = false;  // <-- REMOVE THIS!

    // Reset reader
    reader->reset();

    // Emit reset signal
    emit reset();
}

void DataSimulator::setInterval(int intervalMs)
{
    interval = intervalMs;
    if (timer->isActive())
        timer->start(interval);
}

void DataSimulator::onTimerTick()
{
    qDebug() << "OLD onTimerTick() called (shouldn't happen with external data)";

    frameCounter++;

    const ServoFrame *frame = reader->next();
    if (frame) {
        // Emit only every 10th frame to terminal
        if (frameCounter % 10 == 0) {
            QStringList log;
            log << QString("Frame #%1 | Time: %2 ms").arg(frameCounter).arg(frame->timeMs);

            for (int i = 0; i < frame->angles.size(); ++i) {
                log << QString("  Leg %1, joint %2: %3°")
                           .arg(i / 3 + 1)
                           .arg(i % 3)
                           .arg(frame->angles[i], 0, 'f', 1);
            }

            log << QString("  Speed: %1").arg(frame->speed, 0, 'f', 2);
            log << QString("  Packets: %1").arg(frame->packetCount);

            emit logMessage(log.join('\n'));
        }

        emit frameReady(*frame);
    }

    // Connection quality simulation
    float rssi = -50 + 10 * qSin(qDegreesToRadians(angle));
    float per  = 10  + 5  * qCos(qDegreesToRadians(angle));
    angle = fmod(angle + 5, 360.0f);

    emit qualitySample(rssi, per);

    // Error simulation (after quality)
    if (simulateErrors && (QRandomGenerator::global()->bounded(10) == 0)) {
        crcErrorCount++;
        emit logError(QString("Simulated CRC error! [%1/20]").arg(crcErrorCount));

        if (crcErrorCount >= 20) {
            emit logError("Too many CRC errors - simulation stopped!");
            pauseSimulation();  // stop timer
            emit disconnectedDueToErrors();  // signal to GUI
        }
        return;
    }
}

void DataSimulator::setSimulateErrors(bool val) {
    simulateErrors = val;
}

bool DataSimulator::loadDataFromSerial(const QString &devicePath)
{
    QFile *dev = new QFile(devicePath, this);
    if (!dev->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open port" << devicePath;
        return false;
    }
    return reader->loadFromDevice(dev);
}

void DataSimulator::setSerialDevice(QIODevice* device) {
    qDebug() << "setSerialDevice() called";
    reader->setSerialDevice(device);

    // Test if signal arrives
    connect(reader, &DataReader::newFrameReady, this, [](const ServoFrame &frame) {
        qDebug() << "TEST: newFrameReady received! Time:" << frame.timeMs;
    });

    connect(reader, &DataReader::newFrameReady, this, &DataSimulator::onExternalFrame);
    qDebug() << "Connections established";
}

void DataSimulator::onExternalFrame(const ServoFrame &frame)
{
    qDebug() << "DataSimulator::onExternalFrame() - processing external frame";

    // Mark that we're receiving data from external source
    isReceivingData = true;

    // Stop main timer (we don't need simulation)
    if (timer->isActive()) {
        qDebug() << "Stopping internal simulation timer (using external data)";
        timer->stop();
    }

    // Increase frame counter
    frameCounter++;
    qDebug() << "FM data from frame - RSSI:" << frame.rssi << "dBm, PER:" << frame.per << "%";
    emit qualitySample(frame.rssi, frame.per);

    if (frameCounter % 10 == 0) {
        QStringList log;
        log << QString("External Frame #%1 | Time: %2 ms").arg(frameCounter).arg(frame.timeMs);
        log << QString("  FM: RSSI: %1 dBm, PER: %2%").arg(frame.rssi, 0, 'f', 1).arg(frame.per, 0, 'f', 1);
        emit logMessage(log.join('\n'));
    }

    emit frameReady(frame);
}
