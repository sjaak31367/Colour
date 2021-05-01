#pragma once

class Storage
{
 public:
  Storage(int sizeX, int sizeY, int sizeZ);
  ~Storage();
  double& operator() (int x, int y, int z);
 private:
  int m_sizeX;
  int m_sizeY;
  int m_sizeZ;
  double* m_storage;
};
