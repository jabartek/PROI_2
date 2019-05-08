//
// Created by Bartek on 08.05.2019.
//

#include "header.h"
#include <deque>

void PlaceShips(std::deque<Ship *> *Pending, std::deque<Ship *> *Placed, IntGrid *IntMap, PimplGrid *ShipMap) {
    int xPos = 0;
    int yPos = 0;
    int shipsPlaced = 0;

    bool yEnd = false;

    while (!Pending->empty()) {
        while (IntMap->getValue(xPos, yPos - 1) == 0) {
            yPos--;
        }
        if (Pending->front()->placeAtXY(ShipMap, IntMap, xPos, yPos, 3)) {
            Placed->push_front(Pending->front());
            Pending->pop_front();
            shipsPlaced++;
            if (shipsPlaced == 4) IntMap->addAtXY(6, 3);
        } else
            xPos++;

        if (xPos >= ShipMap->getXSize() && yEnd) {
            break;
        }
        if (xPos >= ShipMap->getXSize()) {
            xPos = 0;
            while (IntMap->getValue(xPos, yPos) > 0)
                yPos++;
        }
        if (yPos == ShipMap->getYSize()) {
            yEnd = true;
        }
    }
    if (Pending->empty()) {
        return;
    }
    for (int i = 0; i < ShipMap->getXSize(); i++) {
        if (Pending->empty()) break;
        for (int j = 0; j < ShipMap->getYSize(); j++) {
            if (Pending->empty()) break;
            for (int k = 0; k < 3; k += 2) {
                if (Pending->empty()) break;
                if (IntMap->getValue(i, j) == 0) {
                    for (int o = 0; o < Pending->size(); o++) {
                        if (Pending->empty()) break;
                        if (Pending->front()->placeAtXY(ShipMap, IntMap, i, j, k)) {
                            Placed->push_front(Pending->front());
                            Pending->pop_front();
                            break;
                        } else {
                            Pending->push_back(Pending->front());
                            Pending->pop_front();
                        }
                    }
                }
            }
        }
    }
}