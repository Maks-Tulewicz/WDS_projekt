#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal> // dla qChecksum()

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

    /// Wczytuje ramki w formacie <...;CRC> i weryfikuje CRC
    bool loadFromFile(const QString &filePath);

    /**
 * @brief Zwraca następną ramkę (zawija w pętli).
 * @return Wskaźnik na aktualną ramkę lub nullptr, jeżeli nie załadowano danych.
 */
    const ServoFrame* next();

    /**
 * @brief Resetuje odczyt do pierwszej ramki.
 */
    void reset();


private:
    QVector<ServoFrame> frames;
    int currentIndex = 0;
};

#endif // DATAREADER_H
