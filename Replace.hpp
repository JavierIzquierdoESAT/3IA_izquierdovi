#pragma once
#include <bitset>
#include <ppltasks.h>
#include <string>
#include <vector>

enum class rType {
  none,
  plaza,
  tJunction,
  corridor,
  turn,
  deadEnd
};


struct Room {
  // rType type;
  // int clockwise_rotations;
  // int doors_number;
  std::bitset<4> outDoors;

  void randomize() {
    outDoors = 0 + rand() % 32;
  }
};

class Maze {
  Maze(int w, int h, int total)
    : width(w),
      height(h),
      start_x(0 + rand() % w),
      start_y(0 + rand() % h),
      room_count(total) {}

  int getPos(int x, int y) { return x + y * width; }
  
  bool isValid(int x, int y) {
    if (start_x - 1 < 0 || start_x + 1 >= width ||
        start_y - 1 < 0 || start_y + 1 >= height) {
      return false;
    }
    if( maze.at(getPos(x, y)).outDoors.any() ) {
      return true;
    }
    return false;
  }
  
  void Generate() {
    int curr_x = start_x;
    int curr_y = start_y;
    int i = 0;
    while(i < room_count) {
      Room current = maze.at(getPos(curr_x, curr_y));
      bool bad = false;
      while (bad) {
        current.randomize();
        if (current.outDoors[0]) {
          if (!isValid(start_x, start_y - 1)) {
            bad = true;
          }
        }
        if (current.outDoors[1]) {
          if (!isValid(start_x + 1, start_y)) {
            bad = true;
          }
        }
        if (current.outDoors[2]) {
          if (!isValid(start_x, start_y + 1)) {
            bad = true;
          }
        }
        if (current.outDoors[3]) {
          if (!isValid(start_x - 1, start_y)) {
            bad = true;
          }
        }
      }
      
      i++;
    }
  }
  void placeRoom(int x, int y) {
    
  }

private
:
  int width, height;
  int start_x, start_y;
  int room_count;
  std::vector<Room> maze;
};
