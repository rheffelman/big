#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "Number.h"
#include "Suit.h"
#include "Deck.h"

using namespace std;

int main(){

Deck d;
d.print();
printf("\n");
d.shuffleDeck();
d.print();
return 0;
}