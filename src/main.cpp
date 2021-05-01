#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <cmath>
#include "config.h"
#include "PerlinNoise.hpp"
#include "Colour.h"
#include "Storage.h"


int seed = 3512;

#if PRINTMODE == 1
#include <vector>
std::vector<Colour> colours(255 * 255, Colour());
#endif // PRINTMODE == 1

#if PRINTMODE == 3
double radius = 23.45;
#endif // PRINTMODE == 3

#if PRINTMODE == 2 || PRINTMODE == 3
Storage storage(STORAGESIZEX, STORAGESIZEY, STORAGESIZEZ);
#endif // PRINTMODE == 2 || PRINTMODE == 3



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
  const siv::PerlinNoise perlin(seed);

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
        storage(x,y,z) = perlin.octaveNoise0_1(x/32.f, y/32.f, z/32.f, 8);
      }
    }
  }
  // unoptimised : optimised -O3
  // Home   4633 : 1719
  // School    ? : ?
  std::cout << " Time spent generating: " << (std::clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 2

  #if PRINTMODE == 3
  std::clock_t startTime = std::clock();
  int ax; // Adjusted Axis
  int ay; // Eyy
  for (int x = 0; x < STORAGESIZEX; ++x) {
    for (int y = 0; y < STORAGESIZEY; ++y) {
      for (int z = 0; z < STORAGESIZEZ; ++z) {
        ax = x - TERMINALSIZEX / 2;
        ay = y - TERMINALSIZEY / 2;
        if (std::sqrt(std::pow(ax,2) + std::pow(ay,2) + std::pow(z,2)) <= radius) {
          storage(x,y,z) = perlin.octaveNoise0_1(x/32.f, y/32.f, z/64.f, 12);
          //storage(x,y,z) = (double)z / (double)STORAGESIZEZ; // Use this too see how far away a "pixel" is from the camera.
        }
      }
    }
  }
  // unoptimised : optimised -O3
  // Home    495 : 199
  // School    ? : ?
  std::cout << " Time spent generating: " << (std::clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 3

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

  for (int z = 0; z < STORAGESIZEZ; z += 4) {
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
  std::cout << "\e[38;2;255;255;255m" << "\e[48;2;0;0;0m";
  // unoptimised : optimised -O3
  // Home     59 : 49
  // School    ? : ?
  std::cout << " Average computing time per frame: " << ((std::clock() - startTime) / framesPrinted) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 2

  #if PRINTMODE == 3
  // 3D planet (v1)
  std::array<Colour, TERMINALSIZEX * TERMINALSIZEY> tempstorage;
  int val;

  std::clock_t startTime = std::clock();

  // NOTE: Reversely going through the z direction, only storing the first found value
  // and then stop checking at that x,y would be faster, but I've already implemented this and it's fast enough IMO.
  for (int z = 0; z < STORAGESIZEZ; ++z) {
    for (int y = 0; y < STORAGESIZEY; ++y) {
      for (int x = 0; x < STORAGESIZEX; ++x) {
        val = static_cast<int>(storage(x,y,z) * CHANNELSIZE);
        if (val != 0) {
          tempstorage[y * TERMINALSIZEX + x] = val; // TODO WHY ARE YOU COLOUR STORAGE FOR INTS?
        }
      }
    }
  }
  for (int y = 0; y < STORAGESIZEY; ++y) {
    for (int x = 0; x < STORAGESIZEX; ++x) {
      std::cout << Colour(tempstorage[y * TERMINALSIZEX + x]) << "██"; // TODO FIX THIS!
    }
    std::cout << std::endl;
  }
  std::cout << "\e[38;2;255;255;255m" << "\e[48;2;0;0;0m";
  // unoptimised : optimised -O3
  // Home     54 : 35
  // School    ? : ?
  std::cout << " Computing time spent on frame: " << (std::clock() - startTime) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  #endif // PRINTMODE == 3

  std::cout << " RENDERER DONE!" << std::endl;
}

int main()
{
  std::cout << "int seed = ";
  std::cin >> seed;
  generate();
  render();
  return 0;
}
