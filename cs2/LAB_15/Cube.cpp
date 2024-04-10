#include <iostream>
#include <cmath>

#include "Cube.h"
#include "Box.h"

using namespace std;

void Cube::setDepth(float d){
    depth = d;
    setHeight(d);
    setWidth(d);
}
//--
float Cube::getDepth(){
    return depth;
}
//--
float Cube::getVolume(){
    return pow(depth, 3);
}
//--
void Cube::expand(float scalingFactor){
    setDepth(depth * scalingFactor);
}
//--
void Cube::printCube(){
    printf("\nHeight: %.3f\n", getHeight());
    printf("Width: %.3f\n", getWidth());
    printf("Depth: %.3f\n", getDepth());
    printf("Volume: %.3f\n", getVolume());
}