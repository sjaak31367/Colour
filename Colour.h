#pragma once
#include <iosfwd>
#include <string>

#define CHANNELSIZE 256
#define MAXCHANNELVALUE CHANNELSIZE - 1

class Colour
{
 public:
  Colour(int luminosity);
  Colour(int red, int green, int blue);
  Colour() {};

  void set(int luminosity);
  void set(int red, int green, int blue);

  std::string getAsText() const;
  friend std::ostream& operator<<(std::ostream& os, Colour const& colour);
 private:
  int m_red = 0;
  int m_green = 0;
  int m_blue = 0;
};
