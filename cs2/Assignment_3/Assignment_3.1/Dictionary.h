#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Dictionary{
public:
    Dictionary(const string& dictionaryPath);
    bool search(string& searchWord);
    void addMoreWords(const string& filePath);
    void getSuggestion(const string& word, vector < string >& suggestions);
    int levenshteinDistance(const string& word1, const string& word2);
    double jaccardSimilarity(const string& word1, const string& word2);
    vector < vector<string> > words;
    string cleanse(const string& word);
    int getWordPos(string& word);
    void bubbleSortByJaccard(vector <string>& vec, const string& word);
};