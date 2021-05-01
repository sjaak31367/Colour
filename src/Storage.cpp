#include <iostream>
#include <limits>
#include "Storage.h"

extern int clamp(int lo, int hi, int val); // main.cpp

Storage::Storage(int sizeX, int sizeY, int sizeZ)
{
  int max_int = std::numeric_limits<int>::max();
  m_sizeX = clamp(1, max_int, sizeX);
  m_sizeY = clamp(1, max_int, sizeY);
  m_sizeZ = clamp(1, max_int, sizeZ);
  m_storage = new double[m_sizeX * m_sizeY * m_sizeZ];
};

Storage::~Storage()
{
  delete m_storage;
};

double& Storage::operator() (int x, int y, int z)
{
  x = clamp(0, m_sizeX, x);
  y = clamp(0, m_sizeY, y);
  z = clamp(0, m_sizeZ, z);

  return m_storage[z * (m_sizeX * m_sizeY) + y * m_sizeX + x];
};
