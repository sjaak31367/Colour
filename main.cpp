#include <iostream>
#include <vector>
#include "PerlinNoise.hpp"
#include "Colour.h"

int main()
{
  #define TERM 1

  #if TERM == 0
  static const std::vector<int> terminalSize = {78, 62}; // School terminal size
  #endif // TERM == 0

  #if TERM == 1
  static const std::vector<int> terminalSize = {105, 50}; // Personal Raspi terminal size (1920 x 1017)
  #endif // TERM == 1

  std::vector<Colour> colours(255 * 255, Colour());
  const siv::PerlinNoise perlin(3512);
  int temp;

  // Generator
  for (int y = 0; y < 255; ++y) {
    for (int x = 0; x < 255; ++x) {
      // PerlinNoise(locationX [, locationY [, locationZ]], octave): returns double 0 ~ 1 (-0.04 ~ 0.96)
      temp = static_cast<int>( perlin.octaveNoise0_1(x / 32.f, y / 32.f, 8) * 256 );
      colours[y * 255 + x].set(temp, temp, temp);
      /* ColourMap / ColourWheel generator
      colours[y * 255 + x].set(x, y, ((x + y) / 2 - 128) * -1 + 127); */
    }
  }

  // 0: print RGB seperate
  // 1: print RGB combined
  #define PRINTMODE 1

  #if PRINTMODE == 0
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
  #endif // PRINTMODE == 0

  #if PRINTMODE == 1
  // RGB
  for (float y = 0; y < 255; y += (255.f / terminalSize[1])) {
    for (float x = 0; x < 255; x += (255.f / terminalSize[0])) {
      std::cout << colours[static_cast<int>(y) * 255 + static_cast<int>(x)] << "██";
    }
    std::cout << std::endl;
  }
  #endif // PRINTMODE == 1

  return 0;
}
