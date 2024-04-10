#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "HandOfCards.h"
#include "Number.h"
#include "Suit.h"
#include "Deck.h"

using namespace std;

class PokerEvaluator {
public:
    PokerEvaluator(int handSize);
    void playAndDisplay();
    void addCardToHand(int val, string suit);
    void setNumberOfHandsToPlay(int num);
    bool royalFlush(vector <Card>& h);
    bool straightFlush(vector <Card>& h);
    bool fourOfAKind(vector <Card>& h);
    bool fullHouse(vector <Card>& h);
    bool flush(vector <Card>& h);
    bool straight(vector <Card>& h);
    bool threeOfAKind(vector <Card>& h);
    bool twoPair(vector <Card>& h);
    bool pair(vector <Card>& h);
    Card highCard(vector <Card>& h);
    int numberOfHands = 100000;
    int m_handSize = 5;
    Deck d;
    HandOfCards reserved;
private:
};