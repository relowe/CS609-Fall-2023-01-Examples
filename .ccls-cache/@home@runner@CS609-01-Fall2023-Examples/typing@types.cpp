#include <iostream>

int main()
{
  int x;
  double y;
  char c;
  
  std::cout << 1 + 1.0 << std::endl;

  x = 7;
  y = x;
  std::cout << y << std::endl;

  y = 1.5;
  x = y;
  std::cout << x << std::endl;

  y = 65.9;
  c = y;
  std::cout << c << std::endl;
}