#include <iostream>
#include <string>
#include <ctime>
#include "BoggleBoard.h"
using namespace std;

int main()
{
    //comment this out while debugging to get the same board over and over again
    srand(time(0));

    BoggleBoard bb("bigDictionary.txt");
    bb.printBoard();
    bb.solve();

    cout<<"exited";
    return 0;
}