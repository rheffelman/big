#include "TrieElement.h"

TrieElement::TrieElement(char letter)
{
    c = letter;
}
//--
TrieElement::~TrieElement()
{
    for (int i = 0; i < sizeof(subTries)/sizeof(subTries[0]); i++)
    {
        delete subTries[i];
    }
}