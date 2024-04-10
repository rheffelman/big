#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Card.h"
#include "Number.h"

using namespace std;

class Suit {
public:
    Suit(){}
    Suit(string s){
        if (inputCheck(s)){
            str = s;
        }
    }
    string str;
private:
    bool inputCheck(string s) {
        string inputs = "Hearts Diamonds Clubs Spades hearts diamonds clubs spades";

        //true if string s is found in the inputs string, else false.
        return (inputs.find(s) != string::npos);
    }
};