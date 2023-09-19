///////////////////////////////////////////////////////////////////////////
// File: circle.h
// Purpose: Class definition of a circle.
///////////////////////////////////////////////////////////////////////////
#ifndef CIRCLE_H
#define CIRCLE_H
class Circle: public Shape
{
    virtual double area()=0;
    virtual double perimeter()=0;
    virtual int number_sides()=0;
    virtual double side_length(int i)=0;
};
#endif