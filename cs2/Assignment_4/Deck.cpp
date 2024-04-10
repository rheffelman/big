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
// void Deck::shuffleDeck(){
//     shuffle(begin(allCards), end(allCards), eng);
// }
//--
bool Deck::getCards(int numRequestedCards, vector < Card >& cards){
    //if the deck doesn't have the requested amount of cards, return false.
    if (numRequestedCards > allCards.size()){
        return false;
    }
    //if it does, add the requested amount of cards to a new vector and remove them from the old (take them).
    for (int i = 0; i < numRequestedCards; i++){
        int randIndex = rand() % allCards.size();
        Card c = allCards[randIndex];
        cards.push_back(c);
        allCards.erase(allCards.begin() + randIndex);
    }
    return true;
}
//--
void Deck::addCardsBackToDeck(vector < Card >& cards){
    for (auto x : cards){
        allCards.push_back(x);
    }
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