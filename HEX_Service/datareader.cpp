#include "datareader.h"
#include <QtGlobal> // qChecksum

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
        if (!line.startsWith('<') || !line.endsWith('>')) continue;

        QString core = line.mid(1, line.length() - 2);
        QStringList parts = core.split(';');
        // 1 timestamp + 18 angles + speed + packets + crc = 22 elementy
        if (parts.size() != 22) continue;
        // Weryfikacja CRC: sum bytes mod 256
        QByteArray raw = core.left(core.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int crc = parts.last().toInt(&okCrc);
        if (!okCrc) {
            qWarning() << "CRC nie parsuje:" << parts.last();
            continue;
        }
        uint8_t sum = 0;
        for (auto b : raw)
            sum = uint8_t(sum + static_cast<uint8_t>(b));
        if (sum != static_cast<uint8_t>(crc)) {
            qWarning() << "CRC niezgodne (obliczone=" << sum << "odebrane=" << crc << ")";
            continue;
        }


        ServoFrame frame;
        frame.timeMs     = parts[0].toInt();
        for (int i = 1; i <= 18; ++i)
            frame.angles.append(parts[i].toFloat());
        frame.speed       = parts[19].toFloat();
        frame.packetCount = parts[20].toInt();
        frames.append(frame);
    }

    file.close();
    return !frames.isEmpty();
}

const ServoFrame* DataReader::next()
{
    if (frames.isEmpty()) return nullptr;
    const ServoFrame* f = &frames[currentIndex];
    currentIndex = (currentIndex + 1) % frames.size();
    return f;
}

void DataReader::reset()
{
    currentIndex = 0;
}

bool DataReader::loadFromDevice(QIODevice* device)
{
    frames.clear();
    currentIndex = 0;

    while (device->canReadLine()) {
        QString line = QString::fromUtf8(device->readLine()).trimmed();
        if (!line.startsWith('<') || !line.endsWith('>')) continue;

        QString core = line.mid(1, line.length() - 2);
        QStringList parts = core.split(';');
        if (parts.size() != 22) continue;

        QByteArray raw = core.left(core.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int crc = parts.last().toInt(&okCrc);
        if (!okCrc) continue;

        uint8_t sum = 0;
        for (auto b : raw)
            sum = uint8_t(sum + static_cast<uint8_t>(b));
        if (sum != static_cast<uint8_t>(crc)) continue;

        ServoFrame frame;
        frame.timeMs     = parts[0].toInt();
        for (int i = 1; i <= 18; ++i)
            frame.angles.append(parts[i].toFloat());
        frame.speed       = parts[19].toFloat();
        frame.packetCount = parts[20].toInt();
        frames.append(frame);
    }

    return !frames.isEmpty();
}

void DataReader::setSerialDevice(QIODevice* device)
{
    if (serial) {
        disconnect(serial, nullptr, this, nullptr);
    }
    serial = device;
    buffer.clear();
    connect(serial, &QIODevice::readyRead, this, &DataReader::handleSerialData);
}

void DataReader::handleSerialData()
{
    if (!serial) return;
    buffer += QString::fromUtf8(serial->readAll());

    while (true) {
        int start = buffer.indexOf('<');
        int end   = buffer.indexOf('>', start);
        if (start == -1 || end == -1) break;

        QString frameStr = buffer.mid(start + 1, end - start - 1);
        buffer.remove(0, end + 1);

        QStringList parts = frameStr.split(';');
        if (parts.size() != 22) continue;

        QByteArray raw = frameStr.left(frameStr.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int crc = parts.last().toInt(&okCrc);
        if (!okCrc) continue;

        uint8_t sum = 0;
        for (auto b : raw)
            sum = uint8_t(sum + static_cast<uint8_t>(b));
        if (sum != static_cast<uint8_t>(crc)) continue;

        ServoFrame frame;
        frame.timeMs = parts[0].toInt();
        for (int i = 1; i <= 18; ++i)
            frame.angles.append(parts[i].toFloat());
        frame.speed = parts[19].toFloat();
        frame.packetCount = parts[20].toInt();

        emit newFrameReady(frame);
    }
}


