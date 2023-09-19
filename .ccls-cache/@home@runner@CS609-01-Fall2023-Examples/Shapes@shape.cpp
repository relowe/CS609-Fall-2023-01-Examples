#include <iostream>
#include <string>
#include "shape.h"
#include "triangle.h"

void triangle::getData()
{
    cout<<"Enter Length of all Three Sides: ";
    cin>>a>>b>>c;
}
float triangle::areaOfTriagle()
{
    s = (a+b+c)/2;
    ar = sqrt(s*(s-a)*(s-b)*(s-c));
    return ar;
}
float traingle::perOfTriangle()
{
    return (a+b+c);
}