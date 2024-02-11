#pragma once
#include <bitset>
#include <iostream>
#include <ppltasks.h>
#include <queue>
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
  std::bitset<4> freePaths;
  int x = 0;
  int y = 0;

  void randomize(int comming_dir) {
    outDoors = 0 + rand() % 32;
    freePaths = outDoors;
    if (comming_dir != -1) {
      outDoors[comming_dir] = true;
      freePaths[comming_dir] = true;
    }

  }

  static void getAdyacentPos(int& x, int& y, int dir) {
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
  static int getOpositeDir(const int dir) {
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
};

class Maze {
public:
  Maze(int w, int h, int total)
    : width(w),
      height(h),
      start_x(0 + rand() % w),
      start_y(0 + rand() % h),
      room_count(total) {
    for (int i = 0; i < w * h; ++i) {
      maze.emplace_back(Room());
    }
  }

  int getPos(int x, int y) const {
    return x + y * width;
  }
  Room& getRoom(int x, int y) {
    return maze.at(x + y * width);
  }
  Room& getAdyacentRoom(int x, int y, int direction) {
    Room::getAdyacentPos(x, y, direction);
    return maze.at(x + y * width);
  }

  bool isValid(int x, int y, int comming_dir, bool path_needed) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
      if (path_needed) return false;
      return true;
    }

    Room& checking_room = maze.at(getPos(x, y));
    if (checking_room.outDoors.none()) {
      return true;
    }
    if (path_needed) {
      if (checking_room.freePaths[comming_dir]) {
        return true;
      }
      return false;
    } else {
      if (checking_room.freePaths[comming_dir]) {
        return false;
      }
    }
    return true;
  }


  void print() const {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        char t = ' ';
        switch (maze.at(getPos(x, y)).outDoors.count()) {
          case 0:
            t = '0';
            break;
          case 1:
            t = '1';
            break;
          case 2:
            t = '2';
            break;
          case 3:
            t = '3';
            break;
          case 4:
            t = '4';
            break;
          default:
            break;
        }
        std::cout << " " << t << " ";
      }
      std::cout << "\n";
    }
    std::cout << "----------------------------------------------" << std::endl;
  }


  void Generate() {
    int curr_x = start_x;
    int curr_y = start_y;

    placeRoom(curr_x, curr_y, -1);
    while (!queue.empty()) {
      print();
      //getting the last available form the queue
      bool empty = false;
      Room* placed_room = queue.front();
      while (placed_room->freePaths.none()) {
        queue.pop();
        if (queue.empty()) {
          empty = true;
          break;
        }
        placed_room = queue.front();
      }
      if (empty) break;
      curr_x = placed_room->x;
      curr_y = placed_room->y;
      //find random dir available for the last room placed
      int next_dir = 0 + rand() % 4;
      while (!placed_room->freePaths[next_dir]) {
        next_dir--;
        if (next_dir < 0) next_dir = 3;
      }
      Room::getAdyacentPos(curr_x, curr_y, next_dir);

      placeRoom(curr_x, curr_y, Room::getOpositeDir(next_dir));
    }
  }

  bool roomCanFit(Room& room, int room_x, int room_y) {
    bool res = true;
    for (int i = 0; i < 4; i++) {
      int adjacent_x = room_x;
      int adjacent_y = room_y;
      Room::getAdyacentPos(adjacent_x, adjacent_y, i);

      if (!isValid(adjacent_x, adjacent_y, Room::getOpositeDir(i),
                   room.freePaths[i])) {
        res = false;
        break;
      }
    }
    if (res) {
      for (int i = 0; i < 4; i++) {
        int adjacent_x = room_x;
        int adjacent_y = room_y;
        Room::getAdyacentPos(adjacent_x, adjacent_y, i);
        if (room.freePaths[i]) {
          Room& checking_room = getAdyacentRoom(room_x, room_y, i);
          if (checking_room.outDoors[Room::getOpositeDir(i)]) {
            room.freePaths[i] = false;
            checking_room.freePaths[Room::getOpositeDir(i)] = false;
          }
        }
      }
    }

    return res;
  }

  void placeRoom(int x, int y, int comming_dir) {
    Room& current = getRoom(x, y);
    current.x = x;
    current.y = y;
    do {
      current.randomize(comming_dir);
    }
    while (!roomCanFit(current, x, y));

    queue.push(&current);
  }

private:
  int width, height;
  int start_x, start_y;
  int room_count;
  std::vector<Room> maze;
  std::queue<Room*> queue;
};
