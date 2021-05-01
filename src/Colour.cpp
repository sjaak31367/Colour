#include <iostream>
#include "config.h"
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
  luminosity = clamp(0, MAXCHANNELVALUE, luminosity);
  #if PRINTMODE == 3
  if (luminosity < WATERLEVEL) {
    m_blue = luminosity;
  } else {
    m_green = luminosity - WATERLEVEL / 2;
  }
  #endif // PRINTMODE == 3
  #if PRINTMODE < 3
  m_red = luminosity;
  m_green = luminosity;
  m_blue = luminosity;
  #endif // PRINTMODE < 3
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
    val = clamp(0, MAXCHANNELVALUE, val);

    // Assign to correct m_RGB
    if (i == 0) { m_red = val; }
    else if (i == 1) { m_green = val; }
    else { m_blue = val; }
  }
};


std::string Colour::getAsText() const
{
  std::string temp;
  temp.reserve(19);
  temp.append("\e[38;2;");
  temp.append(std::to_string(m_red));
  temp.append(";");
  temp.append(std::to_string(m_green));
  temp.append(";");
  temp.append(std::to_string(m_blue));
  temp.append("m");
  return temp;
};

std::ostream& operator<<(std::ostream& os, Colour const& colour)
{
  os << colour.getAsText();
  return os;
};
