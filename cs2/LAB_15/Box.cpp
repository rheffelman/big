#include "Box.h" 
#include <iostream> 
 
using namespace std; 
 
Box::Box() 
{ 
    setHeight(10.0); 
    setWidth(10.0); 
} 
//-- 
Box::Box(float h, float w) 
{ 
    setHeight(h); 
    setWidth(w); 
} 
//-- 
void Box::expand(float scalingFactor) 
{ 
    setHeight(getHeight() * scalingFactor); 
    setWidth(getWidth() * scalingFactor); 
} 
//-- 
void Box::print() 
{ 
    cout<<"Box height: "<<getHeight()<<endl; 
    cout<<"Box width: "<<getWidth()<<endl; 
    cout<<"Box area: "<<getArea()<<endl; 
    cout<<"Box perimeter: "<<getPerimeter()<<endl; 
 
    for(int row = 1;row <= getHeight();row++) 
    { 
        for(int col = 1;col <= getWidth();col++) 
        { 
            if(row == 1 || col == 1 || row == getHeight() || col == getWidth()) 
            { 
                cout<<"*"; 
            } 
            else 
            { 
                cout<<" "; 
            } 
        } 
        cout<<endl; 
    } 
} 
//-- 
float Box::getPerimeter() 
{ 
    return (2.0 * getHeight()) + (2.0 * getWidth()); 
} 
//-- 
float Box::getArea() 
{ 
    return getHeight() * getWidth(); 
} 
//-- 
void Box::setHeight(float h) 
{ 
    if(h > 0.0) 
    { 
        height = h; 
    } 
    else 
    { 
        height = 1.0; 
    } 
} 
//-- 
float Box::getHeight() 
{ 
    return height; 
} 
//-- 
void Box::setWidth(float w) 
{ 
    if(w > 0.0) 
    { 
        width = w; 
    } 
    else 
    { 
        width = 1.0; 
    } 
} 
//-- 
float Box::getWidth() 
{ 
    return width; 
} 
