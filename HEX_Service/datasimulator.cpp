#include "datasimulator.h"

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
    if (frame)
        emit frameReady(*frame);
}
