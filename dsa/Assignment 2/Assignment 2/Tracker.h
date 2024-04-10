#pragma once
#include <string>
#include <iostream>
#include "Stack.h"
#include "Map.h"
using namespace std;

class Tracker
{
public:

    void findPath(Map* map);

private:

    Stack < Cell* > s;
    
};