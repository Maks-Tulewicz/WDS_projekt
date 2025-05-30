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
 * @brief Główne okno aplikacji sterującej hexapodem.
 *
 * Klasa odpowiada za wyświetlanie głównych widoków aplikacji,
 * obsługę nawigacji między ekranami oraz przetwarzanie i wyświetlanie danych.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor głównego okna.
     * @param parent Wskaźnik do obiektu rodzica (domyślnie nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
 * @brief Aktualizuje wszystkie QLabel-e kątów.
 * @param frame  Struktura z czasem i wektorem kątów, prędkości i licznikiem pakietów.
 */
    void updateServoGUI(const ServoFrame &frame);



private slots:
    /** @brief Pokazuje widok animacji */
    void showAnimations();

    /** @brief Pokazuje widok kątów serw */
    void showServoAngles();

    /** @brief Pokazuje widok jakości połączenia FM */
    void showConnection();

    /** @brief Pokazuje widok ustawień aplikacji */
    void showSettings();

    /** @brief Zmieniona aktywna noga w SideView */
    void onLegSelectionChanged(int index);

    /** @brief Loguje komunikat błędu do systemu
        @param msg Treść komunikatu błędu */
    void logError(const QString &msg);

    /** @brief Obsługuje i formatuje komunikat błędu
        @param msg Treść komunikatu błędu */
    void handleLogError(const QString &msg);

    /** @brief Obsługuje i formatuje standardową wiadomość
        @param msg Treść wiadomości */
    void handleLogMessage(const QString &msg);

    /** @brief Obsługuje zmianę języka interfejsu
        @param index Indeks wybranego języka */
    void onLanguageChanged(int index);



private:
    Ui::MainWindow *ui;               ///< Wskaźnik na wygenerowany interfejs UI
    DataSimulator *simulator;         ///< Symulator strumienia danych
    ServoAngleManager *servoManager;  ///< Manager aktualizacji QLabeli kątów
    SideView *sideView;              ///< Widget bocznego widoku nogi
    TopView *topView;                ///< Widget widoku z góry całego robota
    QComboBox *comboBoxLegSide;      ///< Dropdown wyboru nogi w widoku bocznym
    QTranslator *translator;          ///< Obiekt tłumacza interfejsu

    /** @brief Pomocnicza funkcja do logowania w terminalu
        @param message Treść wiadomości */
    void logToTerminal(const QString &message);

    /** @brief Obsługuje zdarzenie rozłączenia symulatora */
    void onSimDisconnect();

    /** @brief Obsługuje zdarzenie ponownego połączenia */
    void onReconnectClicked();

    /** @brief Wczytuje wybrany język interfejsu
        @param language Kod języka */
    void loadLanguage(const QString &language);

    /** @brief Obsługuje zdarzenia zmiany stanu
        @param event Obiekt zdarzenia */
    void changeEvent(QEvent* event) override;

    /** @brief Inicjalizuje etykiety interfejsu */
    void setupLabels();

    /** @brief Dodaje ikonę do etykiety tekstowej
        @param text Tekst etykiety
        @param iconPath Ścieżka do pliku ikony
        @param width Szerokość ikony
        @param height Wysokość ikony
        @return Tekst HTML z ikoną */
    QString getTranslatedLabelWithIcon(const QString& text, const QString& iconPath,
                                       int width = 40, int height = 40);
};

#endif // MAINWINDOW_H
