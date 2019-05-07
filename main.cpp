#include <iostream>
#include <cmath>
#include <memory>
#include <deque>

#include "header.h"

int main() {
    const int choices = 4;
    std::deque<ShipPImpl *> Kolejka1 = {};
    std::deque<ShipPImpl *> Kolejka2 = {};

    int x, y;
    std::cout << "Podaj szerokosc planszy: ";
    std::cin >> x;
    std::cout << "Podaj wysokosc planszy: ";
    std::cin >> y;
    auto *MapaInt = new IntGrid(x, y);
    auto *MapaPimpl = new PimplGrid(x, y);
    auto *liczby = new int[choices];
    for (int i = 1; i <= choices; i++) {
        std::cout << "\nPodaj liczbe " << i << "-masztowcow : ";
        std::cin >> liczby[i - 1];
    }
    for (int i = 0; i < choices; i++) {
        for (int j = 0; j < liczby[i]; j++) {
            auto temp = new ShipPImpl(i + 1);
            Kolejka1.push_back(temp);
        }
    }
    while (!Kolejka1.empty()) {
        int xPos, yPos, heading;
        ShipPImpl *temp = Kolejka1.front();
        std::cout << "Oto " << temp->getTiles() << "-masztowiec. Gdzie stawiamy?\nPodaj x: ";
        std::cin >> xPos;
        std::cout << "Podaj y: ";
        std::cin >> yPos;
        std::cout << "Podaj kierunek (0 - wschod, 1 - polnoc, 2 - zachod, 3 - poludnie): ";
        std::cin >> heading;
        if (temp->placeAtXY(MapaPimpl, MapaInt, xPos, yPos, heading)) {
            std::cout << "\nSukces!\n";
            MapaPimpl->printGrid();
            Kolejka2.push_front(Kolejka1.front());
            Kolejka1.pop_front();
        } else {
            std::cout << "O nie! Sprobuj ponownie :<\n";
        }
    }
    bool shooting = true;
    int xCoord, yCoord;
    while (shooting) {
        std::cout << "Strzelamy? (Tak - 1, Nie - 0) : ";
        std::cin >> shooting;
        shooting = (bool) shooting;
        if (shooting) {
            MapaPimpl->printGrid(1);
            std::cout << "Podaj wspolrzedne (x y): ";
            std::cin >> xCoord >> yCoord;
            if (MapaPimpl->getValue(xCoord, yCoord)) {
                if (MapaPimpl->getValue(xCoord, yCoord)->shotAtXY(xCoord, yCoord)) {
                    std::cout << "TRAFIONY!\n";
                    if (MapaPimpl->getValue(xCoord, yCoord)->isDead())
                        std::cout << "ZATOPIONY!\n";
                    MapaPimpl->printGrid(1);
                }
            } else
                std::cout << "Nie trafiles :<\n";
        }
    }
    return 0;
}
