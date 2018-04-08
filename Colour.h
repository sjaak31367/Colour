#pragma once
#include <iosfwd>

class Colour
{
 public:
  Colour(int red, int green, int blue);
  friend std::ostream& operator<<(std::ostream& os, Colour const& colour);
 private:
  int m_red = 0;
  int m_green = 0;
  int m_blue = 0;
};
