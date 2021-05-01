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
  luminosity = clamp(UNSET, MAXCHANNELVALUE, luminosity);
  #if PRINTMODE == 3
  m_red_fg = 0;
  if (luminosity < WATERLEVEL) {
    m_green_fg = 0;
    m_blue_fg = luminosity;
  } else {
    m_green_fg = luminosity - WATERLEVEL / 2;
    m_blue_fg = 0;
  }
  #endif // PRINTMODE == 3
  #if PRINTMODE < 3
  m_red_fg = luminosity;
  m_green_fg = luminosity;
  m_blue_fg = luminosity;
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

    // Confine to -1~255
    val = clamp(UNSET, MAXCHANNELVALUE, val);

    // Assign to correct m_RGB
    if (i == 0) { m_red_fg = val; }
    else if (i == 1) { m_green_fg = val; }
    else { m_blue_fg = val; }
  }
};


std::string Colour::getAsText() const
{
  std::string temp;
  temp.reserve(19);
  if (m_red_fg != UNSET) {
    temp.append("\e[38;2;");
    temp.append(std::to_string(m_red_fg));
    temp.append(";");
    temp.append(std::to_string(m_green_fg));
    temp.append(";");
    temp.append(std::to_string(m_blue_fg));
    temp.append("m");
  } else {
    #if PRINTMODE == 3
    temp.append("\e[38;2;0;0;0m");
    #else
    temp.append("\e[0m");
    #endif
  }
  return temp;
};

std::ostream& operator<<(std::ostream& os, Colour const& colour)
{
  os << colour.getAsText();
  return os;
};

bool operator==(Colour const& left, Colour const& right) {
  return ((left.m_red_fg == right.m_red_fg) && (left.m_green_fg == right.m_green_fg) && (left.m_blue_fg == right.m_blue_fg) && (left.m_red_bg == right.m_red_bg) && (left.m_green_bg == right.m_green_bg) && (left.m_blue_bg == right.m_blue_bg));
};
