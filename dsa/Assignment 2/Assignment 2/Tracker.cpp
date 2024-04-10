#include "Tracker.h"

void Tracker::findPath(Map* map)
{
    Cell* c = map->getStart();
    s.push(c);
    c->setIsTraversed(true);
    c->setOnPath(true);
    const string ar3[8] {"North", "Northeast", "East", "Southeast", "South", "Southwest", "West", "Northwest"};

    for (;c->getCellType() != 'E';)
    {
        bool ar[8] {map->getNorth(c) != NULL, map->getNorthEast(c) != NULL, map->getEast(c) != NULL, map->getSouthEast(c) != NULL, map->getSouth(c) != NULL, map->getSouthWest(c) != NULL, map->getWest(c) != NULL, map->getNorthWest(c) != NULL};
        Cell* ar2[8] {map->getNorth(c), map->getNorthEast(c), map->getEast(c), map->getSouthEast(c), map->getSouth(c), map->getSouthWest(c), map->getWest(c), map->getNorthWest(c)};

        //check is true if it's able to move, false if it isn't.
        bool check = false;

        for (int i = 0; i < 8; i++)
        {
            if (ar[i] and !ar2[i]->getIsTraversed())
            {
                c = ar2[i];
                c->setIsTraversed(true);
                c->setOnPath(true);
                s.push(c);
                check = true;
                cout << "Going " << ar3[i] << " row: " << c->getRow() + 1<< " col: " << c->getColumn() + 1<< " Type: " << c->getCellType() << endl;
                break;
            }
        }

        if (!check)
        {
            c->setOnPath(false);
            cout << "Backtracking from: row: " << c->getRow() + 1<< " col: " << c->getColumn() + 1<< " Type: " << c->getCellType() << " to: row: ";
            s.pop();
            c = s.top();
            cout << c->getRow() + 1<< " col: " << c->getColumn() + 1<< " Type: " << c->getCellType() << endl;
        }
    }

}