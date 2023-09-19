///////////////////////////////////////////////////////////////////////////
// File: shape.h
// Purpose: Class definition of a shape.
///////////////////////////////////////////////////////////////////////////
#ifndef SHAPE_H
#define SHAPE_H
class Shape
{
public:
    virtual double area()=0;
    virtual double perimeter()=0;
    virtual int number_sides()=0;
    virtual double side_length(int i)=0    ;
};
#endif