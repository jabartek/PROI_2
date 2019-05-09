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

    while (interaction(&shipsNotPlaced, &MapaI, &MapaS));

    ClearQueue(&shipsNotPlaced);

    return 0;
}
