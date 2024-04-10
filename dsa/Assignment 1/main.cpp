#include <iostream>
#include <cassert>
#include <string>
#include "SafeArray.h"
#include "IntersectionContainer.h"
#include "CrossWordHelper.h"
#include "SafeArrayException.h"

using namespace std;

int main(){
    string word = "a--";
    CrossWordHelper b("C:\\Users\\ryanh\\OneDrive\\Documents\\GitHub\\CSC-2560\\Assignment 1\\A31_dictionary.txt", word.length());
    IntersectionContainer < string > c;
    b.getSuggestions(word, c);
    c.printersection();
}