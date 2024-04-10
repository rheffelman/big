#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Dictionary{
public:
    Dictionary(const string& dictionaryPath);
    bool search(string& searchWord);
    void print();
    void addMoreWords(const string& filePath);
private:
    vector < vector < string > > words;
    string cleanse(const string& word);
    int getWordPos(string& word);
};