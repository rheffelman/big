#include <iostream>
#include <cassert> //for assert function
#include <string>
#include "SafeArrayInt.h"
#include "SafeArrayException.h"

using namespace std;

int main(){

    //create a safe array
    SafeArrayInt <double> s1;
    
    //verify that the number of used elements is 0
    assert(s1.index == 0);

    //add 3 items
    s1.push_back(10);
    s1.push_back(20);
    s1.push_back(30);
    
    //number of used elements is 3
    assert(s1.index == 3);

    //retrieve the values by position
    assert(s1.at(0) == 10);
    assert(s1.at(1) == 20);
    assert(s1.at(2) == 30);

    //verify the overloaded operator []    
    assert(s1[0] == 10);
    assert(s1[1] == 20);
    assert(s1[2] == 30);

    //update the first two with at()
    s1.at(0) = 50;
    s1.at(1) = 40;
    
    //verify
    assert(s1.index == 3);
    assert(s1.at(0) == 50);
    assert(s1.at(1) == 40);
    assert(s1.at(2) == 30);
    
    //adding 100 random numbers
    for(int i = 0; i < 100; i++)
    {
        s1.push_back(rand());
    }
    
    //verify
    assert(s1.index == 103);
    assert(s1.at(0) == 50); 
    assert(s1.at(1) == 40);
    assert(s1.at(2) == 30);
    
    //removing the last 100 random numbers
    for(int i = 0; i < 100; i++)
    {
        s1.pop_back();
    }
    
    //verify
    assert(s1.index == 3);
    assert(s1.at(0) == 50);
    assert(s1.at(1) == 40);
    assert(s1.at(2) == 30);
    
    //going outside the bounds, the program should end
    s1.at(3) = 40;
    cout<<"You should not see this on the screen!"<<endl;
    
    return 0;

}//remember, s1's destructor will be called here
//--

    // try{

    // } catch(exceptionType ex1){

    // } catch(exceptionType2 ex2){

    // }


    // if (pos < 0 or pos >= size()){
    //     string err = "Out of bounds";
    //     throw err;
    // }


    // template < class T >
    // int SafeArray < T >:: size(){
    //     return numElementsUsed;
    // }