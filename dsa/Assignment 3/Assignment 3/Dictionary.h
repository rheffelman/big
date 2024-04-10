#pragma once
#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>
using namespace std;

class Dictionary{
public:
    Dictionary(const string& dictionaryPath);
    bool isWordPresent(const string& word);
private:
    unordered_set < string > allWords;
};