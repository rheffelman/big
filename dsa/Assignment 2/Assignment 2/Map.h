#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SafeArray.h"
#include "SafeArrayException.h"
#include "Cell.h"
using namespace std;

class Map
{
public:

    Map(const string& pathToFile);
    ~Map();
    void printCells();
    void printRoute();
    
    Cell* getNorth(Cell* p_cell);
    Cell* getEast(Cell* p_cell);
    Cell* getSouth(Cell* p_cell);
    Cell* getWest(Cell* p_cell);
    Cell* getNorthEast(Cell* p_cell);
    Cell* getSouthEast(Cell* p_cell);
    Cell* getSouthWest(Cell* p_cell);
    Cell* getNorthWest(Cell* p_cell);
    Cell* getStart();
    Cell* getCell(int index);
    bool isFree(const Cell* c);
    Cell* getIfFree(Cell* c);

private:

    int size = 0;
    SafeArray < Cell* > allCells;

};