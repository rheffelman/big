#pragma once
#include <string>
#include <iostream>
using namespace std;

template < typename T >
class DoublyLinkedList
{
public:

    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& x);
    ~DoublyLinkedList();
    void insertAtFront(const T& elem);
    void insertAtRear(const T& elem);
    bool removeFromFront (T& elem);
    bool removeFromRear();
    bool remove();
    bool remove(const T& elem);
    bool first(T& elem);
    bool last(T& elem);
    bool next(T& elem);
    bool previous(T& elem);
    int size() const;
    void printList();
    bool isEmpty() const;
    bool find(const T& elem);
    T& at(int pos);
    T& operator[](int pos);
    
private:

    struct Node
    {
        T data;
        Node* p_prev;
        Node* p_next;
    };
    Node* p_head;
    Node* p_tail;
    Node* p_current;
    int numElements;

};
template < typename T >DoublyLinkedList<T>::DoublyLinkedList()
{
        p_head = 0;
        p_tail = 0;
        p_current = 0;
        numElements = 0;
}
//--
template < typename T >DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& x)
{
        p_head = x.p_head;
        p_tail = x.p_tail;
        p_current = x.p_current;
        numElements = x.numElements;
}
//--
template < typename T >DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node* p_temp;

    for (;!isEmpty();)
    {
        p_temp = p_head;
        p_head = p_head->p_next;
        delete p_temp;                                      
        numElements--;
    }
}
//--
template < typename T >void DoublyLinkedList<T>::printList()
{
    p_current = p_head;
    Node* a = p_head;

    for (;a;)
    {
        cout<<a->data<<" ";
        a = a->p_next;
    }
    cout << endl;
}
//--
template < typename T >void DoublyLinkedList<T>::insertAtFront(const T& elem)
{
    Node* p_temp = new Node;
    p_temp->data = elem;
    p_temp->p_prev = NULL;

    if (!numElements)
    {
        p_temp->p_next = NULL;
        p_head = p_temp;
        p_tail = p_temp;
        p_current = p_head;
    }
    else
    {
        p_temp->p_next = p_head;
        p_head = p_temp;
        p_head->p_next->p_prev = p_head;
    }

    numElements++;
}
//--
template < typename T >void DoublyLinkedList<T>::insertAtRear(const T& elem)
{
    Node* p_temp = new Node;
    p_temp->data = elem;
    p_temp->p_next = NULL;

    if (!numElements)
    {
        p_temp->p_prev = NULL;
        p_head = p_temp;
        p_tail = p_temp;
        p_current = p_tail;
    }
    else
    {
        p_tail->p_next = p_temp;
        p_temp->p_prev = p_tail;
        p_tail = p_temp;
    }
    numElements++;
}
//--
template < typename T >bool DoublyLinkedList<T>::removeFromFront(T& elem)
{
    Node* p_temp;

    if (p_head == 0)
    {
        return false;
    } 

    if (p_tail == p_head)
    {
        elem = p_tail->data;
        delete p_tail;
        p_current = NULL;
        p_tail = NULL;
        p_head = NULL;
        numElements--;
        return true;
    }

    p_temp = p_head;
    p_head = p_temp->p_next;
    p_head->p_prev = NULL;
    elem = p_temp->data;
    delete p_temp;
    numElements--;
    return true;
}
//--
template < typename T >bool DoublyLinkedList<T>::removeFromRear()
{
    Node* p_temp;

    if (p_tail == 0)
    {
        return false;
    } 

    if (p_tail == p_head)
    {
        //elem = p_tail->data;
        delete p_tail;
        p_current = NULL;
        p_tail = NULL;
        p_head = NULL;
        numElements--;
        return true;
    }

    p_temp = p_tail;
    p_tail = p_temp->p_prev;
    p_tail->p_next = NULL;
    //elem = p_temp->data;
    delete p_temp;
    numElements--;
    return true;
}
//--
template < typename T >bool DoublyLinkedList<T>::remove()
{
    if (p_current == p_head)
    {
        if (p_current == p_tail)
        {
            delete p_current;
            p_current = NULL;
            p_tail = NULL;
            p_head = NULL;
            numElements--;
            return true;
        }

        Node* a = p_head;
        p_head->p_next->p_prev = NULL;
        p_head = p_head->p_next;
        delete a;
        p_current = p_head;
    }
    
    else if (p_current == p_tail)
    {
        Node* a = p_tail;
        p_tail->p_prev->p_next = NULL;
        p_tail = p_tail->p_prev;
        delete a;
        p_current = p_head;
    }

    else
    {
        p_current->p_next->p_prev = p_current->p_prev;
        p_current->p_prev->p_next = p_current->p_next;
        delete p_current;
        p_current = p_head;
    }
    numElements--;
    return true;
}
//--
template < typename T >bool DoublyLinkedList<T>::remove(const T& elem)
{
    bool retVal = false;
    Node* a = p_head;

    for (;a;)
    {
        if (a->data == elem)
        {
            p_current = a;
            remove();
            a = a->p_next;
            retVal = true;
        }
        else a = a->p_next;
    }
    return retVal;
}
//--
template < typename T >bool DoublyLinkedList<T>::first(T& elem)
{
    bool retVal = false;

    if (!isEmpty())
    {
        retVal = true;
        elem = p_head->data;
            p_current = p_head;
    }
    return retVal;
}
//--
template < typename T >bool DoublyLinkedList<T>::last(T& elem)
{
    bool retVal = false;

    if (!isEmpty())
    {
        retVal = true;
        elem = p_tail->data;
        p_current = p_tail;
    }
    return retVal;
}
//--
template < typename T >bool DoublyLinkedList<T>::next(T& elem)
{
    bool retVal = false;

    if (p_current->p_next != 0)
    {
        p_current = p_current->p_next;
        retVal = true;
        elem = p_current->data;     
    }
    return retVal;
}
//--
template < typename T >bool DoublyLinkedList<T>::previous(T& elem)
{
    bool retVal = false;

    if (p_current->p_prev != 0)
    {
        p_current = p_current->p_prev;
        retVal = true;
        elem = p_current->data;
    }
    return retVal;
}
//--
template < typename T >int DoublyLinkedList<T>::size() const
{
    return numElements;
}
//--
template < typename T >bool DoublyLinkedList<T>::isEmpty() const
{
    return(size() == 0);
}
//--
template < typename T >bool DoublyLinkedList<T>::find(const T& elem)
{
    p_current = p_head;
    Node* a = p_head;

    for (;a;)
    {
        if (a->data == elem) return true;
        a = a->p_next;
    }
    return false;
}
//--
template < typename T >T& DoublyLinkedList<T>::at(int pos)
{
    if (pos < 0 or pos > numElements)
    {
        string err = "You tried to access an element outside the bounds\n";
        throw err;
    }
    else
    {
        Node* a = p_head;

        for (int i = 0; i < pos; i++)
        {
            a = a->p_next;
        }
        return a->data;
    }
}
//--
template < typename T >T& DoublyLinkedList<T>::operator[](int pos)
{
    return at(pos);
}