#include "grid.hpp"
#include "room.hpp"

#include <iostream>

Maze::Maze(int w, int h, int total): width(w),
                                     height(h),
                                     start_x(0 + rand() % w),
                                     start_y(0 + rand() % h),
                                     room_count(total) {
  for (int i = 0; i < w * h; ++i) {
    maze.emplace_back(Room());
  }
}
int Maze::getPos(int x, int y) const {
  return x + y * width;
}
Room& Maze::getRoom(int x, int y) {
  return maze.at(x + y * width);
}
Room& Maze::getAdyacentRoom(int x, int y, int direction) {
  Room::getAdyacentPos(x, y, direction);
  return maze.at(x + y * width);
}
bool Maze::isValid(int x, int y, int comming_dir, bool path_needed) {
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

void Maze::print() const {
  for (int y = 0; y < height; ++y) {
    //top
    for (int x = 0; x < width; ++x) {
      std::string t;
      if(maze.at(getPos(x, y)).outDoors[0]) t += "   |   ";
      else t += "       ";
      std::cout << t ;
    }
    std::cout << "\n";
    //middle
    for (int x = 0; x < width; ++x) {
      std::string t;
      if(maze.at(getPos(x, y)).outDoors[3]) t += "---";
      else t+= "   ";
      switch (maze.at(getPos(x, y)).outDoors.count()) {
        case 0:
          t += '0';
        break;
        case 1:
          t += '1';
        break;
        case 2:
          t += '2';
        break;
        case 3:
          t += '3';
        break;
        case 4:
          t += '4';
        break;
        default:
          break;
      }
      if(maze.at(getPos(x, y)).outDoors[1]) t += "---";
      else t += "   ";
      
      std::cout << t ;
    }
    std::cout << "\n";

    //bottom
    for (int x = 0; x < width; ++x) {
      std::string t = "";
      if(maze.at(getPos(x, y)).outDoors[2]) t += "   |   ";
      else t += "       ";
      std::cout << t ;
    }
    std::cout << "\n";
  }
  std::cout << "----------------------------------------------" << std::endl;
}
void Maze::Generate() {
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
bool Maze::roomCanFit(Room& room, int room_x, int room_y) {
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
void Maze::placeRoom(int x, int y, int comming_dir) {
  Room& current = getRoom(x, y);
  current.x = x;
  current.y = y;
  do {
    current.randomize(comming_dir);
  }
  while (!roomCanFit(current, x, y));

  queue.push(&current);
}
