//
// Created by Bartek on 08.05.2019.
//

#include "header.h"

using namespace std;

int readInt() {
    string temp;
    int value = 0;
    bool error = false;
    do {
        cin >> temp;
        try {
            value = stoi(temp);
            error = false;
        }
        catch (invalid_argument) {
            cout << "\nInvalid input! Try again: ";
            error = true;
        }
    } while (error);

    return value;
}

int readIntFromRange(int minimum, int maximum = INT8_MAX) {
    int result = readInt();
    while (result < minimum or result > maximum) {
        cout << "\nInserted value is out of range. Try again: ";
        result = readInt();
    }
    return result;
}

int gatherX() {
    cout << "Enter desired width of grid: ";
    return readIntFromRange(0);
}

int gatherY() {
    cout << "Enter desired height of grid: ";
    return readIntFromRange(0);
}

int gatherXPos(int m) {
    cout << "Enter desired X coordinate of ship's stern: ";
    return readIntFromRange(0, m);
}

int gatherYPos(int m) {
    cout << "Enter desired Y coordinate of ship's stern: ";
    return readIntFromRange(0, m);
}

int gatherXCoord(int m) {
    cout << "Enter desired X coordinate: ";
    return readIntFromRange(0, m);
}

int gatherYCoord(int m) {
    cout << "Enter desired Y coordinate: ";
    return readIntFromRange(0, m);
}

int gatherHeading() {
    cout << "Enter desired heading of the ship (0 - E, 1 - N, 2 - W, 3 - S): ";
    return readIntFromRange(0, 3);
}

void presentGrid(PimplGrid *map) {
    cout << "\nGrid currently looks like this:\n";
    map->printGrid();
}

void addShips(deque<Ship *> *shipsQueue) {
    for (int i = MAX_SHIP; i >= MIN_SHIP; i--) {
        int temp;
        cout << "How many " << i << "-tile ships do you want in the inventory? ";
        temp = readIntFromRange(0);
        for (int j = 0; j < temp; j++) {
            Ship *tempShip = new Ship(i);
            shipsQueue->push_back(tempShip);
        }
    }
}


void PlaceFromQueue(deque<Ship *> *pending, IntGrid *IntMap, PimplGrid *ShipMap) {
    int action;
    cout << "\nHow do you want ships to be placed? (1 - automatically, 2 - manually)\n";
    action = readIntFromRange(1, 2);
    switch (action) {
        case 1:
            PlaceShips(pending, IntMap, ShipMap);
            presentGrid(ShipMap);
            break;
        case 2:
            PlaceManually(pending, IntMap, ShipMap);
            break;
    }
}

void PlaceManually(std::deque<Ship *> *pending, IntGrid *IntMap, PimplGrid *ShipMap) {
    int action;
    bool exit = false;
    while (!pending->empty() and !exit) {
        cout << "\nCurrent ship is a " << pending->front()->getTiles()
             << "-tile one. Do you want to place it? (1 - Yes, 0 - No (skip), 2 - exit manual placing)\n";
        action = readIntFromRange(0, 2);
        switch (action) {
            case 1:
                int xPos, yPos, heading;
                xPos = gatherXPos(ShipMap->getXSize() - 1);
                yPos = gatherYPos(ShipMap->getXSize() - 1);
                heading = gatherHeading();
                if (TryPlacing(pending->front(), ShipMap, IntMap, xPos, yPos, heading)) {
                    pending->pop_front();
                }
                break;
            case 2:
                exit = true;
                break;
            default:
                pending->push_back(pending->front());
                pending->pop_front();
                break;
        }
    }
}

void RemoveManually(std::deque<Ship *> *pending, IntGrid *IntMap, PimplGrid *ShipMap) {
    int action;
    bool exit = false;
    while (!exit) {
        cout << "\nDo you want to remove a ship from map? (1 - Yes, 0 - No)\n";
        action = readIntFromRange(0, 1);
        switch (action) {
            case 1:
                int xCoord, yCoord;
                xCoord = gatherXCoord(ShipMap->getXSize() - 1);
                yCoord = gatherYCoord(ShipMap->getXSize() - 1);
                if (ShipMap->getValue(xCoord, yCoord) != nullptr) {
                    pending->push_back(ShipMap->getValue(xCoord, yCoord));
                    ShipMap->getValue(xCoord, yCoord)->removeFromMap();
                    cout << "Ship succesfully removed!";
                    presentGrid(ShipMap);
                } else {
                    cout << "No ship at such coordinates, try again!";
                }
                break;
            case 0:
                exit = true;
                break;
        }
    }
}

bool TryPlacing(Ship *toBePlaced, PimplGrid *ShipMap, IntGrid *IntMap, int xPos, int yPos, int heading) {
    if (toBePlaced->placeAtXY(ShipMap, IntMap, xPos, yPos, heading)) {
        cout << "Ship succesfully placed at x: " << xPos << ", y: " << yPos;
        presentGrid(ShipMap);
        return 1;
    } else {
        cout << "Placing at x: " << xPos << ", y: " << yPos << " failed. Try some other place";
        return 0;
    }
}

void AnalyzeNotPlaced(std::deque<Ship *> *pending) {
    int sum = 0;
    int *tab = new int[MAX_SHIP];
    for (int i = 0; i < MAX_SHIP; i++) {
        tab[i] = 0;
    }
    for (unsigned int i = 0; i < pending->size(); i++) {
        if (pending->front()->getTiles() <= MAX_SHIP)
            tab[pending->front()->getTiles() - 1]++;
        sum++;
        pending->push_back(pending->front());
        pending->pop_front();
    }
    cout << "\nThose ships have not been placed: ";
    for (int i = 0; i < MAX_SHIP; i++) {
        cout << tab[i] << " " << i + 1 << "-mast ones, ";
    }
    cout << " for a total of " << sum;
    delete[] tab;
}

void ClearQueue(std::deque<Ship *> *toBeCleared) {
    while (!toBeCleared->empty()) {
        delete toBeCleared->front();
        toBeCleared->pop_front();
    }
};

bool interaction(deque<Ship *> *shipsNotPlaced, IntGrid *MapaI, PimplGrid *MapaS) {
    cout
            << "\nWhich action do you want to take?\n1 - Display the map\n2 - Add ships to queue\n3 - Place ships from queue\n4 - Display a report about ships in queue\n5 - Remove ships from map\n6 - Clear queue\n0 - Exit\n";
    bool toContinue = true;
    int action = readIntFromRange(0, 6);
    switch (action) {
        case 1:
            presentGrid(MapaS);
            break;
        case 2:
            addShips(shipsNotPlaced);
            break;
        case 3:
            PlaceFromQueue(shipsNotPlaced, MapaI, MapaS);
            break;
        case 4:
            AnalyzeNotPlaced(shipsNotPlaced);
            break;
        case 5:
            RemoveManually(shipsNotPlaced, MapaI, MapaS);
            break;
        case 6:
            ClearQueue(shipsNotPlaced);
            break;
        default:
            toContinue = false;
    }
    return toContinue;
}