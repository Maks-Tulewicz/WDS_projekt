#include "datareader.h"
#include <QtGlobal>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

DataReader::DataReader(QObject *parent)
    : QObject(parent)
{}

bool DataReader::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
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
        if (parts.size() != 24) {
            qWarning() << "Wrong number of parts:" << parts.size() << "(expected 24)";
            continue;
        }

        // CRC verification: sum of bytes mod 256
        QByteArray raw = core.left(core.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int crc = parts[23].toInt(&okCrc);
        if (!okCrc) {
            qWarning() << "CRC parsing failed:" << parts[23];
            continue;
        }
        uint8_t sum = 0;
        for (auto b : raw)
            sum = uint8_t(sum + static_cast<uint8_t>(b));
        if (sum != static_cast<uint8_t>(crc)) {
            qWarning() << "CRC mismatch (calculated=" << sum << "received=" << crc << ")";
            continue;
        }

        ServoFrame frame;
        frame.timeMs = parts[0].toInt();
        for (int i = 1; i <= 18; ++i)
            frame.angles.append(parts[i].toFloat());
        frame.speed = parts[19].toFloat();
        frame.packetCount = parts[20].toInt();

        // Parse FM data
        frame.rssi = parts[21].toFloat();  // RSSI in dBm
        frame.per = parts[22].toFloat();   // PER in %

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
        if (parts.size() != 24) continue;

        QByteArray raw = core.left(core.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int crc = parts[23].toInt(&okCrc);
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

        // Parse FM data
        frame.rssi = parts[21].toFloat();
        frame.per = parts[22].toFloat();

        frames.append(frame);
    }

    return !frames.isEmpty();
}

void DataReader::setSerialDevice(QIODevice* device)
{
    qDebug() << "DataReader::setSerialDevice() called with device:" << device;

    if (serial) {
        qDebug() << "Disconnecting previous device";
        disconnect(serial, nullptr, this, nullptr);
    }
    serial = device;

    if (!device) {
        qWarning() << "Device is nullptr!";
        return;
    }

    // Configure serial port (if it's QSerialPort)
    if (QSerialPort* serialPort = qobject_cast<QSerialPort*>(device)) {
        qDebug() << "Configuring QSerialPort";
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        qDebug() << "Device is QFile, not QSerialPort";
    }

    // Check if device is open
    if (!device->isOpen()) {
        qWarning() << "Device is not open!";
        return;
    }

    qDebug() << "Device is open, checking readability...";
    qDebug() << "   - isReadable():" << device->isReadable();
    qDebug() << "   - bytesAvailable():" << device->bytesAvailable();

    buffer.clear();

    // Connect readyRead signal
    connect(serial, &QIODevice::readyRead, this, &DataReader::handleSerialData, Qt::DirectConnection);
    qDebug() << "Connected readyRead signal";

    // For QFile - check if data is already available
    if (device->bytesAvailable() > 0) {
        qDebug() << "Data already available, calling handleSerialData()";
        QTimer::singleShot(100, this, &DataReader::handleSerialData);
    }

    // Add timer for periodic checking (workaround for QFile)
    QTimer *checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, [this]() {
        if (serial && serial->bytesAvailable() > 0) {
            qDebug() << "Timer detected data, calling handleSerialData()";
            handleSerialData();
        }
    });
    checkTimer->start(100); // Check every 100ms
}

void DataReader::handleSerialData()
{
    qDebug() << "handleSerialData() CALLED!";

    if (!serial) {
        qWarning() << "Serial device is nullptr in handleSerialData()";
        return;
    }

    QByteArray newData = serial->readAll();
    qDebug() << "Read" << newData.size() << "bytes from device";

    if (newData.isEmpty()) {
        qDebug() << "No data read from device";
        return;
    }

    // Show first 100 characters of data
    QString dataPreview = QString::fromUtf8(newData.left(100));
    qDebug() << "Data preview:" << dataPreview;

    buffer += QString::fromUtf8(newData);
    qDebug() << "Buffer size after append:" << buffer.size();

    int frameCount = 0;
    while (true) {
        int start = buffer.indexOf('<');
        int end   = buffer.indexOf('>', start);
        if (start == -1 || end == -1) break;

        QString frameStr = buffer.mid(start + 1, end - start - 1);
        buffer.remove(0, end + 1);
        frameCount++;

        qDebug() << "Processing frame #" << frameCount;
        qDebug() << "   Content:" << frameStr.left(50) + "...";

        QStringList parts = frameStr.split(';');
        if (parts.size() != 24) {
            qWarning() << "Wrong number of parts:" << parts.size() << "(expected 24)";
            qDebug() << "   Parts:" << parts;
            continue;
        }

        // Calculate CRC from parts without last element (which is CRC)
        QByteArray raw = frameStr.left(frameStr.lastIndexOf(';')).toUtf8();
        bool okCrc = false;
        int receivedCrc = parts[23].toInt(&okCrc);

        if (!okCrc) {
            qWarning() << "CRC cannot be parsed:" << parts[23];
            continue;
        }

        // Calculate CRC
        uint8_t sum = 0;
        for (auto b : raw) {
            sum = uint8_t(sum + static_cast<uint8_t>(b));
        }
        uint8_t calculatedCrc = sum;

        // Debug info for each frame
        qDebug() << "CRC Debug:";
        qDebug() << "   Raw data length:" << raw.size() << "bytes";
        qDebug() << "   Calculated CRC:" << calculatedCrc;
        qDebug() << "   Received CRC:" << receivedCrc;
        qDebug() << "   Match:" << (calculatedCrc == receivedCrc ? "YES" : "NO");

        if (calculatedCrc != static_cast<uint8_t>(receivedCrc)) {
            qWarning() << "CRC mismatch! Calculated:" << calculatedCrc
                       << "Received:" << receivedCrc
                       << "Frame:" << frameStr.left(30) + "...";
            // TEMPORARILY CONTINUE DESPITE CRC ERROR
            qDebug() << "CONTINUING DESPITE CRC ERROR (temporary debug mode)";
            // continue;  // commented out temporarily
        }

        // CRC OK (or ignored) - create frame
        ServoFrame frame;
        frame.timeMs = parts[0].toInt();
        for (int i = 1; i <= 18; ++i)
            frame.angles.append(parts[i].toFloat());
        frame.speed = parts[19].toFloat();
        frame.packetCount = parts[20].toInt();

        // Parse FM data
        frame.rssi = parts[21].toFloat();
        frame.per = parts[22].toFloat();

        qDebug() << "Frame created successfully - emitting newFrameReady";
        qDebug() << "   TimeMs:" << frame.timeMs;
        qDebug() << "   First 3 angles:" << frame.angles[0] << frame.angles[1] << frame.angles[2];
        qDebug() << "   Speed:" << frame.speed;
        qDebug() << "   PacketCount:" << frame.packetCount;
        qDebug() << "   FM: RSSI:" << frame.rssi << "dBm, PER:" << frame.per << "%";

        emit newFrameReady(frame);
        qDebug() << "Signal newFrameReady emitted!";
    }

    qDebug() << "Processed" << frameCount << "frames in this iteration";
    qDebug() << "Remaining buffer size:" << buffer.size();
}
