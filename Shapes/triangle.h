
///////////////////////////////////////////////////////////////////////////
// File: circle.h
// Purpose: Class definition of a circle.
///////////////////////////////////////////////////////////////////////////
#ifndef TRIANGLE_
#define TRIANGLE_

class triangle : public Shape {
    private:
        Triangle::Triangle(double S1, double S2, double S3){
          Side1 = S1;
          Side2 = S2;
          Side3 = S3;
        }
        float a, b, c, s, ar;
    public:
        void getData();
        float areaOfTriagle();
        float perOfTriangle();
};
#endif
