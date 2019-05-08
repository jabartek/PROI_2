//
// Created by Bartek on 07.05.2019.
//

#ifndef STATKI_PIMPL_SHIPPIMPL_H
#define STATKI_PIMPL_SHIPPIMPL_H

#include <iostream>
#include <cmath>
#include <memory>
#include <deque>
#include <string>
#include <stdexcept>


#define MIN_SHIP 1
#define MAX_SHIP 4

class Ship;

class ShipImpl;

template<class T>
class GridTemplate {
public:
    GridTemplate(int, int);

    GridTemplate();

    virtual ~GridTemplate();

    GridTemplate(const GridTemplate &other);

    GridTemplate &operator=(const GridTemplate &other);

    T getValue(int, int);

    void setValue(T, int, int);

    void clearTile(int, int);

    inline int getXSize() { return xSize_; };

    inline int getYSize() { return ySize_; };

    void addAtXY(int, int);

    void subAtXY(int, int);

    void printGrid();

    void printGrid(int);

private:
    void allocation();

    int xSize_;
    int ySize_;
    T **tiles_;
};

typedef GridTemplate<Ship *> PimplGrid;
typedef GridTemplate<int> IntGrid;

class Ship {
public:

    explicit Ship(int);

    Ship();

    ~Ship();

    bool placeAtXY(PimplGrid *, IntGrid *, int, int, int);

    void removeFromMap();

    int shotAtXY(int, int);

    int shotAtTile(int);

    int getTiles();

    bool isDead();

    char renderTile(int, int param = 0);

    char renderXY(int, int, int param = 0);

private:
    const ShipImpl *pImpl() const { return pImpl_.get(); }

    ShipImpl *pImpl() { return pImpl_.get(); }

    std::unique_ptr<ShipImpl> pImpl_;

};

//placer.cpp
//void PlaceShips(std::deque<Ship *>*, std::deque<Ship *>*, IntGrid *, PimplGrid*);
void PlaceShips(std::deque<Ship *> *, IntGrid *, PimplGrid *);

//interface.cpp
int readInt();

int readIntFromRange(int, int);

int gatherX();

int gatherY();

int gatherXCoord(int);

int gatherYCoord(int);

int gatherHeading();

int gatherXPos(int);

int gatherYPos(int);

void presentGrid(PimplGrid *);

void addShips(std::deque<Ship *> *);

void PlaceFromQueue(std::deque<Ship *> *, IntGrid *, PimplGrid *);

void PlaceManually(std::deque<Ship *> *, IntGrid *, PimplGrid *);

bool TryPlacing(Ship *, PimplGrid *, IntGrid *, int, int, int);

void RemoveManually(std::deque<Ship *> *, IntGrid *, PimplGrid *);

void AnalyzeNotPlaced(std::deque<Ship *> *);

void DestroyNotPlaced(std::deque<Ship *> *);


#endif //STATKI_PIMPL_SHIPPIMPL_H
