#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <regex>
using namespace std;

class Dictionary
{

public:

    Dictionary();
    unordered_set < string > words;

private:

};
//--
Dictionary::Dictionary()
{
    string filePath = "A31_dictionary.txt";
    ifstream infile;
    infile.open(filePath);
    string word;

    for (;infile.good();)
    {
        infile >> word;
        if (word.length() == 5)
        {
            words.insert(word);
        }
    }
}