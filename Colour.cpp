#include <iostream>
#include "Colour.h"


std::ostream& operator<<(std::ostream& os, Colour const& colour)
{
  os << "\e[38;2;" << colour.m_red << ";" << colour.m_green << ";" << colour.m_blue << "m";
  return os;
};
