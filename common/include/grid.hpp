#pragma once

#include <array>

#include "room.hpp"
#include <queue>
#include <vector>
#include <esat/sprite.h>

#include "room_pool.hpp"

class Maze {
public:
  Maze(int w, int h, int total, int special_rooms);

  int getPos(int x, int y) const;
  Room& getRoom(int x, int y);
  Room& getAdyacentRoom(int x, int y, int direction);

  bool isValid(int x, int y, int comming_dir, bool path_needed);


  void print() const;


  void Generate();

  bool roomCanFit(Room& room, int room_x, int room_y);

  void placeRoom(int x, int y, int comming_dir);

  void setSprites();

  void clear();

  //crap
  esat::SpriteHandle empty;
  
  int width, height;
  std::vector<Room> maze;

private:
  int start_x, start_y;
  int special_rooms;
  int room_count;
  std::queue<Room*> queue;
  

  //crap
  LevelPool room_pool_;

};
