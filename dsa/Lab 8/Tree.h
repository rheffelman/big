#pragma once
#include <string>
#include <iostream>
using namespace std;

class Tree
{

public:

    struct Node
    {
        int val;
        Node* left;
        Node* right;
    };

    Tree();
    Node*& min(Node*& c);
    void insert(int v);
    void insertHelper(Node*& c, int v);
    void remove(Node*& n);
    void print(Node*& c);
    int numElements;
    Node* root;

private:


};