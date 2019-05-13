# Statki 1

Celem programu jest realizacja interfejsu reprezentującego statek w grze w statki. Poniżej znajduje się opis poszczególnych plików:
## Makefile
Jest to plik dla programu make. Zrealizowany w sposób uniwersalny tak, by załadować wszystkie pliki .cpp ze swojego folderu. 
## main.cpp
Jest to plik w ramach którego wykonywany jest program. Oparty jest wyłącznie na procedurach z interface.cpp i to tu tworzone są wskaźniki na dane użyte w ramach realizacji.
## interface.cpp
Realizacja funkcji i procedur koniecznych do wyświetlenia interfejsu użytkownika. Korzysta wyłącznie z funkcji własnych i tych zrealizowanych w ramach realizacja.cpp 
## placer.cpp
Naiwnie zrealizowany algorytm stawiania statków na planszy. Stara się wypełniać ją początkowo statkami pionowymi, by następnie zapełnić poziomymi. Ze względu na brak obostrzeń miewa problemy przy niepustej planszy na początku działania. Wymaga poprawy dla stabilnej funkcjonalności.
## realizacja.cpp
Zawiera realizację klasy Ship oraz GridTemplate, które odpowiednio reprezentują statek oraz planszę. Realizacja klasy GridTempate wykorzystuje szablony, a klasy Ship technikę _pointer to implementation_
## header.h
Zawiera prototypy wszystkich wykorzystanych w programie funkcji.
