#include <iostream> 
#include <string>
#include "shape.h"

class Circle : public Shape
{
public:
    virtual double area();
    virtual double perimeter();
    virtual int number_sides();
    virtual double side_length (int number_sides);
};
double rad = 0.0;

int main()
{
    Shape *sh;
    sh = new Circle();

    // double rad;
    std::cout << "Radius: ";
    std::cin >> rad;
    
    sh->area();
    sh->perimeter();
    sh->number_sides();
    sh->side_length(0);

    delete sh;
}


// implementation
double Circle::area() 
{
  // double rad;
  double area = (22*rad*rad)/7;
  std::cout << "Area of Circle: " << area << std::endl;
  return 0.00;
}

double Circle::perimeter() 
{
  double perimeter = 2*3.14*rad;
  std::cout << "Perimeter of Circle: " << perimeter << std::endl;
  return 0.00;
}

int Circle::number_sides() 
{
  std::cout << "Number of sides of Circle is 0" << 0 << std::endl;
  return 0;
}

double Circle::side_length(int i) 
{
  std::cout << "Side Length of Circle" << std::endl;
  return 0.00;
}
