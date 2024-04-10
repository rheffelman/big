#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "CoinFlipper.h"

using namespace std;

void printVector(vector<CoinFlipper>& v);

int main()
{
    srand(time(0));

    CoinFlipper c;

    //In main(), create a vector of 10 coin flip objects --
    vector < CoinFlipper > flips;
    for (int i = 0; i < 10; i++)
    {
        flips.push_back(c);
    }

    //and print them.
    printVector(flips);

    //Then, iterate through all 10 objects in the vector again and call flipCoin() on each object.
    for (int i = 0; i < flips.size(); i++)
    {
        flips[i].flipCoin();
    }

    //Print the 10 values one more time.
    printVector(flips);

    return 0;
}

void printVector(vector<CoinFlipper>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        printf("%s\n", v[i].getCoinFlip().c_str());
    }
    printf("\n");
}