#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>

/**
 * @brief Pojedyncza ramka danych z hexapoda.
 */
struct ServoFrame {
    int timeMs;               ///< Czas w ms
    QVector<float> angles;    ///< 18 kątów nóg
    float speed;              ///< Prędkość transmisji
    int packetCount;          ///< Liczba przesłanych pakietów
};

class DataReader : public QObject {
    Q_OBJECT

public:
    explicit DataReader(QObject *parent = nullptr);

    bool loadFromFile(const QString &filePath);
    bool loadFromDevice(QIODevice* device); // starsza metoda do jednorazowego odczytu
    void setSerialDevice(QIODevice* device); // nowa metoda do nasłuchiwania
    const ServoFrame* next();
    void reset();

signals:
    void newFrameReady(const ServoFrame &frame);

private slots:
    void handleSerialData();

private:
    QVector<ServoFrame> frames;
    int currentIndex = 0;
    QIODevice* serial = nullptr;
    QString buffer; ///< Bufor dla danych przychodzących
};

#endif // DATAREADER_H
