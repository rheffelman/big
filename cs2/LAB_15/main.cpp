#include <iostream> 
#include "Box.h"
#include "Cube.h"
 
using namespace std; 

int main() 
{ 
    // Box b1; 
    // b1.setHeight(3.0); 
    // b1.setWidth(8.0); 
    // b1.print(); 
    // b1.expand(3.0); 
    // b1.print(); 
 
    // Box b2(20.0, 20.0); 
    // b2.print(); 

    Cube c1;
    c1.setDepth(5.0);
    c1.printCube();
    
    Cube c2;
    c2.setDepth(20.0);
    c2.printCube();
    
    c2.expand(3.0);
    c2.printCube();
    return 0; 
}