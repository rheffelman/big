#pragma once
#include <iostream>
using namespace std;
template < typename T >
class LinkedList{
public:
    LinkedList(){
        p_head = 0;
        p_current = 0;
        numElements = 0;
    }
    //--
    ~LinkedList(){
        Node* p_temp;
        for (;!isEmpty();){
            p_temp = p_head;
            p_head = p_head->p_link;
            cout << "Deleting: " << p_temp->data << endl;
            delete p_temp;
            numElements--;
        }
    }
    //--
    void insert(const T& elem){
        Node* p_temp = new Node;
        p_temp->data = elem;
        p_temp->p_link = p_head;
        p_head = p_temp;
        numElements++;
    }
    bool first(T& elem){
        bool retVal = false;
        if (!isEmpty()){
            retVal = true;
            elem = p_head->data;
            p_current = p_head;
        }
        return retVal;
    }
    //--
    bool next(T& elem){
        bool retVal = false;
        if (p_current->p_link != 0){
            p_current = p_current->p_link;
            retVal = true;
            elem = p_current->data;
        }
        return retVal;
    }
    //--
    int length(){
        return numElements;
    }
    //--
    bool isEmpty(){
        return(length() == 0);
    }
private:
    struct Node{
        T data;
        Node* p_link;
    };
    Node* p_head;
    Node* p_current;
    int numElements;
};