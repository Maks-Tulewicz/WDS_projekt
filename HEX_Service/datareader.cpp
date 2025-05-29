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
