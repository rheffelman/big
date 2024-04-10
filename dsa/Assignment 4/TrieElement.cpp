#include "TrieElement.h"

TrieElement::TrieElement(char letter)
{
    c = letter;
}
//--
TrieElement::~TrieElement()
{
    for (int i = 0; i < 26; i++)
    {
        delete subTries[i];
    }
}