#include <iostream>
#include <vector>
#include "Colour.h"

int main()
{
  std::vector<Colour> colours(255 * 255, Colour());

  // Generator
  for (int y = 0; y < 255; ++y) {
    for (int x = 0; x < 255; ++x) {
      colours[y * 255 + x].set(x, y, ((x + y) / 2 - 128) * -1 + 127);
    }
  }

  // 0: print RGB seperate
  // 1: print RGB combined
  #define MODE 1

  #if MODE == 0
  // RED
  for (int y = 0; y < 255; y += 10) {
    for (int x = 0; x < 255; x += 10) {
      std::cout << Colour(red[y * 255 + x], 0, 0) << "██";
    }
    std::cout << std::endl;
  }

  // GREEN
  for (int y = 0; y < 255; y += 10) {
    for (int x = 0; x < 255; x += 10) {
      std::cout << Colour(0, green[y * 255 + x], 0) << "██";
    }
    std::cout << std::endl;
  }

  // BLUE
  for (int y = 0; y < 255; y += 10) {
    for (int x = 0; x < 255; x += 10) {
      std::cout << Colour(0, 0, blue[y * 255 + x]) << "██";
    }
    std::cout << std::endl;
  }
  #endif // MODE == 0

  #if MODE == 1
  // RGB
  for (int y = 0; y < 255; y += 5) {
    for (int x = 0; x < 255; x += 5) {
      std::cout << colours[y * 255 + x] << "██";
    }
    std::cout << std::endl;
  }
  #endif // Mode == 1

  return 0;
}
