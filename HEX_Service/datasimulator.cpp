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
    connect(timer, &QTimer::timeout, this, &DataSimulator::onTimerTick);
}

bool DataSimulator::loadData(const QString &filePath)
{
    return reader->loadFromFile(filePath);
}

void DataSimulator::startSimulation(int intervalMs)
{
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
}

void DataSimulator::setInterval(int intervalMs)
{
    interval = intervalMs;
    if (timer->isActive())
        timer->start(interval);
}

void DataSimulator::onTimerTick()
{
    const ServoFrame *frame = reader->next();
    if (frame) {
        emit frameReady(*frame);
    }

    // Jakość połączenia
    static float angle = 0;
    float rssi = -50 + 10 * qSin(qDegreesToRadians(angle));
    float per  = 10  + 5  * qCos(qDegreesToRadians(angle));
    angle = fmod(angle + 5, 360.0f);

    // Błąd symulowany?
    if (simulateErrors && (QRandomGenerator::global()->bounded(10) == 0)) {
        emit logError("Zasymulowano błąd CRC!");
        return;  // pomijamy ramkę
    }

    emit qualitySample(rssi, per);
}

void DataSimulator::setSimulateErrors(bool val) {
    simulateErrors = val;
}

