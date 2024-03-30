#pragma once

#include <bitset>
#include <random>

#include "global.hpp"

class RoomLayout {
public:
  RoomLayout() = default;
  void randomize(int in_direction,
                 std::default_random_engine& random_engine,
                 const std::discrete_distribution<int>& random_distribution);
  void reset();
  bool valid() const {return doors_.any();}
  
  int rotations_ = 0;
  std::bitset<4> doors_;
  std::bitset<4> free_doors_;
  bool special_ = false;
};
