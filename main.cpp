#include <iostream>
#include <cmath>
#include <memory>
#include <deque>

#include "header.h"

using namespace std;


int main() {
    IntGrid *MapaI = new IntGrid(7, 5);
    PimplGrid *MapaS = new PimplGrid(7, 5);
    deque<Ship *> kolejka1 = {};
    deque<Ship *> kolejka2 = {};
    for (int i = 0; i < 0; i++) {
        Ship *temp = new Ship(1);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < 2; i++) {
        Ship *temp = new Ship(2);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < 1; i++) {
        Ship *temp = new Ship(3);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < 2; i++) {
        Ship *temp = new Ship(4);
        kolejka1.push_front(temp);
    }

    PlaceShips(&kolejka1, &kolejka2, MapaI, MapaS);

    MapaS->printGrid();;

    delete MapaS;
    while (!kolejka1.empty()) {
        std::cout << "M";
        delete kolejka1.front();
        kolejka1.pop_front();
    }
    while (!kolejka2.empty()) {
        std::cout << "N";
        delete kolejka2.front();
        kolejka2.pop_front();
    }

    return 0;
}
