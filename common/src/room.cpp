#include "room.hpp"

#include <array>
#include <chrono>
#include <random>

void RotateLeft(std::bitset<4>& rot, int num) {
  for (int i = 0; i < num; ++i) {
    bool set_first = rot[3]?true:false;
    rot <<= 1;
    if(set_first) rot[0] = true;
  }
}
void RotateRight(std::bitset<4>& rot, int num) {
  for (int i = 0; i < num; ++i) {
    bool set_first = rot[0]?true:false;
    rot >>= 1;
    if(set_first) rot[3] = true;
  }
}

void Room::randomize(int comming_dir) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine random_engine (seed);
  std::discrete_distribution num_doors_distribution({1, 1, 1, 97});
  std::uniform_int_distribution rotation_distribution(1,3);
  int num_doors = num_doors_distribution(random_engine);

  outDoors.reset();
  for(int i=0; i<num_doors; i++) {
    int pos = 0;
    while (outDoors[pos]) {pos++;}
    outDoors[pos] = true;
    RotateLeft(outDoors, rotation_distribution(random_engine));
  }
  freePaths = outDoors;
  if (comming_dir != -1) {
    outDoors[comming_dir] = true;
    freePaths[comming_dir] = true;
  }
}


void Room::getAdyacentPos(int& x, int& y, int dir) {
  switch (dir) {
    case 0:
      y--;
      break;
    case 1:
      x++;
      break;
    case 2:
      y++;
      break;
    case 3:
      x--;
      break;
    default:
      break;
  }
}

int Room::getOpositeDir(const int dir) {
  int res = -1;
  switch (dir) {
    case 0:
      res = 2;
      break;
    case 1:
      res = 3;
      break;
    case 2:
      res = 0;
      break;
    case 3:
      res = 1;
      break;
    default:
      break;
  }
  return res;
}
