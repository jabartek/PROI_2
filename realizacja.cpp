//
// Created by Bartek on 07.05.2019.
//

#include "header.h"

template<class T>
GridTemplate<T>::GridTemplate(int xSize, int ySize) : xSize_(xSize), ySize_(ySize) {
    allocation();
    for (int i = 0; i < ySize_; i++) {
        for (int j = 0; j < xSize_; j++) {
            tiles_[i][j] = (T) 0;
        }
    }
}

template<class T>
GridTemplate<T>::GridTemplate():xSize_(1), ySize_(1) {
    allocation();
}


template<class T>
GridTemplate<T>::~GridTemplate() {
    //dtor
}

template<class T>
GridTemplate<T>::GridTemplate(const GridTemplate &other) {
    //copy ctor
}

template<class T>
GridTemplate<T> &GridTemplate<T>::operator=(const GridTemplate &rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


template<class T>
void GridTemplate<T>::addAtXY(int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
        tiles_[yPos][xPos]++;
}

template<class T>
void GridTemplate<T>::subAtXY(int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
        tiles_[yPos][xPos]--;
}

template<class T>
void GridTemplate<T>::setValue(T value, int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
        tiles_[yPos][xPos] = value;
    }
}

template<>
int GridTemplate<int>::getValue(int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
        return tiles_[yPos][xPos];
    } else return -1;
}

template<>
ShipPImpl *GridTemplate<ShipPImpl *>::getValue(int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
        return (ShipPImpl *) tiles_[yPos][xPos];
    } else return nullptr;
}


template<class T>
void GridTemplate<T>::clearTile(int xPos, int yPos) {
    if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
        tiles_[yPos][xPos] = (T) NULL;
}

template<>
void GridTemplate<int>::printGrid() {
    for (int i = 0; i < ySize_; i++) {
        for (int j = 0; j < xSize_; j++) {
            std::cout << this->getValue(j, i);
        }
        std::cout << std::endl;
    }
}

template<>
void GridTemplate<ShipPImpl *>::printGrid(int param) {
    for (int i = 0; i < ySize_; i++) {
        for (int j = 0; j < xSize_; j++) {

            if (tiles_[i][j]) {
                std::cout << tiles_[i][j]->renderXY(j, i, param);
            } else std::cout << "=";
        }
        std::cout << std::endl;
    }
}

template<>
void GridTemplate<ShipPImpl *>::printGrid() {
    this->printGrid(0);
}


template<class T>
void GridTemplate<T>::allocation() {
    tiles_ = new T *[ySize_];
    for (int i = 0; i < ySize_; i++) {
        tiles_[i] = new T[xSize_];
    }
}


class ShipPImpl::Impl {
public:
    Impl(int tilesNum) : tiles_(tilesNum) {
        allocation();
        placedOnInts_ = nullptr;
        placedOnShip_ = nullptr;
    }

    Impl() : tiles_(0) {
        allocation();
        placedOnInts_ = nullptr;
        placedOnShip_ = nullptr;
    }

    virtual ~Impl() {
        //ehhhhhhh
    };

    Impl(const Impl &);

    //Impl& operator=(const Impl& );
    void removeFromMap(const ShipPImpl *S) {
        if (!isPlaced_)
            return;
        switch (heading_) {
            case 0:
                for (int i = -1; i <= tiles_; i++) {
                    for (int j = -1; j <= 1; j++) {
                        placedOnInts_->subAtXY(headX_ + i, headY_ + j);
                        if (placedOnShip_->getValue(i, j) == S) placedOnShip_->clearTile(i, j);
                    }
                }
                headX_ = -1;
                headY_ = -1;
                heading_ = -1;
                isPlaced_ = false;
                placedOnInts_ = nullptr;
                placedOnShip_ = nullptr;
                break;
            case 1:
                for (int i = -1; i <= tiles_; i++) {
                    for (int j = -1; j <= 1; j++) {
                        placedOnInts_->subAtXY(headX_ + j, headY_ - i);
                        if (placedOnShip_->getValue(i, j) == S) placedOnShip_->clearTile(i, j);
                    }
                }
                headX_ = -1;
                headY_ = -1;
                heading_ = -1;
                isPlaced_ = false;
                placedOnInts_ = nullptr;
                placedOnShip_ = nullptr;
                break;
            case 2:
                for (int i = -1; i <= tiles_; i++) {
                    for (int j = -1; j <= 1; j++) {
                        placedOnInts_->subAtXY(headX_ - i, headY_ + j);
                        if (placedOnShip_->getValue(i, j) == S) placedOnShip_->clearTile(i, j);
                    }
                }
                headX_ = -1;
                headY_ = -1;
                heading_ = -1;
                isPlaced_ = false;
                placedOnInts_ = nullptr;
                placedOnShip_ = nullptr;
                break;
            case 3:
                for (int i = -1; i <= tiles_; i++) {
                    for (int j = -1; j <= 1; j++) {
                        placedOnInts_->subAtXY(headX_ + j, headY_ + i);
                        if (placedOnShip_->getValue(i, j) == S) placedOnShip_->clearTile(i, j);
                    }
                }
                headX_ = -1;
                headY_ = -1;
                heading_ = -1;
                isPlaced_ = false;
                placedOnInts_ = nullptr;
                placedOnShip_ = nullptr;
                break;
        }
    }

    bool placeAtXY(PimplGrid *shipGrid, IntGrid *intGrid, int xPos, int yPos, int heading, const ShipPImpl *S) {
        if (isPlaced_) removeFromMap(S);
        bool ifValid = false;
        if (intGrid->getValue(xPos, yPos) != 0)
            return 0;
        switch (heading) {
            default:
                for (int i = 0; i < tiles_; i++) {
                    if (intGrid->getValue(xPos + i, yPos) != 0) {
                        ifValid = false;
                        break;
                    } else ifValid = true;
                }
                if (ifValid) {
                    headX_ = xPos;
                    headY_ = yPos;
                    heading_ = heading;
                    isPlaced_ = true;
                    placedOnShip_ = shipGrid;
                    placedOnInts_ = intGrid;
                    for (int i = -1; i <= tiles_; i++) {
                        for (int j = -1; j <= 1; j++) {
                            intGrid->addAtXY(xPos + i, yPos + j);
                        }
                    }
                    for (int i = 0; i < tiles_; i++) {
                        shipGrid->setValue((ShipPImpl *) S, xPos + i, yPos);
                    }
                }
                break;
            case 1:
                for (int i = 0; i < tiles_; i++) {
                    if (intGrid->getValue(xPos, yPos - i) != 0) {
                        ifValid = false;
                        break;
                    } else ifValid = true;
                }
                if (ifValid) {
                    headX_ = xPos;
                    headY_ = yPos;
                    heading_ = heading;
                    isPlaced_ = true;
                    placedOnShip_ = shipGrid;
                    placedOnInts_ = intGrid;
                    for (int i = -1; i <= tiles_; i++) {
                        for (int j = -1; j <= 1; j++) {
                            intGrid->addAtXY(xPos + j, yPos - i);
                        }
                    }
                    for (int i = 0; i < tiles_; i++) {
                        shipGrid->setValue((ShipPImpl *) S, xPos, yPos - i);
                    }
                }
                break;
            case 2:
                for (int i = 0; i < tiles_; i++) {
                    if (intGrid->getValue(xPos - i, yPos) != 0) {
                        ifValid = false;
                        break;
                    } else ifValid = true;
                }
                if (ifValid) {
                    headX_ = xPos;
                    headY_ = yPos;
                    heading_ = heading;
                    isPlaced_ = true;
                    placedOnShip_ = shipGrid;
                    placedOnInts_ = intGrid;
                    for (int i = -1; i <= tiles_; i++) {
                        for (int j = -1; j <= 1; j++) {
                            intGrid->addAtXY(xPos - i, yPos + j);
                        }
                    }
                    for (int i = 0; i < tiles_; i++) {
                        shipGrid->setValue((ShipPImpl *) S, xPos - i, yPos);
                    }
                }
                break;
            case 3:
                for (int i = 0; i < tiles_; i++) {
                    if (intGrid->getValue(xPos, yPos + i) != 0) {
                        ifValid = false;
                        break;
                    } else ifValid = true;
                }
                if (ifValid) {
                    headX_ = xPos;
                    headY_ = yPos;
                    heading_ = heading;
                    isPlaced_ = true;
                    placedOnShip_ = shipGrid;
                    placedOnInts_ = intGrid;
                    for (int i = -1; i <= tiles_; i++) {
                        for (int j = -1; j <= 1; j++) {
                            intGrid->addAtXY(xPos + j, yPos + i);
                        }
                    }
                    for (int i = 0; i < tiles_; i++) {
                        shipGrid->setValue((ShipPImpl *) S, xPos, yPos + i);
                    }
                }
                break;
        }
        return ifValid;
    }

    int shotAtTile(int shotTile) {
        if (shotTile >= 0 && shotTile < tiles_) {
            if (hitTiles_[shotTile] == 0) {
                shotAt_++;
            }
            hitTiles_[shotTile]++;
            return hitTiles_[shotTile];
        }
        return 0;
    }

    int shotAtXY(int xCoord, int yCoord) {
        switch (heading_) {
            case 0:
                if (yCoord == headY_ && xCoord < headX_ + tiles_ && xCoord >= headX_)
                    return shotAtTile(std::abs(xCoord - headX_));
            case 1:
                if (xCoord == headX_ && yCoord > headY_ - tiles_ && yCoord <= headY_)
                    return shotAtTile(std::abs(yCoord - headY_));
            case 2:
                if (yCoord == headY_ && xCoord > headX_ - tiles_ && xCoord <= headX_)
                    return shotAtTile(std::abs(xCoord - headX_));
            case 3:
                if (xCoord == headX_ && yCoord < headY_ + tiles_ && yCoord >= headY_)
                    return shotAtTile(std::abs(yCoord - headY_));
        }
        return 0;
    }

    inline int getTiles() { return tiles_; };

    char renderTile(int tileToRender, int param) {
        switch (param) {
            case 0:
                if (tileToRender >= 0 && tileToRender < tiles_) {
                    if (hitTiles_[tileToRender] == 0) {
                        return 'O';
                    }
                    return 'X';
                }
                return '=';
            case 1:
                if (tileToRender >= 0 && tileToRender < tiles_) {
                    if (hitTiles_[tileToRender] != 0) {
                        return 'X';
                    }
                }
                return '=';
        }
        return '=';
    }

    char renderXY(int xCoord, int yCoord, int param) {
        {
            if (xCoord == headX_) {
                return renderTile(std::abs(yCoord - headY_), param);
            } else if (yCoord == headY_) {
                return renderTile(std::abs(xCoord - headX_), param);
            }
        }
        return '=';
    }

    bool isDead() {
        return (shotAt_ >= tiles_);
    }

private:
    void allocation() {
        hitTiles_ = new int[tiles_];
        for (int i = 0; i < tiles_; i++) {
            hitTiles_[i] = 0;
        }
    }

    int *hitTiles_;
    int heading_ = -1;
    int tiles_ = 0;
    int headX_ = -1;
    int headY_ = -1;
    bool isPlaced_ = 0;
    int shotAt_ = 0;
    PimplGrid *placedOnShip_;
    IntGrid *placedOnInts_;

};

bool ShipPImpl::placeAtXY(PimplGrid *shipGrid, IntGrid *intGrid, int xPos, int yPos, int heading) {
    return pImpl->placeAtXY(shipGrid, intGrid, xPos, yPos, heading, (const ShipPImpl *) this);
}

void ShipPImpl::removeFromMap() {
    pImpl->removeFromMap((const ShipPImpl *) this);
}

int ShipPImpl::shotAtXY(int xCoord, int yCoord) {
    return pImpl->shotAtXY(xCoord, yCoord);
}

int ShipPImpl::shotAtTile(int pos) {
    return pImpl->shotAtTile(pos);
}

char ShipPImpl::renderTile(int pos, int param) {
    return pImpl->renderTile(pos, param);
}

char ShipPImpl::renderXY(int xCoord, int yCoord, int param) {
    return pImpl->renderXY(xCoord, yCoord, param);
}

int ShipPImpl::getTiles() {
    return pImpl->getTiles();
}

bool ShipPImpl::isDead() {
    return pImpl->isDead();
}

ShipPImpl::~ShipPImpl() {
    delete pImpl;
    pImpl = nullptr;
}

ShipPImpl::ShipPImpl(int s) : pImpl(new Impl(s)) {
};

template
class GridTemplate<int>;

template
class GridTemplate<ShipPImpl *>;
