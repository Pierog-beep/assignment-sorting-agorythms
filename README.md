# Algorytmy sortujące

## Opis

### Algorytm sortowania przez kopcowanie

Heap Sort wykorzystuje kopiec maksymalny, w którym największy element znajduje się w korzeniu. Algorytm najpierw buduje kopiec, a następnie zamienia jego korzeń z ostatnim elementem i przywraca własność kopca dla pozostałej części tablicy. Sortowanie ma złożoność czasową \(O(n \log n)\) i wykonuje się w miejscu.

### Algorytm szybkiego sortowania

Quick Sort działa na zasadzie „dziel i zwyciężaj”. Wybiera element osiowy (pivot), dzieli tablicę na elementy mniejsze lub równe pivotowi oraz większe, a następnie rekurencyjnie sortuje obie części. Średnia złożoność czasowa wynosi \(O(n \log n)\), natomiast w najgorszym przypadku \(O(n^2)\).

### Algorytm sortowania Shell'a

Shell Sort jest rozszerzeniem sortowania przez wstawianie – porównuje elementy oddalone od siebie o określony odstęp (*gap*), który stopniowo zmniejsza do 1. Program udostępnia dwa warianty: `shell_s`, wykorzystujący odstępy dzielone przez 2, oraz `shell_k`, korzystający z przyrostów Knutha. Wydajność algorytmu zależy od zastosowanego ciągu odstępów.

## Działanie

### Komendy

Program obsługuje liczby całkowite (`int`) i zmiennoprzecinkowe (`float`). Dostępne polecenia:

| Komenda | Opis |
|---|---|
| `generate <type> <min> <max> <size>` | Generuje losową listę o podanym zakresie wartości i rozmiarze. |
| `generate custom <type> <min> <max> <size> <threshold> <order>` | Generuje listę częściowo lub całkowicie uporządkowaną. |
| `load <type> <filename>` | Wczytuje listę z pliku. |
| `show <type>` | Wyświetla aktualnie przechowywaną listę. |
| `sort <algorithm> <type>` | Sortuje listę wybranym algorytmem. |
| `test <algorithm> <size> <repetitions>` | Uruchamia test wydajności algorytmu. |
| `quit` | Kończy działanie programu. |

Dostępne algorytmy: `heap`, `quick`, `shell_s`, `shell_k`.

### Generowanie listy

Aby wygenerować losową listę, należy podać typ danych, minimalną i maksymalną wartość oraz liczbę elementów. Przykładowo:

```bash
generate int 0 100 1000
```

Możliwe jest również wygenerowanie listy częściowo uporządkowanej:

```bash
generate custom float 0 100 1000 0.66 ASC
```

Parametr `threshold` określa część listy przeznaczoną do uporządkowania (wartość od 0 do 1), a `order` wskazuje kierunek: `ASC` – rosnąco lub `DESC` – malejąco.

### Ładowanie list

Listę można wczytać z pliku, podając jej typ oraz nazwę pliku:

```bash
load int dane.txt
```

Program zapisuje wczytaną listę w pamięci i udostępnia ją do wyświetlenia lub sortowania.

### Sortowanie

Do sortowania aktualnie przechowywanej listy służy komenda:

```bash
sort quick int
```

Pierwszy argument określa algorytm, a drugi typ listy. Dostępne algorytmy to `heap`, `quick`, `shell_s` i `shell_k`. Po zakończeniu sortowania program wyświetla czas wykonania w nanosekundach i milisekundach.

### Testowanie

Test wydajności uruchamia się poleceniem:

```bash
test heap 10000 5
```

Argumenty oznaczają kolejno: algorytm sortujący, rozmiar testowanych list oraz liczbę powtórzeń. Program mierzy czas sortowania list typu `int` i `float` dla czterech rodzajów danych: losowych, częściowo uporządkowanych, malejących i rosnących. Po każdym sortowaniu sprawdzana jest poprawność wyniku, a na końcu prezentowane są średnie czasy wykonania w milisekundach.
