using namespace std;

class Node
{

public:

    ~Node()
    {
        delete left;
        delete right;
    }

    Node* left = NULL;
    Node* right = NULL;
    int val;

private:

};