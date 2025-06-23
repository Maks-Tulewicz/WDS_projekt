/**
 * @file mainwindow.h
 * @brief Główne okno aplikacji interfejsu sterowania robotem hexapod
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPlainTextEdit>
#include <qtranslator.h>
#include "servoanglemanager.h"
#include "datasimulator.h"
#include "sideview.h"
#include "topview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Główne okno aplikacji do sterowania i monitorowania robota hexapod
 *
 * MainWindow służy jako centralny hub aplikacji sterowania hexapodem,
 * zapewniając kompleksowy interfejs do monitorowania kątów serwomechanizmów, wizualizacji
 * ruchu robota oraz śledzenia jakości komunikacji. Okno integruje
 * wiele wyspecjalizowanych widoków i kontrolek w spójne doświadczenie użytkownika.
 *
 * ## Kluczowe funkcje:
 * - **Interfejs wielozakładkowy** z kątami serwomechanizmów, wizualizacjami, monitorowaniem FM i ustawieniami
 * - **Wyświetlanie kątów serwomechanizmów w czasie rzeczywistym** dla wszystkich 18 serwomotorów (6 nóg × 3 stawy)
 * - **Wizualizacje 3D** z widokiem z góry i widokiem bocznym reprezentacji robota
 * - **Monitorowanie jakości FM** z wykresami RSSI/PER i statusem połączenia
 * - **Obsługa wielu języków** (polski/angielski) z natychmiastowym przełączaniem
 * - **Symulacja błędów i logowanie** do testowania i debugowania
 * - **Komunikacja szeregowa** z automatycznym wykrywaniem i konfiguracją portów
 *
 * ## Architektura:
 * Okno podąża za wzorcem Model-View-Controller:
 * - **Model**: DataSimulator dostarcza dane ramek z plików lub portów szeregowych
 * - **Widok**: Wiele wyspecjalizowanych widgetów (TopView, SideView, FmQualityView)
 * - **Kontroler**: MainWindow koordynuje przepływ danych i interakcje użytkownika
 *
 * @see DataSimulator
 * @see ServoAngleManager
 * @see TopView
 * @see SideView
 * @see FmQualityView
 *
 * Przykład inicjalizacji:
 * @code
 * MainWindow okno;
 * okno.show();
 * // Okno automatycznie konfiguruje wszystkie komponenty i rozpoczyna odbiór danych
 * @endcode
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor - Inicjalizuje główne okno aplikacji
     *
     * Konfiguruje kompletny interfejs użytkownika włączając:
     * - Nawigację zakładkami i połączenia przycisków
     * - Zarządzanie kątami serwomechanizmów dla 18 serwomotorów
     * - Symulację danych z obsługą plików i portu szeregowego
     * - Wykresy monitorowania jakości
     * - System tłumacza wielojęzycznego
     * - Automatyczne wykrywanie i konfigurację urządzenia szeregowego
     *
     * Konstruktor automatycznie próbuje połączyć się z domyślnym urządzeniem
     * szeregowym (/dev/pts/3) i konfiguruje je dla komunikacji 115200 baud.
     *
     * @param parent Rodzic widget do zarządzania pamięcią (zwykle nullptr dla głównego okna)
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor - Czyści zasoby
     *
     * Właściwie zwalnia zasoby UI i zapewnia czyste zamknięcie wszystkich
     * kanałów komunikacji i timerów.
     */
    ~MainWindow();

    /**
     * @brief Aktualizuj GUI nowymi danymi ramki serwomechanizmów
     *
     * To jest główna metoda przetwarzania danych która aktualizuje wszystkie komponenty
     * wizualne gdy przychodzą nowe dane serwomechanizmów. Aktualizacje są wykonywane
     * efektywnie aby utrzymać płynne wyświetlanie w czasie rzeczywistym.
     *
     * ## Aktualizowane komponenty:
     * - Poszczególne etykiety kątów serwomechanizmów (18 serwomechanizmów)
     * - Wizualizacja kątów bioder w widoku z góry (6 bioder)
     * - Wizualizacja kolana/kostki w widoku bocznym (wybrana noga)
     * - Wyjście terminala ze statystykami ramek
     *
     * @param frame Kompletna ramka serwomechanizmów zawierająca kąty, timing i dane jakości
     *
     * @note Wywoływana automatycznie gdy DataSimulator emituje frameReady()
     * @note Aktualizacje są ograniczane aby utrzymać wydajność GUI 60fps
     *
     * @see ServoFrame
     * @see DataSimulator::frameReady()
     */
    void updateServoGUI(const ServoFrame &frame);

private slots:
    /**
     * @brief Pokaż zakładkę kątów serwomechanizmów
     *
     * Przełącza główny wyświetlacz na widok kątów serwomechanizmów, który pokazuje
     * szczegółową tabelę wszystkich 18 pozycji serwomechanizmów zorganizowaną według nóg i stawów.
     */
    void showServoAngles();

    /**
     * @brief Pokaż zakładkę animacji/wizualizacji
     *
     * Przełącza na zakładkę wizualizacji zawierającą widgety TopView i SideView
     * które zapewniają graficzną reprezentację postawy i ruchu robota.
     */
    void showAnimations();

    /**
     * @brief Pokaż zakładkę jakości połączenia FM
     *
     * Wyświetla interfejs monitorowania serwisu FM z wykresami RSSI/PER
     * w czasie rzeczywistym i informacjami o statusie połączenia.
     */
    void showConnection();

    /**
     * @brief Pokaż zakładkę ustawień aplikacji
     *
     * Otwiera panel ustawień dla wyboru języka, konfiguracji symulacji błędów
     * i innych preferencji aplikacji.
     */
    void showSettings();

    /**
     * @brief Obsłuż zmianę wyboru nogi w widoku bocznym
     *
     * Aktualizuje wizualizację widoku bocznego gdy użytkownik wybiera inną
     * nogę do szczegółowego badania. Widok boczny pokazuje pozycje stawów kolana i kostki
     * dla wybranej nogi.
     *
     * @param index Indeks nogi (0-5) odpowiadający nogom 1-6
     *
     * @see SideView::setActiveLeg()
     */
    void onLegSelectionChanged(int index);

    /**
     * @brief Zaloguj komunikat błędu do terminala
     *
     * Wyprowadza komunikaty błędów do terminala aplikacji z odpowiednim
     * formatowaniem i prefiksem błędu dla widoczności użytkownika.
     *
     * @param msg Tekst komunikatu błędu
     *
     * @see handleLogError()
     */
    void logError(const QString &msg);

    /**
     * @brief Obsłuż i sformatuj komunikaty błędów
     *
     * Przetwarza komunikaty błędów z formatowaniem HTML (czerwony kolor) dla
     * lepszej widoczności w wyświetlaczu logu aplikacji.
     *
     * @param msg Komunikat błędu do sformatowania i wyświetlenia
     */
    void handleLogError(const QString &msg);

    /**
     * @brief Obsłuż i sformatuj komunikaty informacyjne
     *
     * Przetwarza standardowe komunikaty logu z automatycznym zarządzaniem limitem linii
     * aby zapobiec nadmiernemu użyciu pamięci w długotrwałych sesjach.
     *
     * @param msg Komunikat informacyjny do wyświetlenia
     *
     * @note Automatycznie ogranicza log do 1000 linii
     */
    void handleLogMessage(const QString &msg);

    /**
     * @brief Obsłuż zmianę języka z ustawień
     *
     * Dynamicznie przełącza język aplikacji między obsługiwanymi
     * językami (polski/angielski) bez wymagania restartu. Aktualizuje
     * wszystkie elementy UI i regeneruje etykiety z ikonami.
     *
     * @param index Indeks języka (0=Polski, 1=Angielski)
     *
     * @see setupLabels()
     * @see changeEvent()
     */
    void onLanguageChanged(int index);

    /**
     * @brief Obsłuż rozłączenie symulacji z powodu błędów
     *
     * Wywoływana gdy symulator danych rozłącza się z powodu nadmiernych błędów
     * CRC. Aktualizuje stan UI i włącza opcję ponownego połączenia.
     *
     * @see DataSimulator::disconnectedDueToErrors()
     */
    void onSimDisconnect();

    /**
     * @brief Obsłuż kliknięcie przycisku ponownego połączenia
     *
     * Próbuje zrestartować symulację po rozłączeniu z powodu błędów.
     * Wykonuje właściwe czyszczenie i sekwencję restartu z odpowiednimi opóźnieniami.
     */
    void onReconnectClicked();

private:
    Ui::MainWindow *ui;               /**< Wskaźnik wygenerowanego interfejsu UI */
    DataSimulator *simulator;         /**< Kontroler symulacji i odtwarzania danych */
    ServoAngleManager *servoManager;  /**< Manager aktualizacji etykiet kątów serwomechanizmów */
    SideView *sideView;              /**< Widget dla szczegółowego widoku bocznego nogi */
    TopView *topView;                /**< Widget dla przeglądu robota z góry */
    QComboBox *comboBoxLegSide;      /**< Dropdown wyboru nogi w widoku bocznym */
    QTranslator *translator;          /**< Tłumacz Qt dla obsługi wielu języków */

    /**
     * @brief Wyprowadź komunikat do terminala aplikacji
     *
     * Metoda pomocnicza do logowania komunikatów do zintegrowanego wyświetlacza terminala.
     * Obecnie wyłączona aby zmniejszyć wizualny bałagan podczas normalnej pracy.
     *
     * @param message Tekst komunikatu do zalogowania
     */
    void logToTerminal(const QString &message);

    /**
     * @brief Wczytaj pliki tłumaczeń dla określonego języka
     *
     * Wczytuje i aktywuje pliki tłumaczeń Qt dla określonego języka.
     * Obsługuje błędy wczytywania plików gracefully i spada na język domyślny.
     *
     * @param language Kod języka ("pl" dla polskiego, "en" dla angielskiego)
     *
     * @see onLanguageChanged()
     */
    void loadLanguage(const QString &language);

    /**
     * @brief Obsłuż zdarzenia zmian Qt (głównie zmiany języka)
     *
     * Nadpisana z QMainWindow aby obsłużyć dynamiczne przełączanie języka.
     * Automatycznie retłumaczy elementy UI gdy wykryta jest zmiana języka.
     *
     * @param event Obiekt zdarzenia zmian Qt
     *
     * @see onLanguageChanged()
     */
    void changeEvent(QEvent* event) override;

    /**
     * @brief Inicjalizuj etykiety UI z tłumaczeniami i ikonami
     *
     * Konfiguruje wszystkie widoczne dla użytkownika etykiety z odpowiednimi tłumaczeniami i
     * osadzonymi ikonami. Wywoływana podczas inicjalizacji i po zmianach języka.
     *
     * @see getTranslatedLabelWithIcon()
     * @see onLanguageChanged()
     */
    void setupLabels();

    /**
     * @brief Generuj etykietę HTML z osadzoną ikoną
     *
     * Tworzy tekst etykiety sformatowany HTML który zawiera osadzoną ikonę
     * wraz z tłumaczonym tekstem. Używana do spójnego stylowania wizualnego
     * w całej aplikacji.
     *
     * @param text Tłumaczony tekst etykiety
     * @param iconPath Ścieżka zasobu do pliku ikony
     * @param width Szerokość ikony w pikselach (domyślnie: 40)
     * @param height Wysokość ikony w pikselach (domyślnie: 40)
     * @return Ciąg sformatowany HTML z ikoną i tekstem
     *
     * @see setupLabels()
     */
    QString getTranslatedLabelWithIcon(const QString& text, const QString& iconPath,
                                       int width = 40, int height = 40);
};

#endif // MAINWINDOW_H
