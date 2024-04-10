#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

#include "Card.h"
#include "Number.h"
#include "Suit.h"
#include "Deck.h"
#include "HandOfCards.h"
#include "PokerEvaluator.h"

using namespace std;

int main(){
    srand(time(0));
    //five card evaluator
    //create a poker evaluator for 5 card poker
    PokerEvaluator fiveCardPokerEvaluator(5);

    //play 100,000 (default number of hands) hands and track the statistics, then print the results to the screen
    fiveCardPokerEvaluator.playAndDisplay();

    7 card evaluator
    create a poker evaluator for 7 card poker
    PokerEvaluator sevenCardPokerEvaluator(7);

    //set the number of hands to play- one million this time
    sevenCardPokerEvaluator.setNumberOfHandsToPlay(1000000);
    //play one million hands of 7 card poker
    sevenCardPokerEvaluator.playAndDisplay();

    //add some user defined cards to the hand (these will be a part of every single one of the 1M hands)
    sevenCardPokerEvaluator.addCardToHand(2, "Hearts");
    sevenCardPokerEvaluator.addCardToHand(7, "Diamonds");

    //play all the hands and track the statistics, then print the results to the screen
    sevenCardPokerEvaluator.playAndDisplay();
return 0;
}
//--
