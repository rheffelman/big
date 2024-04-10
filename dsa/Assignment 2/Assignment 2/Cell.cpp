#include "Cell.h"

int Cell::getRow() const
{
    return row;
}
//--
void Cell::setRow(int x)
{
    if (x >= 0)
    {
        row = x;
    }
}

//--
int Cell::getColumn() const
{
    return column;
}
//--
void Cell::setColumn(int x)
{
    if (x >= 0)
    {
        column = x;
    }
}

//--
int Cell::getIndex() const
{
    return index;
}
//--
void Cell::setIndex(int x)
{   
    if (x >= 0)
    {
        index = x;
    }
}

//--
char Cell::getCellType() const
{
    return cellType;
}
//--
void Cell::setCellType(char x)
{
    if (int(x))
    {
        cellType = x;
    }
}

//--
bool Cell::getIsTraversed() const
{
    return isTraversed;
}
//--
void Cell::setIsTraversed(bool x)
{
    isTraversed = x;
}

//--
bool Cell::getOnPath() const
{
    return onPath;
}
//--
void Cell::setOnPath(bool x)
{
    onPath = x;
}