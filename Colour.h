#pragma once
#include <iosfwd>

class Colour
{
 public:
  Colour(int red, int green, int blue) : m_red(red), m_green(green), m_blue(blue) {};
  friend std::ostream& operator<<(std::ostream& os, Colour const& colour);
 private:
  int m_red;
  int m_green;
  int m_blue;
};
