//
// Created by Bartek on 07.05.2019.
//

#ifndef STATKI_PIMPL_SHIPPIMPL_H
#define STATKI_PIMPL_SHIPPIMPL_H

#include <iostream>
#include <cmath>
#include <memory>
#include <deque>

#define CHOICES 4

class ShipPImpl;

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

typedef GridTemplate<ShipPImpl *> PimplGrid;
typedef GridTemplate<int> IntGrid;

class ShipPImpl {
public:

    ShipPImpl(int);

    ShipPImpl();

    ~ShipPImpl();

    ShipPImpl(const ShipPImpl &);

    //ShipPImpl& operator=(const ShipPImpl& );

    bool placeAtXY(PimplGrid *, IntGrid *, int, int, int);

    void removeFromMap();

    int shotAtXY(int, int);

    int shotAtTile(int);

    int getTiles();

    bool isDead();

    char renderTile(int, int param = 0);

    char renderXY(int, int, int param = 0);

private:
    class Impl;

    Impl *pImpl;

};


#endif //STATKI_PIMPL_SHIPPIMPL_H
