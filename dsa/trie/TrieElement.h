#pragma once
#include <string>
#include <vector>
using namespace std;

class TrieElement
{
public:
    TrieElement(char letter)
    {
        c = letter;
    }
    ~TrieElement()
    {
        for (int i = 0; i < 26; i++)
        {
            //if (subTries[i]) printf("Deleting: %s\n", subTries[i]->wordSoFar.c_str());
            delete subTries[i];
        }
    }
    char c;
    string wordSoFar;
    bool isCompletedWord = false;
    TrieElement* subTries[26] {NULL};
};