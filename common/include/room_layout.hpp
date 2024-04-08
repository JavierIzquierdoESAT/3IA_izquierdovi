#pragma once

#include <bitset>
#include <random>


class RoomLayout {
public:
  RoomLayout() = default;
  void randomize(int in_direction,
                 std::default_random_engine& random_engine,
                 const std::discrete_distribution<int>& random_distribution);
  void reset();
  bool valid() const {return doors_.any();}
  int getRotations() const;
  
  std::bitset<4> doors_;
  std::bitset<4> free_doors_;
  bool special_ = false;
};
