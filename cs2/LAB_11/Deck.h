#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Card.h"
#include "Number.h"
#include "Suit.h"

using namespace std;

class Deck {
public:
    Deck(){
        //tried to do it in 1 line in a way that isn't completely stupid, this was the best I could do.
        for (auto& suit: {HEARTS, DIAMONDS, CLUBS, SPADES}){
            for (int i = 2; i <= 14; i++) allCards.push_back(Card(i, suit));
        }
    }
    //--
    void print() {
        for (int i = 0; i < allCards.size(); i++) allCards[i].printCard();
    }
    //--
    void shuffleDeck(){
    auto rng = default_random_engine {};
    shuffle(begin(allCards), end(allCards), rng);
    }
    //--
private:
    vector <Card> allCards;
};