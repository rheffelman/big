#pragma once
#include "Dictionary.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class WordFinder{
public:
    WordFinder(const string& dictionaryPath);
    ~WordFinder();
    void makeWordsFromWord(const string& word);
    
private:
    void mwfwHelper(const string& word, int length, vector < string > k);
    void printWords(vector < string > k);
    string cleanse(const string& word);
    Dictionary* d;
};