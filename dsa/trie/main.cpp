#include <iostream>
#include <string>
#include "Trie.h"
#include "TrieElement.h"
using namespace std;


int main()
{
    Trie trie("bigDictionary.txt");

    if (trie.search("rendezvouz")) printf("true!\n");
    printf("exited\n");
}