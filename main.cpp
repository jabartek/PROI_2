#include <iostream>
#include <cmath>
#include <memory>
#include <deque>

#include "header.h"

using namespace std;


int main() {
    int xSize, ySize;

    deque<Ship *> shipsNotPlaced = {};


    xSize = gatherX();
    ySize = gatherY();

    IntGrid MapaI(xSize, ySize);
    PimplGrid MapaS(xSize, ySize);

    presentGrid(&MapaS);

    addShips(&shipsNotPlaced);
    PlaceFromQueue(&shipsNotPlaced, &MapaI, &MapaS);
    AnalyzeNotPlaced(&shipsNotPlaced);
    RemoveManually(&shipsNotPlaced, &MapaI, &MapaS);

    DestroyNotPlaced(&shipsNotPlaced);

    return 0;
}
