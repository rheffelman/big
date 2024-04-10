#include "Map.h"

Map::Map(const string& pathToFile)
{
        ifstream infile;
        infile.open(pathToFile);

        if (infile.good())
        {
                char latestLetter;
                infile >> latestLetter;

                for (;infile.good();)
                {
                        Cell* c = new Cell;
                        c->setCellType(latestLetter);
                        allCells.push_back(c);
                        infile >> latestLetter;
                }
        }
        size = sqrt(allCells.size());

        for (int i = 0; i < allCells.size(); i++)
        {
                allCells[i]->setIndex(i);
                allCells[i]->setRow(i / size);
                allCells[i]->setColumn(i % size);
        }
}
//--
Map::~Map()
{
        for (int i = 0; i < allCells.size(); i++)
        {
                delete allCells[i];
        }
}
//--
void Map::printCells()
{
        cout << endl;

        for (int i = 0; i < allCells.size(); i++)
        {
                cout << allCells[i]->getCellType() << " ";

                if ((i + 1) % size == 0)
                {
                        cout << endl;
                }
        }
        cout << endl;
}
//--
void Map::printRoute()
{
        for (int i = 0; i < allCells.size(); i++)
        {

                if (allCells[i]->getOnPath())
                {
                        cout << "O ";
                }
                else
                {
                        cout << "X ";
                }
                if ((i + 1) % size == 0)
                {
                        cout << endl;
                }
        }
        cout << endl;
}
//--
bool Map::isFree(const Cell* c)
{
        return (c->getCellType() != 'B');
}
//--
Cell* Map::getIfFree(Cell* c)
{
        if (isFree(c))
        {
                return c;
        }

        else return NULL;
}
//--
Cell* Map::getStart()
{
        for (int i = 0; i < allCells.size(); i++)
        {
                if (allCells[i]->getCellType() == 'S')
                {
                        return allCells[i];
                }
        }
        return NULL;
}
//--
Cell* Map::getCell(int index)
{
        if (index < 0 or index > allCells.size() - 1)
        {
                return NULL;
        }
        
        else return allCells[index];
}
//--
Cell* Map::getNorth(Cell* p_cell)
{
        if (p_cell->getIndex() - size >= 0)
        {
                return getIfFree(allCells[p_cell->getIndex() - size]);
        }
        else return NULL;
}
//--
Cell* Map::getEast(Cell* p_cell)
{
        if ((p_cell->getIndex() + 1) % size != 0)
        { 
                return getIfFree(allCells[p_cell->getIndex() + 1]);
        }
        else return NULL;
}
//--
Cell* Map::getSouth(Cell* p_cell)
{
        if (p_cell->getIndex() + size <= size * size - 1)
        {
                return getIfFree(allCells[p_cell->getIndex() + size]);
        }
        else return NULL;
}
//--
Cell* Map::getWest(Cell* p_cell)
{
        if ((p_cell->getIndex() + 1) % size != 1)
        {
                return getIfFree(allCells[p_cell->getIndex() - 1]);
        }
        else return NULL;
}
//--
Cell* Map::getNorthEast(Cell* p_cell)
{
        if (((p_cell->getRow()) != 0) and ((p_cell->getColumn()) != (size - 1)))
        {
                return getIfFree(allCells[p_cell->getIndex() - size + 1]);
        }
        else return NULL;
}
//--
Cell* Map::getSouthEast(Cell* p_cell)
{
        if (((p_cell->getColumn()) != (size - 1)) and ((p_cell->getRow()) != (size - 1)))
        {
                return getIfFree(allCells[p_cell->getIndex() + size + 1]);
        }
        else return NULL;
}
//--
Cell* Map::getSouthWest(Cell* p_cell)
{
        if (((p_cell->getRow()) != (size - 1)) and ((p_cell->getColumn()) != 0))
        {
                return getIfFree(allCells[p_cell->getIndex() + size - 1]);
        }
        else return NULL;
}
//--
Cell* Map::getNorthWest(Cell* p_cell)
{
        if (((p_cell->getRow()) != 0) and ((p_cell->getColumn()) != 0))
        {
                return getIfFree(allCells[p_cell->getIndex() - size - 1]);
        }
        else return NULL;
}