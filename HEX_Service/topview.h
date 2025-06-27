/**
 * @file topview.h
 * @brief Wizualizacja widoku z góry kompletnego robota hexapod
 * @author Maksymilian Tulewicz
 * @date 2025
 * @version 1.0
 */

#ifndef TOPVIEW_H
#define TOPVIEW_H

#include <QWidget>

/**
 * @brief Widget wizualizacji z lotu ptaka pokazujący kompletną postawę robota hexapod
 *
 * TopView zapewnia widok z lotu ptaka robota hexapod, wyświetlając
 * orientację wszystkich sześciu nóg jednocześnie. Ta wizualizacja jest istotna
 * dla zrozumienia ogólnej postawy robota, wzorców chodu i koordynacji
 * między nogami podczas ruchu.
 *
 * ## Funkcje wizualizacji:
 * - **Kompletny przegląd robota** ze wszystkimi 6 nogami widocznymi
 * - **Proporcjonalna reprezentacja ciała** jako centralne ciało kołowe
 * - **Indywidualne wyświetlanie kąta biodra** dla każdej nogi
 * - **Realistyczne pozycjonowanie nóg** na podstawie rzeczywistej geometrii hexapoda
 * - **Aktualizacje w czasie rzeczywistym** zsynchronizowane z feedbackiem serwomechanizmów
 * - **Wysokiej jakości renderowanie** z antyaliasingiem i płynnymi liniami
 *
 * ## Geometria robota:
 * Hexapod używa standardowej konfiguracji 6-nogiej:
 * ```
 *     Przód
 *   1 ----- 2
 *  /         \
 * 3           4
 *  \         /
 *   5 ----- 6
 *     Tył
 * ```
 *
 * ## Konwencje kąta biodra:
 * - **Orientacje bazowe**: Każda noga ma predefiniowany kierunek bazowy
 * - **Kąty serwomechanizmów**: 0° do 180° typowy zakres serwomechanizmu
 * - **Kąty wyświetlania**: Kąt serwomechanizmu - 90° aby wyśrodkować wokół kierunku bazowego
 * - **Obrót**: Dodatnie kąty obracają zgodnie z ruchem wskazówek zegara od pozycji bazowej
 *
 * ## Orientacje bazowe (w stopniach):
 * - Noga 0 (Przód-Lewa): 225° (SW)
 * - Noga 1 (Środek-Lewa): 270° (W)
 * - Noga 2 (Tył-Lewa): 315° (NW)
 * - Noga 3 (Tył-Prawa): 45° (NE)
 * - Noga 4 (Środek-Prawa): 90° (E)
 * - Noga 5 (Przód-Prawa): 135° (SE)
 *
 * @see SideView
 * @see MainWindow::updateServoGUI()
 *
 * Przykład użycia:
 * @code
 * TopView *widokZGory = new TopView(parent);
 *
 * // Ustaw kąty bioder dla chodu chodzenia
 * for (int noga = 0; noga < 6; ++noga) {
 *     float kat = obliczKatChodzenia(noga, czas);
 *     widokZGory->setHipAngle(noga, kat);
 * }
 * @endcode
 */
class TopView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor - Inicjalizuje widget widoku z góry
     *
     * Tworzy widget widoku z góry ze wszystkimi nogami zainicjalizowanymi do ich
     * orientacji bazowych (pozycja serwomechanizmu 90°). Ustawia system
     * współrzędnych i parametry renderowania.
     *
     * @param parent Rodzic widget do zarządzania pamięcią
     */
    explicit TopView(QWidget *parent = nullptr);

    /**
     * @brief Ustaw kąt biodra dla indywidualnej nogi
     *
     * Aktualizuje kąt biodra dla określonej nogi i wyzwala aktualizację wizualną.
     * Kąt jest interpretowany jako pozycja serwomechanizmu (0-180°) i konwertowany
     * do odpowiedniej orientacji wyświetlania.
     *
     * @param legIndex Numer nogi (0-5)
     * @param angleDeg Kąt serwomechanizmu biodra w stopniach (typowy zakres: 0-180°)
     *
     * @note Nieprawidłowe indeksy nóg są ignorowane cicho
     * @note Wartości kątów poza 0-180° są akceptowane ale mogą wyglądać niezwykle
     * @note Widget automatycznie przemalowuje się gdy kąty się zmieniają
     *
     * Interpretacja kąta:
     * - 0° = Maksymalny obrót przeciwny do ruchu wskazówek zegara
     * - 90° = Pozycja neutralna (wyrównana z orientacją bazową)
     * - 180° = Maksymalny obrót zgodny z ruchem wskazówek zegara
     */
    void setHipAngle(int legIndex, float angleDeg);

protected:
    /**
     * @brief Renderuj kompletną wizualizację robota
     *
     * Niestandardowa implementacja paint która rysuje ciało robota i wszystkie sześć
     * nóg z ich aktualnymi orientacjami bioder. Używa adaptacyjnego skalowania
     * na podstawie wymiarów widgetu.
     *
     * @param e Zdarzenie paint (nieużywane)
     *
     * @note Wywoływana automatycznie przez Qt gdy widget potrzebuje przemalowania
     * @note Renderowanie skaluje się automatycznie z rozmiarem widgetu
     * @note Używa wysokiej jakości rysowania antyaliasowego dla płynnego wyglądu
     */
    void paintEvent(QPaintEvent *e) override;

private:
    float hipAngles[6];                                           /**< Aktualne kąty bioder dla wszystkich 6 nóg */
    static constexpr float kBase[6] = {225, 270, 315, 45, 90, 135}; /**< Orientacje bazowe dla każdej nogi w stopniach */
};

#endif // TOPVIEW_H
