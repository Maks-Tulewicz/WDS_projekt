/**
 * @file sideview.h
 * @brief Wizualizacja widoku bocznego pojedynczej nogi hexapoda
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef SIDEVIEW_H
#define SIDEVIEW_H

#include <QWidget>
#include <QPainter>

/**
 * @brief Widget wizualizacji widoku bocznego dla szczegółowego badania nogi
 *
 * SideView zapewnia szczegółową wizualizację 2D pojedynczej nogi hexapoda
 * z perspektywy bocznej. Pokazuje łańcuch kinematyczny nogi z
 * dokładnymi pozycjami i orientacjami stawów na podstawie kątów serwomechanizmów.
 *
 * ## Funkcje wizualizacji:
 * - **Anatomicznie poprawne proporcje** z realistycznymi długościami segmentów
 * - **Animacja stawów w czasie rzeczywistym** na podstawie feedbacku serwomechanizmów
 * - **Stawy oznaczone kolorami** dla łatwej identyfikacji (czerwony=kolano, niebieski=kostka)
 * - **Stałe odniesienie ciała** pokazujące punkt przyłączenia nogi
 * - **Płynne renderowanie** z antialiasingiem dla profesjonalnego wyglądu
 *
 * ## Model kinematyczny:
 * Model nogi używa uproszczonej reprezentacji 2-DOF (Stopnie Swobody):
 * - **Segment uda**: Od biodra do kolana (80 pikseli długości)
 * - **Segment goleni**: Od kolana do kostki (160 pikseli długości, stosunek 2:1)
 * - **Staw biodra**: Stały punkt przyłączenia (nie wizualizowany)
 * - **Staw kolana**: Główny punkt artykulacji (czerwony wskaźnik)
 * - **Staw kostki**: Orientacja efektora końcowego (niebieski wskaźnik)
 *
 * ## System współrzędnych:
 * - **Początek**: Punkt przyłączenia biodra (środek-lewa część widgetu)
 * - **Zero stopni**: Wskazujący w górę (pozycja 12:00)
 * - **Dodatni obrót**: Zgodnie z ruchem wskazówek zegara od pozycji zerowej
 * - **Interpretacja kąta**: 90° = poziomo, 180° = w dół
 *
 * @see TopView
 * @see MainWindow::onLegSelectionChanged()
 *
 * Przykład użycia:
 * @code
 * SideView *widokBoczny = new SideView(parent);
 * widokBoczny->setActiveLeg(2);           // Wybierz nogę 3 do wyświetlenia
 * widokBoczny->setJointAngles(45, 120);   // Ustaw kolano=45°, kostka=120°
 * @endcode
 */
class SideView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor - Inicjalizuje widget widoku bocznego
     *
     * Tworzy widget widoku bocznego z domyślnymi ustawieniami i początkową
     * pozą. Ustawia stały rozmiar widgetu zoptymalizowany dla wizualizacji nogi.
     *
     * @param parent Rodzic widget do zarządzania pamięcią
     */
    explicit SideView(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Wybierz którą nogę wyświetlić
     *
     * Zmienia aktywną nogę będącą wizualizowaną. To pozwala użytkownikowi
     * badać każdą z 6 nóg indywidualnie dla szczegółowej analizy.
     *
     * @param leg Indeks nogi (0-5, odpowiadający nogom 1-6)
     *
     * @note Wybór nogi wpływa tylko na etykietę wyświetlania, nie na wizualizację
     * @note Kąty stawów pozostają niezmienione przy przełączaniu nóg
     * @note Nieprawidłowe numery nóg są ignorowane cicho
     */
    void setActiveLeg(int leg);

    /**
     * @brief Aktualizuj kąty stawów dla wizualizacji w czasie rzeczywistym
     *
     * Ustawia kąty stawów kolana i kostki dla obecnie aktywnej nogi.
     * Wizualizacja jest natychmiast aktualizowana aby odzwierciedlić nową pozę.
     * Kąty stawów są interpretowane zgodnie z konwencjami robota.
     *
     * @param knee Kąt stawu kolana w stopniach (0° = prosto w górę, 90° = poziomo)
     * @param ankle Kąt stawu kostki w stopniach (względem segmentu goleni)
     *
     * @note Kąty nie są ograniczane zakresem; ekstremalne wartości mogą produkować niezwykłe pozy
     * @note Widget automatycznie przemalowuje się gdy kąty się zmieniają
     *
     * Przykładowe typowe zakresy:
     * - Kolano: 30° do 120° (zgięte do wyprostowane)
     * - Kostka: 90° do 270° (do przodu do tyłu)
     */
    void setJointAngles(float knee, float ankle);

protected:
    /**
     * @brief Renderuj wizualizację nogi
     *
     * Niestandardowa implementacja paint która rysuje kompletną strukturę nogi
     * włączając przyłączenie ciała, udo, goleń i wskaźniki stawów.
     * Używa wysokiej jakości renderowania z antyaliasingiem.
     *
     * @param event Zdarzenie paint (nieużywane)
     *
     * @note Wywoływana automatycznie przez Qt gdy widget potrzebuje przemalowania
     * @note Rysowanie jest zoptymalizowane dla płynnych aktualizacji w czasie rzeczywistym
     */
    void paintEvent(QPaintEvent *event) override;

private:
    int activeLeg = 0;         /**< Obecnie wybrany indeks nogi (0-5) */
    float kneeAngle = 0.f;     /**< Aktualny kąt stawu kolana w stopniach */
    float ankleAngle = 0.f;    /**< Aktualny kąt stawu kostki w stopniach */
};

#endif // SIDEVIEW_H
