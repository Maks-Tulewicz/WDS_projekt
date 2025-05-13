#include "servoanglemanager.h"

ServoAngleManager::ServoAngleManager(QObject *parent)
    : QObject(parent)
{}

void ServoAngleManager::registerLabel(int leg, int joint, QLabel *label)
{
    QString key = QString("%1_%2").arg(leg).arg(joint);
    servoLabels[key] = label;
}

void ServoAngleManager::setAngle(int leg, int joint, float angle)
{
    QString key = QString("%1_%2").arg(leg).arg(joint);
    if (servoLabels.contains(key)) {
        servoLabels[key]->setText(QString::number(angle, 'f', 1) + "°");
    }
}
