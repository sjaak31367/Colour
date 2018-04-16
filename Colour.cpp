#include <iostream>
#include "Colour.h"

extern int clamp(int lo, int hi, int val); // main.cpp


Colour::Colour(int luminosity)
{
  set(luminosity);
};

Colour::Colour(int red, int green, int blue)
{
  set(red, green, blue);
};


void Colour::set(int luminosity)
{
  luminosity = clamp(0, 255, luminosity);
  m_red = luminosity;
  m_green = luminosity;
  m_blue = luminosity;
};

void Colour::set(int red, int green, int blue)
{
  int val;
  for (int i = 0; i < 3; ++i) {
    // RGB
    if (i == 0) { val = red; }
    else if (i == 1) { val = green; }
    else { val = blue; }

    // Confine to 0~255
    val = clamp(0, 255, val);

    // Assign to correct m_RGB
    if (i == 0) { m_red = val; }
    else if (i == 1) { m_green = val; }
    else { m_blue = val; }
  }
};

std::ostream& operator<<(std::ostream& os, Colour const& colour)
{
  os << "\e[38;2;" << colour.m_red << ";" << colour.m_green << ";" << colour.m_blue << "m";
  return os;
};
