#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include "PerlinNoise.hpp"
#include "Colour.h"
#include "Storage.h"


// 1: print RGB combined
// 2: print 3D stuff
#define PRINTMODE 2

// Terminal Window size in chars devided by 2
#define TERMINALSIZEX 105 //50  // Home : School
#define TERMINALSIZEY 50 //61   // Home : School

#if PRINTMODE == 1
std::vector<Colour> colours(255 * 255, Colour());
#endif // PRINTMODE == 1

#if PRINTMODE == 2
#define STORAGESIZEX TERMINALSIZEX
#define STORAGESIZEY TERMINALSIZEY
#define STORAGESIZEZ 100
Storage storage(STORAGESIZEX, STORAGESIZEY, STORAGESIZEZ);
#endif // PRINTMODE == 2


// Functions
int clamp(int lo, int hi, int val)
{
  if (val < lo || val > hi) {
    if (val < lo) { val = lo; }
    else { val = hi; }
  }
  return val;
}

void generate()
{
  std::cout << "GENERATOR STARTED!" << std::endl;
  const siv::PerlinNoise perlin(3512);

  #if PRINTMODE == 1
  for (int y = 0; y < 255; ++y) {
    for (int x = 0; x < 255; ++x) {
      // PerlinNoise(locationX [, locationY [, locationZ]], octave): returns double 0 ~ 1 (-0.04 ~ 0.96)
      colours[y * 255 + x].set( static_cast<int>(perlin.octaveNoise0_1(x / 32.f, y / 32.f, 8) * 256) );
      /* ColourMap / ColourWheel generator
      colours[y * 255 + x].set(x, y, ((x + y) / 2 - 128) * -1 + 127); */
    }
  }
  #endif // PRINTMODE == 1

  #if PRINTMODE == 2
  std::clock_t startTime = std::clock();
  for (int x = 0; x < STORAGESIZEX; ++x) {
    for (int y = 0; y < STORAGESIZEY; ++y) {
      for (int z = 0; z < STORAGESIZEZ; ++z) {
        storage(x,y,z) = perlin.octaveNoise0_1(x/64.f, y/64.f, z/64.f, 8);
      }
    }
  }
  // unoptimised : optimised -O3
  // Home   4633 : 1719
  // School    ? : ?
  std::cout << " Time spent generating: " << (std::clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 2

  std::cout << " GENERATOR DONE!" << std::endl;
}

void render()
{
  std::cout << "RENDERER STARTED!" << std::endl;

  #if PRINTMODE == 1
  // RGB
  for (float y = 0; y < 255; y += (255.f / TERMINALSIZEY)) {
    for (float x = 0; x < 255; x += (255.f / TERMINALSIZEX)) {
      std::cout << colours[static_cast<int>(y) * 255 + static_cast<int>(x)] << "██";
    }
    std::cout << std::endl;
  }
  #endif // PRINTMODE == 1

  #if PRINTMODE == 2
  // 3D stuff
  std::string framebuffer;
  framebuffer.reserve(TERMINALSIZEY * TERMINALSIZEX * 21 + TERMINALSIZEY + 1);

  std::clock_t startTime = std::clock();
  int framesPrinted = 0;

  for (int z = 0; z < STORAGESIZEZ; z += 5) {
    for (int y = 0; y < STORAGESIZEY; ++y) {
      for (int x = 0; x < STORAGESIZEX; ++x) {
        framebuffer.append(Colour(static_cast<int>(storage(x,y,z) * CHANNELSIZE)).getAsText());
        framebuffer.append("██");
      }
      framebuffer.append("\n");
    }
    std::cout << framebuffer << std::flush;
    ++framesPrinted;
    framebuffer.clear();
    framebuffer.append("\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  std::cout << "\e0m"; // Reset colours
  // unoptimised : optimised -O3
  // Home     59 : 49
  // School    ? : ?
  std::cout << " Average computing time per frame: " << ((std::clock() - startTime) / framesPrinted) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 2

  std::cout << " RENDERER DONE!" << std::endl;
}

int main()
{
  generate();
  render();
  return 0;
}
