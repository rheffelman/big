#pragma once
#include <string>

using namespace std;

class CoinFlipper
{
public:
    CoinFlipper();
    void setHeadsTails(int randNum);
    string getCoinFlip();
    void flipCoin();
private:
    string headsOrTails;
};