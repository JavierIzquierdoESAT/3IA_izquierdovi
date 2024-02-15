#include "room.hpp"

void Room::randomize(int comming_dir) {
  int path_count = 1 + rand() % 4;
  outDoors.reset();
  for (int i = 0; i < path_count; ++i) {
    int pos = 0;
    while (outDoors[pos]) {pos++;}
    outDoors[pos] = true;
    outDoors <<= rand() % 4;
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
