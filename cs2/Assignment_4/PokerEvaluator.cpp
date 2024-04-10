#include "PokerEvaluator.h" 
PokerEvaluator::PokerEvaluator(int handSize){
    m_handSize = handSize;
}
//--
void PokerEvaluator::playAndDisplay(){
    int countArray[9] {0};
    for (int i = 0; i < numberOfHands; i++){
        HandOfCards h;
        vector <Card> someCards;
        h.addCards(reserved.cards);
        d.getCards(m_handSize - reserved.cards.size(), someCards);
        h.addCards(someCards);
        //lambda function that sorts the hand on getValue() comparison
        sort(h.cards.begin(), h.cards.end(),
        [](Card & a, Card & b){
        return a.getValue() < b.getValue();
        });
        if (royalFlush(h.cards)) countArray[0]++;
        else if (straightFlush(h.cards)) countArray[1]++;
        else if (fourOfAKind(h.cards)) countArray[2]++;
        else if (fullHouse(h.cards)) countArray[3]++;
        else if (flush(h.cards)) countArray[4]++;
        else if (straight(h.cards)) countArray[5]++;
        else if (threeOfAKind(h.cards)) countArray[6]++;
        else if (twoPair(h.cards)) countArray[7]++;
        else if (pair(h.cards)) countArray[8]++;
        d.addCardsBackToDeck(someCards);
    }
    for (int i = 0; i < 9; i++){
        printf("%d: %d\n", i, countArray[i]);
    }
}
//--
void PokerEvaluator::addCardToHand(int val, string suit){
    reserved.addCard(Card(val, suit));
    d.removeCard(val, suit);
}
//--
void PokerEvaluator::setNumberOfHandsToPlay(int num){
    numberOfHands = num;
}
//--
bool PokerEvaluator::royalFlush(vector <Card>& h){
    int ar[4] {0};
    string suitAr[4] {HEARTS, DIAMONDS, CLUBS, SPADES};
    for (int i = 0; i < h.size(); i++){
        string suit = h[i].getSuit();
        if (suit == HEARTS) ar[0]++;
        if (suit == DIAMONDS) ar[1]++;
        if (suit == CLUBS) ar[2]++;
        if (suit == SPADES) ar[3]++;
    }

    int suitIndex = -1;
    for (int i = 0; i < 4; i++){
        if (ar[i] >= 5) suitIndex = i;
    }
    if (suitIndex == -1) return false;

    vector <Card> cardsInFlush;
    for (int i = 0; i < h.size(); i++){
        if (h[i].getSuit() == suitAr[suitIndex]){
            cardsInFlush.push_back(h[i]);
        }
    }

    bool valAr[5] {false};
    for (int i = 0; i < h.size(); i++){
        int val = h[i].getValue();
        if (val == 10) valAr[0] = true;
        else if (val == 11) valAr[1] = true;
        else if (val == 12) valAr[2] = true;
        else if (val == 13) valAr[3] = true;
        else if (val == 14) valAr[4] = true;
    }

    bool found = true;
    for (int i = 0; i < 5; i++){
        if (!valAr[i]) found = false;
        if (!found) return false;
    }
    return true;
}
//--
bool PokerEvaluator::straightFlush(vector <Card>& h){
    int ar[4] {0};
    string suitAr[4] {HEARTS, DIAMONDS, CLUBS, SPADES};
    for (int i = 0; i < h.size(); i++){
        string suit = h[i].getSuit();
        if (suit == HEARTS) ar[0]++;
        if (suit == DIAMONDS) ar[1]++;
        if (suit == CLUBS) ar[2]++;
        if (suit == SPADES) ar[3]++;
    }

    int suitIndex = -1;
    for (int i = 0; i < 4; i++){
        if (ar[i] >= 5) suitIndex = i;
    }
    if (suitIndex == -1) return false;
    vector <Card> cardsInFlush;
    for (int i = 0; i < h.size(); i++){
        if (h[i].getSuit() == suitAr[suitIndex]){
            cardsInFlush.push_back(h[i]);
        }
    }
    bool inTheCloset = false;
    int count = 0;
    for (int i = 0; i < cardsInFlush.size() - 1; i++){
        if ((cardsInFlush[i + 1].getValue() - cardsInFlush[i].getValue()) == 0) continue;
        if (count >= 4){
            inTheCloset = true;
            break;
        }
        if ((cardsInFlush[i + 1].getValue() - cardsInFlush[i].getValue()) == 1){
           count++; 
        }
        else count = 0;
    }
    if (count >= 4){
            inTheCloset = true;
    }
    return inTheCloset;
}
//--
bool PokerEvaluator::fourOfAKind(vector <Card>& h){
    for (int i = 0; i < h.size(); i++){
        int count = 0;
        for (int j = 0; j < h.size(); j++){
            int val = h[i].getValue();
            if (h[j].getValue() == val){
                count++;
            }
        }
        if (count >= 4) return true;
    }
    return false;
}
//--
bool PokerEvaluator::fullHouse(vector <Card>& h){
    //  checks if there's a three-of-a-kind in the hand
    int firstVal = 0;
    for (int i = 0; i < h.size(); i++){
        int count = 0;
        for (int j = 0; j < h.size(); j++){
            int val = h[i].getValue();
            if (h[j].getValue() == val){
                count++;
            }
        }
        if (count >= 3) firstVal = h[i].getValue();
    }
    if (firstVal == 0) return false;

    /* if there is, checks to see if a pair exists that doesn't 
     consist of the values that constitute the three-of-a-kind  */
    for (int i = 0; i < h.size(); i++){
        for (int j = 0; j < h.size(); j++){
            if (h[i].getValue() == h[j].getValue() and i != j){
                if (h[i].getValue() != firstVal){
                    return true;
                }
            }
        }
    }
    return false;

}
//--
bool PokerEvaluator::flush(vector <Card>& h){
    int ar[4] {0, 0, 0, 0};
    for (int i = 0; i < h.size(); i++){
        if (h[i].getSuit() == HEARTS){
            ar[0]++;
        }
        else if (h[i].getSuit() == DIAMONDS){
            ar[1]++;
        }
        else if(h[i].getSuit() == CLUBS){
            ar[2]++;
        }
        else ar[3]++;
    }
    for (int i = 0; i < 4; i++){
        if (ar[i] >= 5) return true;
    }
    return false;
}
//--
bool PokerEvaluator::straight(vector <Card>& h){
    for (int i = 0; i < h.size(); i++){
        int val = h[i].getValue();
        if (val < 11){
            vector <int> requisiteVals;
            for (int j = 0; j < 5; j++){
                requisiteVals.push_back(val);
                val++;
            }
            bool ar[5] {false};
            for (int j = 0; j < requisiteVals.size(); j++){
                for (int k = 0; k < h.size(); k++){
                    if (requisiteVals[j] == h[k].getValue()){
                        ar[j] = true;
                    }
                }
            }
            bool inTheCloset = true;
            for (int j = 0; j < 5; j++){
                if (!ar[j]) inTheCloset = false;
            }
            if (inTheCloset) return true;
        }  
    }
    return false;
}
//--
bool PokerEvaluator::threeOfAKind(vector <Card>& h){
    for (int i = 0; i < h.size(); i++){
        int count = 0;
        for (int j = 0; j < h.size(); j++){
            int val = h[i].getValue();
            if (h[j].getValue() == val){
                count++;
            }
        }
        if (count >= 3) return true;
    }
    return false;
}
//--
bool PokerEvaluator::twoPair(vector <Card>& h) {
    bool firstCheck = false;
    int firstI = 0;
    int firstJ = 0;

    for (int i = 0; i < h.size(); i++) {
        for (int j = i + 1; j < h.size(); j++) {
            if (h[i].getValue() == h[j].getValue()) {
                if (!firstCheck) {
                    firstCheck = true;
                    firstI = i;
                    firstJ = j;
                } 
                else {
                    if (i != firstI and i != firstJ and j != firstI and j != firstJ)
                        return true;
                }
            }
        }
    }

    return false;
}
//--
bool PokerEvaluator::pair(vector <Card>& h){
    for (int i = 0; i < h.size(); i++){
        for (int j = 0; j < h.size(); j++){
            if (h[i].getValue() == h[j].getValue() and i != j){
                return true;
            }
        }
    }
    return false;
}
//--
Card PokerEvaluator::highCard(vector <Card>& h){
    Card highestCard = h[0];
    for (int i = 1; i < h.size(); i++){
        if (h[i].getValue() > highestCard.getValue()){
            highestCard = h[i];
        }
    }
    return highestCard;
}