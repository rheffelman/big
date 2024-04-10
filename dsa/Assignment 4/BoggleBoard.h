#pragma once
#include "Trie.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <cassert>
#include <vector>
#include <random>
using namespace std;

class BoggleBoard
{
public:

    struct Die
    {
        string text;
        int x;
        int y;
    };
    
    BoggleBoard(const string& pathToDictionary);
    ~BoggleBoard();
    void printBoard();
    void solve();
    
    private:
    Die* board[5][5];
    Trie words;
    vector < unordered_set < string > > foundWords;
    
    void solveHelper(Die* d, TrieElement* c, unordered_set < Die* > travelled);
    TrieElement* traverse(Die* d, TrieElement* c);
    void printWords();

    Die* west(Die* d);
    Die* southWest(Die* d);
    Die* south(Die* d);
    Die* southEast(Die* d);
    Die* east(Die* d);
    Die* northEast(Die* d);
    Die* north(Die* d);
    Die* northWest(Die* d);
};