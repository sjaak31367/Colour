#include <iostream>
#include "Colour.h"

int main()
{
  //std::cout << Colour(255, 0, 127) << "PURPLE!" << std::endl;
  for (int y = 0; y < 255; y += 5) {
    for (int x = 0; x < 255; x += 5) {
      std::cout << Colour(x,y,0) << "██";
    }
    std::cout << std::endl;
  }
  return 0;
}
