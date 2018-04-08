#include <iostream>
#include "Colour.h"

Colour::Colour(int red, int green, int blue)
{
  for (int i = 0; i < 3; ++i) {
    int val = 128;

    // RGB
    if (i == 0) { val = red; }
    else if (i == 1) { val = green; }
    else { val = blue; }

    // Confide to 0~255
    if (0 < val > 255) {
      if (val < 0) { val = 0; }
      else { val = 255;}
    }

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
