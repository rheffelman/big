#include "Tree.h"

Tree::Tree()
{
    root = 0;
    numElements = 0;
}
void Tree::insert(int v)
{
    insertHelper(root, v);
}
//--
void Tree::insertHelper(Node*& c, int v)
{
    if (c == 0)
    {
        c = new Node;
        c->val = v;
        c->left = 0;
        c->right = 0;
        numElements++;
        return;
    }
    if (v > c->val)
    {
        insertHelper(c->right, v);
    }
    if (v < c->val)
    {
        insertHelper(c->left, v);
    }
}
//--
void Tree::print(Node*& c)
{
    cout << c->val << endl;
    if (c->left)
    {
        print(c->left);
    }
    if (c->right)
    {
        print(c->right);
    }
}
//--
//--
Tree::Node*& Tree::min(Node*& c)
{
    if (c->left) return min(c->left);
    else return c;
}
void Tree::remove(Node*& n)
{
    if (n->left and n->right)
    {
        Node* k = min(n->right);
        n->val = k->val;
        remove(k);
    }
    else if (n->left or n->right)
    {
        Node* k = 
    }
    if (!n->left and !n->right)
    {
        delete n;
    }
}