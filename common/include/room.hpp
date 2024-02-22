#pragma once
#include <bitset>
#include <esat/sprite.h>


struct Room {
  Room() = default;
  Room(esat::SpriteHandle sp):sprite(sp){}
  
  void randomize(int comming_dir);

  static void getAdyacentPos(int& x, int& y, int dir);
  static int getOpositeDir(const int dir);

  esat::SpriteHandle sprite;
  int rotations = 0;
  
  std::bitset<4> outDoors;
  std::bitset<4> freePaths;
  bool special = false;
  int x = 0;
  int y = 0;
};



