#pragma once
#include <string>
#include <vector>
using namespace std;

class TrieElement
{
public:
    TrieElement(char letter);
    ~TrieElement();
    
    char c;
    string wordSoFar;
    bool isCompletedWord = false;
    TrieElement* subTries[26] {NULL};
};