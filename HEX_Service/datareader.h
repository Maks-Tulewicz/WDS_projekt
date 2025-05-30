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
    /**
     * @brief Konstruktor klasy DataReader
     * @param parent Wskaźnik na obiekt rodzica
     */
    explicit DataReader(QObject *parent = nullptr);

    /**
     * @brief Wczytuje ramki w formacie <...;CRC> i weryfikuje CRC
     * @param filePath Ścieżka do pliku
     * @return true jeśli wczytanie się powiodło
     */
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
    QVector<ServoFrame> frames;    ///< Bufor przechowujący wczytane ramki danych
    int currentIndex = 0;          ///< Indeks aktualnie przetwarzanej ramki
};

#endif // DATAREADER_H
