#pragma once
#include <string>
#include <vector>
using namespace std;

class TrieElement
{

public:

    TrieElement(char letter);
    ~TrieElement();
    TrieElement* subTries[26] {NULL};
    
    char c;
    string wordSoFar;
    bool isCompletedWord = false;
    
};