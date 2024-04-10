#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "Deck.h"

using namespace std;

Deck::Deck(){
    for (auto& suit: {HEARTS, DIAMONDS, CLUBS, SPADES}){
            for (int i = 2; i <= 14; i++) allCards.push_back(Card(i, suit));
        }
}
//--
void Deck::print() {
        for (int i = 0; i < allCards.size(); i++) allCards[i].printCard();
    }
//--
void Deck::shuffleDeck(){
    auto rng = default_random_engine {};
    shuffle(begin(allCards), end(allCards), rng);
    }
//--
void Deck::removeCard(int num, string suit){
    for (int i = 0; i < allCards.size(); i++){
        if (allCards[i].getValue() == num and allCards[i].getSuit() == suit){
            allCards.erase(allCards.begin() + i);
            break;
        }
    }
}
//--
void Deck::addCardsBackToDeck(vector < Card >& cards){
    for (auto x : cards){
        allCards.push_back(x);
    }
}
//--
bool Deck::getCards(int numRequestedCards, vector < Card >& cards){
    //if the deck doesn't have the requested amount of cards, return false.
    if (numRequestedCards > allCards.size()){
        return false;
    }
    //if it does, add the requested amount of cards to a new vector and remove them from the old (take them).
    for (int i = 0; i < numRequestedCards; i++){
        cards.push_back(allCards[i]);
        removeCard(allCards[i].getValue(), allCards[i].getSuit());
    }
    return true;
}