#include <iostream>
#include <cassert>

// struct Node{
// 	struct Node * next = nullptr;
// 	unsigned int payload;
// };

// Node* insert(Node* n, Node* head)
// {
// 	if (!head) {
// 		head = n;
// 		return head;
// 	}

// 	if (head->next){
// 		if (head->next->payload > n->payload){
// 			n->next = head->next
// 			head->next = n;
// 		}
// 		else if (head->next->payload <= n->payload){
// 			insert(n, head->next);
// 		}
// 	}
	
// }
struct Node {
};
    unsigned int data;
    Node* next;
//--
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}
//--
void insertSorted(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr or head->data >= data) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr and current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
//--
void display(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
//--
int main(){

    Node* head = nullptr;
    insertSorted(head, 3);
    insertSorted(head, 1);
    insertSorted(head, 5);
    insertSorted(head, 2);
	display(head);
}