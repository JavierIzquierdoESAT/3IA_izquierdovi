#include "room.hpp"

void Room::randomize(int comming_dir) {
  outDoors = 0 + rand() % 32;
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
