#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Card.h"
#include "Number.h"
#include "Suit.h"

class HandOfCards
{
public:
    void addCard(Card aCard);
    void addCards(vector < Card >& someCards    );
    void splitCardsBySuit(vector < vector < Card > >& bySuits);
    void splitCardsByValue(vector < vector < Card > >& byValues);
    bool findCard();
    void printHand();
private:
    vector < Card > cards;
};