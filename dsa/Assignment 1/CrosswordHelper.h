#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include "SafeArray.h"
#include "IntersectionContainer.h"
using namespace std;

class CrossWordHelper{
public:
CrossWordHelper(const string& filePath, int wordLength);
SafeArray < SafeArray < SafeArray <string> > > words;
void getSuggestions(const string& word, IntersectionContainer < string >& c);
private:
};  