/**
 * @file datareader.h
 * @brief Odczyt i parsowanie danych ramek serwomechanizmów hexapoda
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>
#include <QIODevice>

class QSerialPort;

/**
 * @brief Struktura reprezentująca pojedynczą ramkę danych z robota hexapod
 *
 * Struktura zawiera wszystkie dane odebrane w jednej ramce z robota hexapod,
 * włączając kąty serwomechanizmów, informacje czasowe oraz metryki jakości łącza FM.
 */
struct ServoFrame {
    int timeMs;               /**< Znacznik czasu w milisekundach od startu */
    QVector<float> angles;    /**< 18 kątów serwomechanizmów w stopniach (6 nóg × 3 stawy) */
    float speed;              /**< Prędkość ruchu w jednostkach/sekunda */
    int packetCount;          /**< Sekwencyjny licznik pakietów */
    float rssi;               /**< Wskaźnik siły sygnału odbieranego w dBm */
    float per;                /**< Wskaźnik błędów pakietów w procentach */
};

/**
 * @brief Klasa do odczytu i parsowania danych serwomechanizmów hexapoda
 *
 * DataReader obsługuje odczyt danych ramek serwomechanizmów z plików lub urządzeń szeregowych.
 * Obsługuje dwa tryby pracy:
 * - Odczyt z pliku: Wczytanie kompletnego zestawu danych z pliku do odtwarzania
 * - Odczyt szeregowy: Odbiór danych w czasie rzeczywistym z portu szeregowego z parsowaniem ramek
 *
 * Oczekiwany format danych:
 * `<znacznik_czasu;kąt1;kąt2;...;kąt18;prędkość;licznik_pakietów;rssi;per;crc>`
 *
 * @note Weryfikacja CRC jest wykonywana przy użyciu sumy bajtów modulo 256
 *
 * @see ServoFrame
 * @see DataSimulator
 */
class DataReader : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Rodzic QObject do zarządzania pamięcią
     */
    explicit DataReader(QObject *parent = nullptr);

    /**
     * @brief Wczytaj ramki serwomechanizmów z pliku
     *
     * Odczytuje i parsuje wszystkie ramki z pliku tekstowego. Każda linia powinna zawierać
     * kompletną ramkę w oczekiwanym formacie. Nieprawidłowe ramki są pomijane
     * z komunikatami ostrzegawczymi.
     *
     * @param filePath Ścieżka do pliku zawierającego dane ramek serwomechanizmów
     * @return true jeśli plik został pomyślnie wczytany i zawiera prawidłowe ramki
     * @return false jeśli plik nie może zostać otwarty lub nie zawiera prawidłowych ramek
     *
     * @see next()
     * @see reset()
     *
     * Przykład użycia:
     * @code
     * DataReader reader;
     * if (reader.loadFromFile("dane_servo.txt")) {
     *     const ServoFrame* ramka = reader.next();
     *     // Przetwórz ramkę...
     * }
     * @endcode
     */
    bool loadFromFile(const QString &filePath);

    /**
     * @brief Wczytaj ramki z QIODevice (jednorazowy odczyt)
     *
     * Odczytuje wszystkie dostępne dane z urządzenia natychmiast. To jest metoda legacy
     * do jednorazowego odczytu danych. Do ciągłego monitorowania portu szeregowego,
     * użyj setSerialDevice().
     *
     * @param device Otwarte QIODevice do odczytu
     * @return true jeśli dane zostały pomyślnie odczytane i sparsowane
     * @return false jeśli nie znaleziono prawidłowych ramek
     *
     * @deprecated Użyj setSerialDevice() do komunikacji z portem szeregowym
     */
    bool loadFromDevice(QIODevice* device);

    /**
     * @brief Ustaw urządzenie szeregowe do ciągłego monitorowania danych
     *
     * Konfiguruje czytnik do monitorowania urządzenia szeregowego dla przychodzących ramek.
     * Urządzenie powinno być już otwarte. Automatycznie konfiguruje parametry portu
     * szeregowego jeśli urządzenie to QSerialPort.
     *
     * @param device Otwarte QIODevice (zwykle QSerialPort) do monitorowania
     *
     * @note Urządzenie musi być już otwarte
     * @note Poprzednie połączenia urządzeń są automatycznie rozłączane
     * @note Emituje sygnał newFrameReady() dla każdej prawidłowej odebranej ramki
     *
     * @see newFrameReady()
     * @see handleSerialData()
     */
    void setSerialDevice(QIODevice* device);

    /**
     * @brief Pobierz następną ramkę z wczytanych danych
     *
     * Zwraca następną ramkę w sekwencji. Automatycznie przechodzi do początku
     * po osiągnięciu końca wczytanych danych.
     *
     * @return Wskaźnik do następnej ServoFrame, lub nullptr jeśli nie wczytano danych
     *
     * @note Zwrócony wskaźnik jest ważny do następnego wywołania loadFromFile()
     * @see loadFromFile()
     * @see reset()
     */
    const ServoFrame* next();

    /**
     * @brief Zresetuj iterator ramek do początku
     *
     * Resetuje wewnętrzny licznik ramek aby rozpocząć odczyt od pierwszej
     * ramki ponownie.
     *
     * @see next()
     */
    void reset();

signals:
    /**
     * @brief Sygnał emitowany gdy nowa ramka jest odebrana z urządzenia szeregowego
     *
     * Ten sygnał jest emitowany dla każdej prawidłowej ramki odebranej z urządzenia
     * szeregowego ustawionego przez setSerialDevice(). Ramka została już zweryfikowana
     * pod kątem CRC.
     *
     * @param frame Kompletne dane ramki serwomechanizmów
     *
     * @see setSerialDevice()
     */
    void newFrameReady(const ServoFrame &frame);

private slots:
    /**
     * @brief Obsłuż przychodzące dane szeregowe
     *
     * Ten slot jest automatycznie połączony z sygnałem readyRead urządzenia
     * szeregowego. Odczytuje przychodzące dane, buforuje je i próbuje
     * sparsować kompletne ramki.
     *
     * @note Wykonuje wykrywanie granic ramek i weryfikację CRC
     * @note Emituje newFrameReady() dla każdej prawidłowej ramki
     */
    void handleSerialData();

private:
    QVector<ServoFrame> frames;     /**< Przechowywanie wczytanych ramek */
    int currentIndex = 0;           /**< Aktualna pozycja w wektorze ramek */
    QIODevice* serial = nullptr;    /**< Połączone urządzenie szeregowe */
    QString buffer;                 /**< Bufor dla przychodzących danych szeregowych */
};

#endif // DATAREADER_H
