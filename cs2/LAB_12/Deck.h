#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Card.h"
#include "HandOfCards.h"
#include "Number.h"
#include "Suit.h"

using namespace std;

class Deck {
public:
    Deck();

    void print();

    void shuffleDeck();

    bool getCards(int numRequestedCards, vector < Card >& cards);

    void addCardsBackToDeck(vector < Card >& cards);

    void removeCard(int num, string suit);

private:
    vector <Card> allCards;
};