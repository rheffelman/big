#pragma once
#include <iostream>
#include "StackError.h"
#include "DoublyLinkedList.h"
using namespace std;

template < typename T >
class Stack
{
public:

    void push(const T& elem);
    T pop();
    T top();
    bool isEmpty() const;
    int size() const;

private:

    DoublyLinkedList <T> list;

};
//--
template<typename T>void Stack<T>::push(const T& elem)
{
    list.insertAtRear(elem);
}
//--
template<typename T>T Stack<T>::pop()
{
    if (isEmpty())
    {
        StackError er("You've tried to pop an empty stack...moron");
        throw er;
    }

    T elem;
    list.removeFromRear(elem);
    return elem;
}
//--
template<typename T>T Stack<T>::top()
{
    if (isEmpty())
    {
        StackError er("You've tried to top an empty stack... moron");
        throw er;
    }

    T elem;
    list.last(elem);
    return elem;
}
//--
template<typename T>bool Stack<T>::isEmpty() const
{
    return (list.isEmpty());
}
//--
template<typename T>int Stack<T>::size() const
{
    return list.size();
}