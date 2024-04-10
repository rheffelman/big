#pragma once 
 
#include <iostream> 
#include <cassert>

using namespace std; 
 
template < class T > 
class BSTree 
{ 
public: 
    BSTree(); 
    ~BSTree(); 

    struct Node 
	{ 
		T data; 
		Node* left; 
		Node* right; 
	}; 
 
    Node* root;
    Node* monkey; //because it traverses the tree :)
	int numberOfElements;
    int height;
    //int count;

    void insert(const T& d); 
    void printInOrder(); 
    void printPreorder(); 
    void printPostOrder();

    auto* getRoot();
    auto* previous(Node* p);
    //returns the largest value (of type T) in the tree. Throw an exception if this method is called when the tree is empty.
    T max();
    T maxHelper();

    //returns the smallest value (of type T) in the tree. Throw an exception if this method is called when the tree is empty.
    T min();
    T minHelper();

    //takes a piece of data, d, and return true if the data is in the tree and false if it is not
    bool search(const T& d);
    bool searchHelper(const T& d);
    Node* get(const T& d);
    Node* getHelper(const T& d);
    auto* leftMostRightSide();
    auto* leftMostRightSideHelper(int n);

    //takes a piece of data and counts and returns how many times it shows up in the tree.
    int count(const T& d);
    int countHelper(const T& d, int count);

    //return the height of the tree
    int heightOfTree();
    void heightFinder(int count);

    //return the percentage of nodes that are leaf nodes
    double percentLeaf();
    void leafCounter(Node* c);

    //return the percentage of nodes that are interior nodes
    double percentInterior();
    void interiorCounter(Node* c);

    /*removes an element if it is present in the tree. Think about what has to happen if 
    the Node that is to be deleted has no children, one child, or two children.*/
    void remove(const T& d);
    void removeHelper(const T& d);
    void removeRoot(const T& d, Node* temp);
     
private: 
 
    void insert(Node*& p, const T& d); 
    void printInOrderHelper(Node* p); 
    void printPreorderHelper(Node* p); 
    void printPostOrderHelper(Node* p); 
    void removeAll(Node*& p);
}; 
//--
template < class T > 
Node* BSTree< T >::get(const T& d)
{

} 
//--
template < class T > 
BSTree < T >::BSTree() 
{ 
    root = 0; 
    monkey = root;
    numberOfElements = 0;

    height = 0;
    //count = 0;
} 
//-- 
template < class T > 
BSTree < T >::~BSTree() 
{ 
    removeAll(root); 
} 
//-- 
template < class T > 
void BSTree < T >::removeAll(Node*& p) 
{ 
	if (p != 0) 
    { 
        removeAll(p->left); 
        removeAll(p->right); 
        delete p; 
    } 
} 
//-- 
template < class T > 
void BSTree < T >::insert(const T& d) 
{ 
    insert(root, d); 
} 
//-- 
template < class T > 
void BSTree < T >::insert(Node*& p, const T& d) 
{ 
    if (p == 0) 
	{ 
        p = new Node; 
        p->left = 0; 
		p->right = 0; 
        p->data = d; 
        numberOfElements++; 
 
        //cout<<"Inserting "<<d<<endl; 
    } 
    else if (d < p->data) 
    { 
        insert(p->left, d); 
    } 
    else 
    { 
        insert(p->right, d); 
    } 
} 
//-- 
template < class T > 
void BSTree < T >::printInOrder() 
{ 
    printInOrderHelper(root); 
	cout << endl; 
} 
//-- 
template < class T > 
void BSTree < T >::printInOrderHelper(Node* p) 
{ 
    if (p != 0) 
	{ 
		printInOrderHelper(p->left); 
		cout << p->data << " "; 
		printInOrderHelper(p->right); 
	} 
} 
//-- 
template < class T > 
void BSTree < T >::printPreorder() 
{ 
	printPreorderHelper(root); 
	cout << endl; 
} 
//-- 
template < class T > 
void BSTree < T >::printPreorderHelper(Node* p) 
{ 
	if (p != 0) 
	{ 
		cout << p->data << " "; 
		printPreorderHelper(p->left); 
		printPreorderHelper(p->right); 
	} 
} 
//-- 
template < class T > 
void BSTree < T >::printPostOrder() 
{ 
	printPostOrderHelper(root); 
	cout << endl; 
} 
//-- 
template < class T > 
void BSTree < T >::printPostOrderHelper(Node* p) 
{ 
	if (p != 0) 
	{ 
		printPostOrderHelper(p->left); 
		printPostOrderHelper(p->right); 
		cout << p->data << " "; 
	} 
}
//--
template < class T >
auto* BSTree < T >::getRoot()
{
    return root;
}
//--
template < class T >
T BSTree < T >::max()
{
    monkey = root;
    if (numberOfElements == 1)
    {
        return root->data;
    } 
    assert(numberOfElements > 1);
    return maxHelper();
}
//--
template < class T >
T BSTree < T >::maxHelper()
{
    if (monkey->right)
    {
        monkey = monkey->right;
        return maxHelper();
    }
    else
    {
        return monkey->data;
    }
}
//--
template < class T >
T BSTree < T >::min()
{
    monkey = root;
    if (numberOfElements == 1)
    {
        return root->data;
    } 
    assert(numberOfElements > 1);
    return minHelper();
}
//--
template < class T >
T BSTree < T >::minHelper()
{
    if (monkey->left)
    {
        monkey = monkey->left;
        return minHelper();
    }
    else
    {
        return monkey->data;
    } 
}
//--
template < class T >
bool BSTree < T >::search(const T& d)
{
    monkey = root;
    if (numberOfElements == 1)
    {
        return root->data == d;
    }
    assert(numberOfElements > 1);
    return searchHelper(d);
}
//--
template < class T >
bool BSTree < T >::searchHelper(const T& d)
{
    if (monkey->data == d) return true;
    if (d < monkey->data)
    {
        if (monkey->left)
        {
            //if (monkey->left->data == d) return true;
            monkey = monkey->left;
        }
        else
        {
            return false;
        }
        return searchHelper(d);
    }
    else
    {
        if (monkey->right)
        {
            //if (monkey->right->data == d) return true;
            monkey = monkey->right;
        }
        
        else
        {
            return false;
        } 
        return searchHelper(d);
    }
    return false;
}
//--
template < class T >
int BSTree < T >::count(const T& d)
{
    bool y = search(d);
    if (y)
    {
        if (monkey->right->data != d)
        {
            return 1;
        }
        return countHelper(d, 1);
    }
    else return 0;
}
//--
template < class T >
int BSTree < T >::countHelper(const T& d, int count)
{
    if (monkey->data == d)
    {
        if (monkey->right)
        {
            monkey = monkey->right;
            return countHelper(d, count + 1);
        }
    }
    return count;
}
//--
template < class T >
int BSTree < T >::heightOfTree()
{
    int x = 1;
    height = 0;
    if (numberOfElements == 1) return 1;
    if (numberOfElements < 1) return 0;
    monkey = root;
    heightFinder(x);
    return height;
}
//--
template < class T >
void BSTree < T >::heightFinder(int count)
{
    if (count > height)
    {
        height = count;
    }

    if (monkey->left)
    {
        monkey = monkey->left;
        count++;
        heightFinder(count);
    }
    if (monkey->right)
    {
        monkey = monkey->right;
        count++;
        heightFinder(count);
    }
    return;
}
//--
template < class T >
double BSTree < T >::percentLeaf()
{
    count = 0;
    if (numberOfElements == 1) return 1;
    if (numberOfElements < 1) return 0;
    Node* c = root;
    leafCounter(c);
    return 100 * (double(count) / numberOfElements);
}
//--
template < class T >
void BSTree < T >::leafCounter(Node* c)
{
    if (!c->left and !c->right)
    {
        count++;
        return;
    }
    if (c->left)
    {
        leafCounter(c->left);
    }
    if (c->right)
    {
        leafCounter(c->right);
    }
    return;
}
//--
template < class T >
double BSTree < T >::percentInterior()
{
    count = 0;
    if (numberOfElements <= 1) return 0;
    Node* c = root;
    interiorCounter(c);
    return 100 * (double(count) / numberOfElements);
}
//--
template < class T >
void BSTree < T >::interiorCounter(Node* c)
{
    if (c->left or c->right)
    {
        count++;
    }
    else return;

    if (c->left)
    {
        interiorCounter(c->left);
    }
    if (c->right)
    {
        interiorCounter(c->right);
    }
    return;
}
//--