#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "datasimulator.h"
#include "/home/maks/WDS/QT_HEX_SERVICE/HEX_Service/sideview.h"
#include"/home/maks/WDS/QT_HEX_SERVICE/HEX_Service/topview.h"
#include "servoanglemanager.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Główne okno aplikacji sterującej hexapodem.
 *
 * Klasa odpowiada za wyświetlanie głównych widoków aplikacji
 * oraz obsługę przycisków nawigacyjnych. Użytkownik może przełączać się
 * pomiędzy widokiem połączenia FM, animacjami, ustawieniami i kątami serw.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor głównego okna.
     * @param parent Wskaźnik do obiektu rodzica (może być nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor głównego okna.
     */
    ~MainWindow();

    /**
     * @brief Funkcja do aktualizacji GUI, kiedy dane o kątach serwomechanizmów są dostępne.
     * @param frame Ramka z danymi o kątach serw.
     */
    void updateServoGUI(const ServoFrame &frame);

private slots:
    /**
     * @brief Przełącza widok na ekran z animacjami ruchów hexapoda.
     */
    void showAnimations();

    /**
     * @brief Przełącza widok na ekran z kątami serwomechanizmów.
     */
    void showServoAngles();

    /**
     * @brief Przełącza widok na ekran ustawień połączenia FM.
     */
    void showConnection();

    /**
     * @brief Przełącza widok na ekran ustawień aplikacji.
     */
    void showSettings();

    /**
     * @brief Slot zmieniający aktywną nogę na podstawie wyboru w QComboBox.
     * @param index Indeks wybranej nogi.
     */
    void onLegSelectionChanged(int index);

private:
    Ui::MainWindow *ui; ///< Wskaźnik na wygenerowany interfejs użytkownika (z `.ui`)
    DataSimulator *simulator;  ///< Instancja symulatora danych
    SideView* sideView;  ///< Widget do wyświetlania jednej nogi w widoku z boku
    QComboBox* comboBoxLegSide;  ///< ComboBox do wyboru nogi w widoku z boku
    TopView* topView;

};

#endif // MAINWINDOW_H
