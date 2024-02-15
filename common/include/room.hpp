#pragma once
#include <bitset>


struct Room {
  void randomize(int comming_dir);

  static void getAdyacentPos(int& x, int& y, int dir);
  static int getOpositeDir(const int dir);
  
  std::bitset<4> outDoors;
  std::bitset<4> freePaths;
  bool special = false;
  int x = 0;
  int y = 0;
};
