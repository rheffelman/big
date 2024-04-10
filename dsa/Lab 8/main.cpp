#include <iostream>
#include <string>
#include <random>
#include "Tree.h"
using namespace std;

int main()
{
	srand(0);
	Tree t;
	//t.root->val = 5;
	//cout <<t.root->val;
	t.insert(25);
	for (int i = 0; i < 25; i++)
	{
		t.insert(rand() % 51);
	}
	//Tree::Node* p = t.min(t.root->right->right);
	t.remove(t.root);
	//cout << t.min(t.root)->val << endl;
	//t.print(t.root->right);
	printf("Exited");
}