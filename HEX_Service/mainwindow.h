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
    void showAnimations(); /**< Pokaż widok animacji. */
    void showServoAngles(); /**< Pokaż widok kątów serw. */
    void showConnection(); /**< Pokaż widok jakości połączenia FM. */
    void showSettings(); /**< Pokaż widok ustawień aplikacji. */
    void onLegSelectionChanged(int index); /**< Zmieniona aktywna noga w SideView. */
    void logError(const QString &msg);
    void handleLogError(const QString &msg);
    void handleLogMessage(const QString &msg);
    void onLanguageChanged(int index);

private:
    Ui::MainWindow *ui;               ///< Wskaźnik na wygenerowany interfejs UI
    DataSimulator *simulator;         ///< Symulator strumienia danych
    ServoAngleManager *servoManager;  ///< Manager aktualizacji QLabeli kątów
    SideView *sideView;               ///< Widget bocznego widoku nogi
    TopView *topView;                 ///< Widget widoku z góry całego robota
    QComboBox *comboBoxLegSide;       ///< Dropdown wyboru nogi w widoku bocznym
    void logToTerminal(const QString &message); ///< pomocnicza funkcja do logowania
    void onSimDisconnect();
    void onReconnectClicked();
    void loadLanguage(const QString &language);
    void changeEvent(QEvent* event) override;
    QTranslator *translator;

};

#endif // MAINWINDOW_H
