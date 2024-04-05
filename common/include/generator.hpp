#pragma once

#include <queue>
#include <random>
#include <vector>
#include "room_layout.hpp"
#include "global.hpp"

class Generator {
public:
  Generator(int width, int height, int room_count, int seed = 0);
  
  bool findNextPosition();
  bool placeRoom();

  void findSpecialRoom();
  void closeMaze();

  bool ended() const{return room_count_ == curren_room_count_;}
  void clear();

  const RoomLayout& getRoom(const Vec2<int>& pos) const;
  const Vec2<int>& getGridSize() const {return grid_size_;}

  
  
  
  

private:
  bool posInGrid(const Vec2<int>& pos) const;
  RoomLayout& getRoom(const Vec2<int>& pos);
  bool isPathValid(int direction, bool has_going_path);

  std::vector<RoomLayout> maze_;
  
  Vec2<int> grid_size_;
  Vec2<int> start_position_;
  Vec2<int> current_position_;
  int last_dir_;
  int special_room_count_;
  int room_count_;
  int curren_room_count_;
  std::queue<Vec2<int>> room_queue_;
  //std::vector<Vec2<int>> special_room_candidates_;

  unsigned seed_;
  std::default_random_engine random_engine_;
  std::discrete_distribution<int> random_door_count_;
  std::uniform_int_distribution<int> random_rotation_;
  std::uniform_int_distribution<int> random_x_;
  std::uniform_int_distribution<int> random_y_;
  
};

