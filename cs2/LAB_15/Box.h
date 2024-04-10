#pragma once 
 
class Box 
{ 
public: 
    Box(); 
    Box(float h, float w); 
 
    void expand(float scalingFactor); 
    float getArea(); 
    float getPerimeter(); 
    void print(); 
 
    virtual void setHeight(float h); 
    float getHeight(); 
 
    virtual void setWidth(float w); 
    float getWidth(); 
private: 
    float height; 
    float width; 
};