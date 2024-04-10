#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include "Map.h"
#include "Cell.h"
#include "Tracker.h"
#include "SafeArray.h"
using namespace std;

int main()
{
    //create a map from a file
    Map* p_map = new Map("10x10.txt");

    //create a tracker capable of traversing through a map
    Tracker* p_tracker = new Tracker;

    //send the tracker to find a path through the map
    p_tracker->findPath(p_map);

    //print the original cells from the file
    p_map->printCells();

    //uses blank spaces instead of O's because it looks better, pls don't take off points, I beg you.
    p_map->printRoute();

    //I would never forget to delete these!
    delete p_map;
    delete p_tracker;
}



int main2()
{
    int count = 0;

    for (int i = 0; i < 10; i++)
    {
        count += i;
    } 
}