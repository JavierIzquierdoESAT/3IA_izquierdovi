#include "grid.hpp"
#include "room.hpp"
#include "esat/sprite.h"

#include <iostream>

#include "room_pool.hpp"

Maze::Maze(int w, int h, int total, int special_room): width(w),
  height(h),
  start_x(0 + rand() % w),
  start_y(0 + rand() % h),
  special_rooms(3),
  room_count(total) {
  for (int i = 0; i < w * h; ++i) {
    maze.emplace_back(Room());
  }
  LevelPool();
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
      if (maze.at(getPos(x, y)).outDoors[0]) t += "   |   ";
      else t += "       ";
      std::cout << t;
    }
    std::cout << "\n";
    //middle
    for (int x = 0; x < width; ++x) {
      std::string t;
      if (maze.at(getPos(x, y)).outDoors[3]) t += "---";
      else t += "   ";
      if (maze.at(getPos(x, y)).outDoors.none()) { t += ' '; } else if (maze.
        at(getPos(x, y)).special) { t += '*'; } else { t += "&"; }
      if (maze.at(getPos(x, y)).outDoors[1]) t += "---";
      else t += "   ";

      std::cout << t;
    }
    std::cout << "\n";

    //bottom
    for (int x = 0; x < width; ++x) {
      std::string t = "";
      if (maze.at(getPos(x, y)).outDoors[2]) t += "   |   ";
      else t += "       ";
      std::cout << t;
    }
    std::cout << "\n";
  }
  std::cout << "----------------------------------------------" << std::endl;
}
void Maze::Generate() {
  srand(time(NULL));

  empty = esat::SpriteFromFile("../../../assets/Empty.png");


  int curr_x = start_x;
  int curr_y = start_y;

  bool bad_creation = false;
  bool created = false;

  while (!created) {
    placeRoom(curr_x, curr_y, -1);
    for (int i = 1; i < room_count; ++i) {
      if (queue.empty()) {
        bad_creation = true;
        break;//update
      }
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

    if (bad_creation) {
      for (int i = 0; i < maze.size(); ++i) {
        maze[i] = Room();
      }
    }
    else {
      created = true;
    }
  }

  print();
  //close maze
  for (auto& room : maze) {
    if (room.freePaths.any()) {
      room.outDoors &= ~room.freePaths;
      room.freePaths.reset();
      print();
    }
  }

  //set special rooms
  int left = special_rooms;
  for (auto& room : maze) {
    if (room.outDoors.count() == 1) {
      room.special = true;
      left--;
    }
    if (left <= 0) break;
  }
  print();

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



void Maze::setSprites() {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      auto& room = maze.at(getPos(x, y));
      int i = 0;
      std::bitset<4> mask;
      std::uint8_t mask_i;
      switch (room.outDoors.count()) {
        case 1:
          if (room.special)
            room.sprite = esat::SpriteFromFile(
                starting_rooms_[room_pool_.getRandomLevelOfType(
                    kSpecial)].sprite_.c_str());
          else
            room.sprite = esat::SpriteFromFile(
                starting_rooms_[room_pool_.getRandomLevelOfType(kDeadEnd)].
                sprite_.c_str());
          i = 0;
          while (!room.outDoors[i]) { i++; }
          room.rotations = i;
          break;
        case 2:
          mask = 5;
          if (room.outDoors == mask || room.outDoors == mask << 1) {
            room.sprite = esat::SpriteFromFile(
                starting_rooms_[room_pool_.getRandomLevelOfType(kCorridor)].
                sprite_.c_str());
            if (room.outDoors[0] != 1) room.rotations = 1;
          } else {
            room.sprite = esat::SpriteFromFile(
                starting_rooms_[room_pool_.getRandomLevelOfType(kTurn)].sprite_.
                c_str());
            mask_i = 3;
            mask = mask_i;
            i = 0;
            while (room.outDoors != mask && i < 3) {
              i++;
              mask = std::rotl(mask_i, i);
            }
            room.rotations = i;
          }
          break;
        case 3:
          room.sprite = esat::SpriteFromFile(
              starting_rooms_[room_pool_.getRandomLevelOfType(kSplit)].sprite_.
              c_str());
          mask = 7;
          room.rotations = 0;
          if (room.outDoors != mask) {
            room.rotations = 1;
            mask <<= 1;
            if (room.outDoors != mask) {
              room.rotations = 2;
              mask = 13;
              if (room.outDoors != mask) {
                room.rotations = 3;
              }
            }
          }

          break;
        case 4:
          room.sprite = esat::SpriteFromFile(
              starting_rooms_[room_pool_.getRandomLevelOfType(kCross)].sprite_.
              c_str());
          break;
        default:
          room.sprite = empty;
          break;
      }
    }
  }
}
void Maze::clear() {
  for (int i = 0; i < width * height; ++i) {
    maze.at(i) = Room();
  }
}
