#pragma once

#include <queue>
#include <random>
#include <vector>

#include "global.hpp"
#include "grid.hpp"

class RoomLayout;

class Generator {
public:
  Generator(int width, int height, int room_count, int seed = 0);
  
  bool findNextPosition();
  bool placeRoom();

  void findSpecialRoomCandidates();
  void closeMaze();

  bool ended() const{return room_count_ == curren_room_count_;}
  void clear();

  Grid grid_;
private:
  bool isPathValid(int direction, bool has_going_path);

  
  Vec2<int> start_position_;
  Vec2<int> current_position_;
  int last_dir_;
  int special_room_count_;
  int room_count_;
  int curren_room_count_;
  std::queue<Vec2<int>> room_queue_;
  std::vector<Vec2<int>> special_room_candidates_;

  unsigned seed_;
  std::default_random_engine random_engine_;
  std::uniform_int_distribution<int> random_bool_;
  std::uniform_int_distribution<int> random_x_;
  std::uniform_int_distribution<int> random_y_;
  
};

