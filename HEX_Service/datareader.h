#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>

/**
 * @brief Struktura reprezentująca pojedynczy krok w animacji serwomechanizmów.
 *
 * Ta struktura przechowuje czas (w milisekundach) oraz 18 kątów dla 6 nóg (po 3 stawy na nogę).
 */
struct ServoFrame {
    int timeMs;               ///< Czas w milisekundach
    QVector<float> angles;    ///< 18 kątów (6 nóg × 3 stawy)
};

/**
 * @brief Klasa do wczytywania danych z pliku tekstowego.
 *
 * Klasa odpowiedzialna za wczytywanie danych z pliku z kątami serwomechanizmów
 * i umożliwia ich odczyt w postaci klatek (ServoFrame).
 */
class DataReader : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy DataReader.
     * @param parent Wskaźnik na obiekt rodzica (może być nullptr).
     */
    explicit DataReader(QObject *parent = nullptr);

    /**
     * @brief Wczytuje dane z pliku tekstowego.
     * @param filePath Ścieżka do pliku z danymi.
     * @return true, jeśli dane zostały poprawnie wczytane; w przeciwnym razie false.
     */
    bool loadFromFile(const QString &filePath);

    /**
     * @brief Zwraca następny krok (w pętli).
     * @return Wskaźnik na kolejny `ServoFrame` lub nullptr, jeśli brak danych.
     */
    const ServoFrame* next();

    /**
     * @brief Resetuje wskaźnik do początku.
     * Funkcja ta przywraca wskaźnik `currentIndex` do wartości 0.
     */
    void reset();

private:
    QVector<ServoFrame> frames; ///< Kontener przechowujący wczytane klatki z kątami
    int currentIndex = 0;        ///< Wskaźnik na aktualną klatkę (indeks)
};

#endif // DATAREADER_H
