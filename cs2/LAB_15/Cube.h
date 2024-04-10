#pragma once

#include "Box.h"

class Cube : public Box
{
public: 
    void setDepth(float d);
    float getDepth();
    float getVolume();
    void expand(float scalingFactor);
    void printCube();
private:
    float depth;
};