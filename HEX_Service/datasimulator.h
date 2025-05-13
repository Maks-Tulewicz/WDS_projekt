#ifndef DATASIMULATOR_H
#define DATASIMULATOR_H

#include <QObject>
#include <QTimer>
#include "datareader.h"

/**
 * @brief Klasa symulująca odtwarzanie danych z pliku z kątami.
 *
 * Klasa ta zarządza procesem odczytu danych z pliku przy użyciu klasy DataReader
 * oraz emituje dane w postaci ramki (`ServoFrame`) do interfejsu użytkownika.
 * Może uruchamiać, pauzować oraz resetować symulację, a także kontrolować częstotliwość odczytu.
 */
class DataSimulator : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy DataSimulator.
     * @param parent Wskaźnik na obiekt rodzica (może być nullptr).
     */
    explicit DataSimulator(QObject *parent = nullptr);

    /**
     * @brief Ładuje dane z pliku.
     * @param filePath Ścieżka do pliku z danymi.
     * @return true, jeśli dane zostały poprawnie załadowane; false w przeciwnym razie.
     */
    bool loadData(const QString &filePath);

    /**
     * @brief Uruchamia symulację.
     * @param intervalMs Częstotliwość symulacji w milisekundach.
     * Domyślnie 1000 ms (1 sekunda).
     */
    void startSimulation(int intervalMs = 1000);

    /**
     * @brief Pauzuje symulację.
     * Zatrzymuje odczyt danych z pliku i wstrzymuje animację.
     */
    void pauseSimulation();

    /**
     * @brief Resetuje symulację do początku.
     * Powraca do początkowych danych w pliku i ponownie uruchamia symulację.
     */
    void resetSimulation();

    /**
     * @brief Ustawia częstotliwość symulacji.
     * @param intervalMs Nowa częstotliwość odczytu w milisekundach.
     */
    void setInterval(int intervalMs);

signals:
    /**
     * @brief Sygnał emitujący ramkę danych do GUI.
     * @param frame Ramka zawierająca dane o kątach serwomechanizmów.
     */
    void frameReady(const ServoFrame &frame);

private slots:
    /**
     * @brief Funkcja obsługująca odczyt danych co `timer` (co `interval` ms).
     */
    void onTimerTick();

private:
    QTimer *timer;       ///< Timer do odtwarzania danych
    DataReader *reader;  ///< Odczyt danych z pliku
    int interval;        ///< Częstotliwość odczytu danych (ms)
};

#endif // DATASIMULATOR_H
