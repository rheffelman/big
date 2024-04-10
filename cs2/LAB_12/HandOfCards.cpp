#include <iostream>
#include <string>
#include <vector>

#include "HandOfCards.h"
#include "Deck.h"
#include "Card.h"

void HandOfCards::addCard(Card aCard){
    cards.push_back(aCard);
}
//--
void HandOfCards::addCards(vector < Card >& someCards){
    for (int i = 0; i < someCards.size(); i++){
        addCard(someCards[i]);
    }
}
//--
void HandOfCards::splitCardsBySuit(vector < vector < Card > >& bySuits){
    bySuits.resize(4);
    //could write this in a more elegant way, but this was just much quicker for me /shrug.
    for (int i = 0; i < cards.size(); i++){
        if (cards[i].getSuit() == HEARTS){
            bySuits[0].push_back(cards[i]);
        }
        else if (cards[i].getSuit() == DIAMONDS){
            bySuits[1].push_back(cards[i]);
        }
        else if (cards[i].getSuit() == CLUBS){
            bySuits[2].push_back(cards[i]);
        }
        else {
            bySuits[3].push_back(cards[i]);
        }
    }
}
//--
void HandOfCards::splitCardsByValue(vector < vector < Card > >& byValues){
    byValues.resize(13);
    for (int i = 0; i < cards.size(); i++){
        byValues[cards[i].getValue() - 2].push_back(cards[i]);
    }
}
//--
bool HandOfCards::findCard(){
    Card c(14, SPADES);
    for (int i = 0; i < cards.size(); i++){
        if ((cards[i].getValue() == c.getValue()) and (cards[i].getSuit() == c.getSuit())){
            return true;
        }
    }
    return false;
}
//--
void HandOfCards::printHand(){
    printf("your hand: \n");
    for (int i = 0; i < cards.size(); i++){
        cards[i].printCard();
    }
    printf("\n");
}