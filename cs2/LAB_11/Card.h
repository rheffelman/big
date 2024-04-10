#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Number.h"
#include "Suit.h"

using namespace std;

static const string HEARTS = "Hearts";
static const string DIAMONDS = "Diamonds";
static const string CLUBS = "Clubs";
static const string SPADES = "Spades";

class Card {
public:
    Card(int num, string suit){
        n = Number(num);
        s = Suit(suit);
    }
    void printCard(){
        switch (n.val) {
            case 11:
                printf("J of %s\n", s.str.c_str());
                break;
            case 12:
                printf("Q of %s\n", s.str.c_str());
                break;
            case 13:
                printf("K of %s\n", s.str.c_str());
                break;
            case 14:
                printf("Ace of %s\n", s.str.c_str());
                break;
            default:
                printf("%d of %s\n", n.val, s.str.c_str());
                break;
        }
    }
    int getValue(){
        return n.val;
    }
private:
    Number n;
    Suit s;
};

