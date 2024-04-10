#include <iostream>
#include <ctime>
#include <cassert>
#include "DoublyLinkedList.h"

using namespace std;

void verifyLinksInBothDirections(DoublyLinkedList < int >& list);
void randomNumbersInsert();
void randomNumbersRemove();
void randomNumbersInsertAndRemove();
void simpleList();

//some constants so that I can experiment with my tests
const int NUM_ITERATIONS = 1000;
const int SCALE_FACTOR = 100;

int main()
{
    cout << "Doubly Linked List Driver" << endl;
    //use different random numbers each time
    srand(time(0));
    //use the same random numbers from one run to another
    //srand(0);
    
    //test very basic stuff
    simpleList();
    
    //really try and break it with random inserts and removes
    for (int i = 0; i < 100; i++)
    {
        cout << "iteration: " << (i + 1) << " " << endl;
        randomNumbersInsert();
        randomNumbersRemove();
        randomNumbersInsertAndRemove();
    }
    cout << "Done" << endl;
    return 0;
}
//--
void simpleList()
{
    //create a list
    DoublyLinkedList < int > list;
    
    //do some inserts
    list.insertAtRear(20);  //20
    list.insertAtFront(10); //10 20
    list.insertAtRear(30);  //10 20 30
    list.insertAtRear(25);  //10 20 30 25
    list.insertAtRear(5);   //10 20 30 25 5
    list.insertAtFront(20); //20 10 20 30 25 5
    list.insertAtRear(20);  //20 10 20 30 25 5 20
    list.insertAtRear(40);  //20 10 20 30 25 5 20 40
    list.insertAtFront(15); //15 20 10 20 30 25 5 20 40
    list.insertAtFront(5);  //5 15 20 10 20 30 25 5 20 40
    list.insertAtRear(40);  //5 15 20 10 20 30 25 5 20 40 40
    
    assert(list.find(20));
    assert(list.find(10));
    assert(list.find(30));
    assert(list.find(25));
    assert(list.find(5));
    assert(list.find(40));
    assert(list.find(15));

    assert(!list.find(-20));
    assert(!list.find(-10));
    assert(!list.find(-30));
    assert(!list.find(-25));
    assert(!list.find(-5));
    assert(!list.find(-40));
    assert(!list.find(-15));

    assert(list.at(9) == 40);
    assert(list.at(0) == 5);
    assert(list.at(3) == 10);
    assert(list.at(2) == 20);
    assert(list.at(4) == 20);

    try
    {
        list.at(100);
        assert(false);
    }
    catch (...) //catch any type of exception here
    {
        //do nothing, this should happen
    }
    
    //verify
    verifyLinksInBothDirections(list);
    
    //remove some elements
    list.remove(25); //5 15 20 10 20 30 5 20 40 40
    assert(list.size() == 10);
    list.remove(5);  //15 20 10 20 30 20 40 40
    assert(list.size() == 8);
    list.remove(20); //15 10 30 40 40
    assert(list.size() == 5);
    list.remove(10); //15 30 40 40
    assert(list.size() == 4);
    list.remove(40); //15 30
    assert(list.size() == 2);
    
    //verify
    verifyLinksInBothDirections(list);
    
    //remove some elements
    list.remove(3000); //15 30
    assert(list.size() == 2);
    list.remove(15); //30
    assert(list.size() == 1);
    list.remove(30); //empty
    assert(list.size() == 0);

    //verify
    verifyLinksInBothDirections(list);
    
    list.insertAtFront(20); //20
    assert(list.size() == 1);
    list.insertAtRear(10);  //20 10
    assert(list.size() == 2);
    list.insertAtFront(30); //30 20 10
    assert(list.size() == 3);
    list.insertAtFront(25); //25 30 20 10
    assert(list.size() == 4);
    
    //verify
    verifyLinksInBothDirections(list);
    
    int x;
    list.removeFromFront(x); //30 20 10
    assert(x == 25);
    assert(list.size() == 3);
    list.removeFromRear(x);  //30 20
    assert(x == 10);
    assert(list.size() == 2);
    list.removeFromFront(x); //20
    assert(x == 30);
    assert(list.size() == 1);
    list.removeFromRear(x);
    assert(x == 20);
    assert(list.size() == 0);
    
    //verify
    verifyLinksInBothDirections(list);
}
//--
void verifyLinksInBothDirections(DoublyLinkedList < int >& list)
{
    //make sure we read all of the elements, count them and compare to the length
    int count = 0;
    //loop through all the elements
    int data;
    if (list.first(data))
    {
        //count the read
        count++;
        while (list.next(data))
        {
            //count the read
            count++;
        }
    }
    //make sure there were the same number of reads as elements
    assert(count == list.size());
    
    //now go in reverse
    count = 0;
    if (list.last(data))
    {
        count++;
        while (list.previous(data))
        {
            count++;
        }
    }
    //check the count
    assert(count == list.size());
}
//--
void randomNumbersInsert()
{
    //create a list
    DoublyLinkedList < int > list;
    //add random integers to it
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        //pick a random number
        int num = rand();
        //if it is even
        if (num % 2 == 0)
        {
            //insert it at the front
            list.insertAtFront(num);
        }
        else //it is odd
        {
            //insert it at the rear
            list.insertAtRear(num);
        }
        //verify
        verifyLinksInBothDirections(list);
    }
}
//--
void randomNumbersRemove()
{
    //create a list
    DoublyLinkedList < int > list;
    //add some random numbers
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        //scale down to numbers between 0-(SCALE_FACTOR-1)
        list.insertAtRear(rand() % SCALE_FACTOR);
    }
    int data;
    //go through all the elements and remove the evens
    if (list.first(data))
    {
        //if the number is even
        if (data % 2 == 0)
        {
            //remove it
            list.remove();
        }
        //go through the rest of the numbers and do the same
        while (list.next(data))
        {
            if (data % 2 == 0)
            {
                list.remove();
            }
        }
        //verify
        verifyLinksInBothDirections(list);
    }
    //while the list is not empty
    while (!list.isEmpty())
    {
        //attempt to remove a random number
        list.remove(rand() % SCALE_FACTOR);
    }
    //verify
    verifyLinksInBothDirections(list);
}
//--
void randomNumbersInsertAndRemove()
{
    //create a list
    DoublyLinkedList < int > list;
    //mix inserts and removes
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        //flip a coin- insert
        if (rand() % 2 == 0)
        {
            //flip a coin
            if (rand() % 2 == 0)
            {
                //insert a random number at front
                list.insertAtFront(rand() % SCALE_FACTOR);
            }
            else
            {
                //insert a random number at rear
                list.insertAtRear(rand() % SCALE_FACTOR);
            }
            //verify
            verifyLinksInBothDirections(list);
        }
        else//flip a coin- remove
        {
            //attempt to remove a random number
            list.remove(rand() % SCALE_FACTOR);
            //verify
            verifyLinksInBothDirections(list);
        }
    }
    //while the list is not empty
    while (!list.isEmpty())
    {
        //attempt to remove a random number
        list.remove(rand() % SCALE_FACTOR);
        //verify
        verifyLinksInBothDirections(list);
    }
}