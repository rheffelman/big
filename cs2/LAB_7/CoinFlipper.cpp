#include "CoinFlipper.h"

//Add a class constructor that initializes the private data member to a random coin flip.
CoinFlipper::CoinFlipper()
{
    setHeadsTails(rand() % 2);
}

void CoinFlipper::setHeadsTails(int randNum)
{
    if (randNum == 1)
    {
        headsOrTails = "Heads";
    }
    else if (randNum == 0)
    {
        headsOrTails = "Tails";
    }
}

//change the getCoinFlip() method to simply return the value of the private data member.
string CoinFlipper::getCoinFlip()
{
    return headsOrTails;
}

//include a new method flipCoin() that will store a new random value in the private data member.
void CoinFlipper::flipCoin()
{
    setHeadsTails(rand() % 2);
}