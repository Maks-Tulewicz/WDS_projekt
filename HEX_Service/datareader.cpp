
#include "datareader.h"
#include <QTextStream>
#include <QDebug>

DataReader::DataReader(QObject *parent)
    : QObject(parent)
{}

bool DataReader::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie udało się otworzyć pliku:" << filePath;
        return false;
    }

    frames.clear();
    currentIndex = 0;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(";");
        if (parts.size() != 19) continue; // 1 czas + 18 serw

        ServoFrame frame;
        frame.timeMs = parts[0].toInt();

        for (int i = 1; i < parts.size(); ++i) {
            frame.angles.append(parts[i].toFloat());
        }

        frames.append(frame);
    }

    file.close();
    return !frames.isEmpty();
}

const ServoFrame* DataReader::next()
{
    if (frames.isEmpty()) return nullptr;

    const ServoFrame* frame = &frames[currentIndex];
    currentIndex = (currentIndex + 1) % frames.size();
    return frame;
}

void DataReader::reset()
{
    currentIndex = 0;
}
