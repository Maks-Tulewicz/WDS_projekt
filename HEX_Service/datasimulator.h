/**
 * @file datasimulator.h
 * @brief Symulacja i odtwarzanie danych serwomechanizmów hexapoda
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef DATASIMULATOR_H
#define DATASIMULATOR_H

#include <QObject>
#include <QTimer>
#include "qglobal.h"
#include "datareader.h"

/**
 * @brief Kontroler symulacji i odtwarzania danych ramek serwomechanizmów hexapoda
 *
 * DataSimulator zarządza odtwarzaniem danych serwomechanizmów z plików lub odbiorem
 * w czasie rzeczywistym z urządzeń szeregowych. Zapewnia kontrolę czasowania, symulację błędów
 * i integrację między źródłami danych a interfejsem graficznym.
 *
 * Symulator działa w dwóch trybach:
 * - **Tryb odtwarzania z pliku**: Odczytuje ramki z wczytanych danych pliku w kontrolowanych odstępach
 * - **Tryb danych zewnętrznych**: Odbiera ramki w czasie rzeczywistym z urządzenia szeregowego
 *
 * Kluczowe funkcje:
 * - Konfigurowalne tempo odtwarzania (1-1000ms odstępy)
 * - Symulacja błędów CRC do testowania obsługi błędów
 * - Automatyczne przełączanie trybu między plikiem a danymi zewnętrznymi
 * - Symulacja jakości połączenia (metryki RSSI/PER)
 * - Wszechstronne logowanie i raportowanie błędów
 *
 * @see DataReader
 * @see ServoFrame
 *
 * Przykład użycia:
 * @code
 * DataSimulator sym;
 * sym.loadData("dane_servo.txt");
 * sym.startSimulation(50);  // Odtwarzanie 20Hz
 *
 * // Połącz aby odbierać ramki
 * connect(&sym, &DataSimulator::frameReady,
 *         this, &MojaKlasa::przetworzRamke);
 * @endcode
 */
class DataSimulator : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Rodzic QObject do zarządzania pamięcią
     */
    explicit DataSimulator(QObject *parent = nullptr);

    /**
     * @brief Wczytaj dane serwomechanizmów z pliku
     *
     * Wczytuje dane ramek serwomechanizmów z pliku tekstowego do symulacji odtwarzania.
     * Plik powinien zawierać ramki w standardowym formacie z jedną
     * ramką na linię.
     *
     * @param filePath Ścieżka do pliku danych serwomechanizmów
     * @return true jeśli plik został pomyślnie wczytany
     * @return false jeśli plik nie mógł zostać otwarty lub nie zawiera prawidłowych danych
     *
     * @see startSimulation()
     * @see DataReader::loadFromFile()
     */
    bool loadData(const QString &filePath);

    /**
     * @brief Rozpocznij symulację odtwarzania ramek
     *
     * Rozpoczyna okresowe odtwarzanie wczytanych danych ramek. Ramki są emitowane
     * w określonych odstępach. Jeśli odbierane są dane zewnętrzne,
     * timer jest automatycznie zatrzymywany aby uniknąć konfliktów.
     *
     * @param intervalMs Odstęp odtwarzania w milisekundach (domyślnie: 1000ms)
     *
     * @note Minimalny zalecany odstęp: 10ms (100Hz)
     * @note Automatycznie zatrzymuje się jeśli aktywne jest zewnętrzne źródło danych
     *
     * @see pauseSimulation()
     * @see setInterval()
     * @see frameReady()
     */
    void startSimulation(int intervalMs = 1000);

    /**
     * @brief Wstrzymaj odtwarzanie ramek
     *
     * Zatrzymuje timer odtwarzania bez resetowania pozycji ramki.
     * Odtwarzanie może zostać wznowione przez startSimulation().
     *
     * @see startSimulation()
     * @see resetSimulation()
     */
    void pauseSimulation();

    /**
     * @brief Zresetuj symulację do stanu początkowego
     *
     * Resetuje liczniki ramek i statystyki błędów, ale zachowuje
     * status połączenia zewnętrznego źródła danych. Iterator ramek
     * jest resetowany do początku wczytanych danych.
     *
     * @note Nie zatrzymuje odbioru danych zewnętrznych
     * @note Emituje sygnał reset() aby powiadomić połączone komponenty
     *
     * @see reset()
     */
    void resetSimulation();

    /**
     * @brief Ustaw odstęp odtwarzania
     *
     * Zmienia odstęp odtwarzania ramek. Jeśli symulacja jest obecnie
     * uruchomiona, timer jest restartowany z nowym odstępem.
     *
     * @param intervalMs Nowy odstęp w milisekundach
     *
     * @note Zmiany obowiązują natychmiast jeśli symulacja jest aktywna
     */
    void setInterval(int intervalMs);

    /**
     * @brief Włącz lub wyłącz symulację błędów
     *
     * Gdy włączona, losowo wprowadza błędy CRC podczas odtwarzania aby testować
     * mechanizmy obsługi błędów. Błędy występują z ~10% prawdopodobieństwem.
     * Po 20 kolejnych błędach, symulacja jest automatycznie zatrzymywana.
     *
     * @param val true aby włączyć symulację błędów, false aby wyłączyć
     *
     * @see onTimerTick()
     * @see disconnectedDueToErrors()
     */
    void setSimulateErrors(bool val);

    /**
     * @brief Wczytaj dane z urządzenia szeregowego (legacy)
     *
     * Próbuje odczytać dane ze ścieżki urządzenia szeregowego. To jest metoda legacy
     * - użyj setSerialDevice() do komunikacji szeregowej w czasie rzeczywistym.
     *
     * @param devicePath Ścieżka do urządzenia szeregowego (np. "/dev/ttyUSB0")
     * @return true jeśli urządzenie zostało otwarte i dane odczytane pomyślnie
     * @return false jeśli urządzenie nie mogło zostać otwarte
     *
     * @deprecated Użyj setSerialDevice()
     */
    bool loadDataFromSerial(const QString &devicePath);

    /**
     * @brief Połącz z zewnętrznym urządzeniem szeregowym
     *
     * Konfiguruje odbiór danych w czasie rzeczywistym z urządzenia szeregowego. Gdy połączone,
     * symulator przełącza się w tryb danych zewnętrznych i zatrzymuje odtwarzanie z pliku.
     *
     * @param device Otwarte QIODevice (zwykle QSerialPort) do odbioru
     *
     * @note Urządzenie powinno być już otwarte i skonfigurowane
     * @note Automatycznie łączy się z sygnałami DataReader
     * @note Przełącza symulator w tryb danych zewnętrznych
     *
     * @see onExternalFrame()
     */
    void setSerialDevice(QIODevice* device);

signals:
    /**
     * @brief Sygnał emitowany dla każdej przetworzonej ramki
     *
     * To jest główny sygnał wyjściowy zawierający przetworzone dane ramki serwomechanizmów.
     * Emitowany zarówno w trybie odtwarzania z pliku jak i odbioru danych zewnętrznych.
     *
     * @param frame Kompletne dane ramki serwomechanizmów gotowe do przetwarzania przez GUI
     *
     * @see ServoFrame
     */
    void frameReady(const ServoFrame &frame);

    /**
     * @brief Sygnał emitowany dla komunikatów błędów
     *
     * Używany do raportowania błędów CRC, problemów komunikacji i innych
     * warunków błędów wymagających uwagi użytkownika.
     *
     * @param msg Tekst komunikatu błędu
     *
     * @see setSimulateErrors()
     */
    void logError(const QString &msg);

    /**
     * @brief Sygnał emitowany dla komunikatów informacyjnych
     *
     * Używany do aktualizacji statusu, statystyk ramek i innych informacji
     * niekrytycznych. Zwykle wyświetlane w logu aplikacji lub terminalu.
     *
     * @param msg Tekst komunikatu informacyjnego
     */
    void logMessage(const QString &msg);

    /**
     * @brief Sygnał emitowany gdy symulacja zatrzymuje się z powodu nadmiernych błędów
     *
     * Emitowany gdy symulacja błędów generuje zbyt wiele kolejnych błędów
     * CRC (próg: 20 błędów). Wskazuje że połączenie byłoby uznane za
     * niezdatne do użytku w rzeczywistych warunkach.
     *
     * @see setSimulateErrors()
     */
    void disconnectedDueToErrors();

    /**
     * @brief Sygnał emitowany gdy symulacja jest resetowana
     *
     * Powiadamia połączone komponenty że stan symulacji został zresetowany.
     * Komponenty powinny wyczyścić swoje wyświetlacze i przygotować się na nowe dane.
     *
     * @see resetSimulation()
     */
    void reset();

    /**
     * @brief Sygnał emitowany z pomiarami jakości łącza FM
     *
     * Dostarcza wartości RSSI i PER do monitorowania jakości połączenia.
     * Wartości mogą pochodzić z rzeczywistych odebranych ramek lub symulacji.
     *
     * @param rssi Wskaźnik Siły Sygnału Odbieranego w dBm (typowy zakres: -85 do -25)
     * @param per Wskaźnik Błędów Pakietów w procentach (typowy zakres: 0 do 50)
     *
     * @see FmQualityView
     */
    void qualitySample(float rssi, float per);

private slots:
    /**
     * @brief Obsłuż tick timera dla trybu odtwarzania z pliku
     *
     * Wywoływana okresowo podczas symulacji odtwarzania z pliku. Przechodzi do
     * następnej ramki, emituje sygnały i obsługuje symulację błędów jeśli włączona.
     *
     * @note Nie powinna być wywoływana gdy aktywne są dane zewnętrzne
     * @see startSimulation()
     */
    void onTimerTick();

    /**
     * @brief Obsłuż ramkę odebraną z zewnętrznego źródła
     *
     * Przetwarza ramki odebrane z połączonego urządzenia szeregowego. Automatycznie
     * przełącza symulator w tryb danych zewnętrznych i zatrzymuje odtwarzanie z pliku.
     *
     * @param frame Ramka odebrana z DataReader
     *
     * @see setSerialDevice()
     * @see DataReader::newFrameReady()
     */
    void onExternalFrame(const ServoFrame &frame);

private:
    QTimer *timer;               /**< Timer dla trybu odtwarzania z pliku */
    DataReader *reader;          /**< Czytnik danych dla operacji pliku i szeregowych */
    int interval;                /**< Odstęp odtwarzania w milisekundach */
    bool simulateErrors;         /**< Czy wprowadzać symulowane błędy */
    int crcErrorCount;           /**< Licznik kolejnych błędów CRC */
    int frameCounter;            /**< Licznik całkowitych przetworzonych ramek */
    float angle;                 /**< Kąt dla symulacji jakości */
    bool isReceivingData;        /**< Flaga wskazująca odbiór danych zewnętrznych */
};

#endif // DATASIMULATOR_H
