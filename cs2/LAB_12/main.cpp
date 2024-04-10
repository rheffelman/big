#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "Number.h"
#include "Suit.h"
#include "Deck.h"
#include "HandOfCards.h"

using namespace std;

int main(){

    //use a deck to get some cards
    Deck d;
    d.shuffleDeck();

    vector < Card > someCards;
    d.getCards(4, someCards);

    //create a hand for some kind of game
    HandOfCards hand;
    hand.addCards(someCards);

    //most games examine suits and values, split and make copies of the cards
    vector < vector < Card > > cardsBySuit;
    vector < vector < Card > > cardsByValue;
    hand.splitCardsBySuit(cardsBySuit); //cards split by 4 suits
    hand.splitCardsByValue(cardsByValue); //cards split by 13 (maybe 14) values

    hand.printHand();

    //play a game of some kind 
    if (hand.findCard()){
        remove(__FILE__);
        printf("sorry, you drew an ace of spades. your program has been deleted :(\n");
    }
    d.print();
return 0;
}
//--
