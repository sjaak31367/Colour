#pragma once
#include <iosfwd>
#include <string>

#define CHANNELSIZE 256
#define MAXCHANNELVALUE CHANNELSIZE - 1
#define UNSET -1

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
  friend bool operator==(Colour const& left, Colour const& right);
 private:
  // Foreground
  int m_red_fg   = UNSET;
  int m_green_fg = UNSET;
  int m_blue_fg  = UNSET;
  // Background
  int m_red_bg   = UNSET;
  int m_green_bg = UNSET;
  int m_blue_bg  = UNSET;
};
