#pragma once

#include <array>
#include <chrono>

#include "room.hpp"
#include <queue>
#include <random>
#include <vector>
#include <esat/sprite.h>

#include "room_pool.hpp"

struct Vec2 {
  float x_, y_;
};

class RoomLayout{
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
  Vec2 position_;
};

class Maze {
public:
  Maze(int width, int height, int room_count, int seed = 0) :
  width_(width), height_(height), room_count(room_count){
    if(seed == 0) {
      seed_ = std::chrono::system_clock::now().time_since_epoch().count();
    }
    else {
      seed_ = seed;
    }
    random_engine_ =  std::default_random_engine(seed);
    num_doors_distribution_ = std::discrete_distribution ({1, 1, 1, 97});
    rotation_distribution_ = std::uniform_int_distribution (1,3);
  }

  int getPos(int x, int y) const;
  Room& getRoom(int x, int y);
  Room& getAdyacentRoom(int x, int y, int direction);

  bool isValid(int x, int y, int comming_dir, bool path_needed);
  


  void Generate();

  bool roomCanFit(Room& room, int room_x, int room_y);

  void placeRoom(int x, int y, int comming_dir);
  

  void clear();
  
  
  
  std::vector<RoomLayout> maze;

private:
  int width_, height_;
  int start_x, start_y;
  int special_rooms;
  int room_count;
  std::queue<RoomLayout*> queue;

  unsigned seed_;
  std::default_random_engine random_engine_;
  std::discrete_distribution num_doors_distribution_;
  std::uniform_int_distribution rotation_distribution_;
};
