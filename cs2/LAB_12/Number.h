#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Card.h"
#include "Suit.h"

using namespace std;

class Number {
public:
    Number(){}
    Number(int n){
        if (inputCheck(n)){
            val = n;
        }
    }
    int val = -1;
private:
    bool inputCheck(int n) {
        return (n >= 2 and n <= 14);
    }
};