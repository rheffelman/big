#pragma once
#include "Trie.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <cassert>
#include <vector>
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
    TrieElement* traverse(const Die* d, const TrieElement* c);
    void printWords() const;
    void shuffle(string(&a)[25][6]);

    Die* west(const Die* d);
    Die* southWest(const Die* d);
    Die* south(const Die* d);
    Die* southEast(const Die* d);
    Die* east(const Die* d);
    Die* northEast(const Die* d);
    Die* north(const Die* d);
    Die* northWest(const Die* d);

};