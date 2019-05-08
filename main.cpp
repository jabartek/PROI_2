#include <iostream>
#include <cmath>
#include <memory>
#include <deque>

#include "header.h"

using namespace std;


int main() {
    int m, n;
    cin >> m >> n;
    IntGrid *MapaI = new IntGrid(m, n);
    PimplGrid *MapaS = new PimplGrid(m, n);
    deque<Ship *> kolejka1 = {};
    deque<Ship *> kolejka2 = {};
    int x1, x2, x3, x4;
    cin >> x1 >> x2 >> x3 >> x4;
    for (int i = 0; i < x1; i++) {
        Ship *temp = new Ship(1);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < x2; i++) {
        Ship *temp = new Ship(2);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < x3; i++) {
        Ship *temp = new Ship(3);
        kolejka1.push_front(temp);
    }
    for (int i = 0; i < x4; i++) {
        Ship *temp = new Ship(4);
        kolejka1.push_front(temp);
    }

    PlaceShips(&kolejka1, &kolejka2, MapaI, MapaS);

    MapaS->printGrid();;


    return 0;
}
