#include "datasimulator.h"
#include <QRandomGenerator>
#include"qrandom.h"
#include <QtMath>
#include "datareader.h"
class MainWindow;


DataSimulator::DataSimulator(QObject *parent)
    : QObject(parent),
    timer(new QTimer(this)),
    reader(new DataReader(this)),
    interval(1000)
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
        timer->stop(); // zabezpieczenie
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
    reader->reset();
    crcErrorCount = 0;
    // Clear any pending timer events
    if (timer->isActive()) {
        timer->stop();
    }
    // Give time for cleanup before potentially restarting
    QTimer::singleShot(100, this, [this]() {
        emit reset();
    });
}

void DataSimulator::setInterval(int intervalMs)
{
    interval = intervalMs;
    if (timer->isActive())
        timer->start(interval);
}
void DataSimulator::onTimerTick()
{
    static int frameCounter = 0;
    frameCounter++;

    const ServoFrame *frame = reader->next();
    if (frame) {
        // Emitujemy tylko co 10. ramkę do terminala
        if (frameCounter % 10 == 0) {
            QStringList log;
            log << QString("▶ Ramka #%1 | Czas: %2 ms").arg(frameCounter).arg(frame->timeMs);

            for (int i = 0; i < frame->angles.size(); ++i) {
                log << QString("  Noga %1, staw %2: %3°")
                           .arg(i / 3 + 1)
                           .arg(i % 3)
                           .arg(frame->angles[i], 0, 'f', 1);
            }

            log << QString("  Szybkość: %1").arg(frame->speed, 0, 'f', 2);
            log << QString("  Pakiety: %1").arg(frame->packetCount);

            emit logMessage(log.join('\n'));
        }

        emit frameReady(*frame);
    }

    // Symulacja jakości połączenia
    static float angle = 0;
    float rssi = -50 + 10 * qSin(qDegreesToRadians(angle));
    float per  = 10  + 5  * qCos(qDegreesToRadians(angle));
    angle = fmod(angle + 5, 360.0f);

    emit qualitySample(rssi, per);

    // Symulacja błędu (po jakości)
    if (simulateErrors && (QRandomGenerator::global()->bounded(10) == 0)) {
        crcErrorCount++;
        emit logError(QString("Zasymulowano błąd CRC! [%1/20]").arg(crcErrorCount));

        if (crcErrorCount >= 20) {
            emit logError("❌ Zbyt wiele błędów CRC – symulacja została zatrzymana!");
            pauseSimulation();  // zatrzymujemy timer
            emit disconnectedDueToErrors();  // sygnał do GUI
        }
        return;
}
}


void DataSimulator::setSimulateErrors(bool val) {
    simulateErrors = val;
}

