#include "room_layout.hpp"

void RotateLeft(std::bitset<4>& rot, int num) {
  for (int i = 0; i < num; ++i) {
    bool set_first = rot[3]?true:false;
    rot <<= 1;
    if(set_first) rot[0] = true;
  }
}
void RotateRight(std::bitset<4>& rot, int num) {
  for (int i = 0; i < num; ++i) {
    bool set_first = rot[0]?true:false;
    rot >>= 1;
    if(set_first) rot[3] = true;
  }
}

void RoomLayout::randomize(int in_direction,
                 std::default_random_engine& random_engine,
                 const std::uniform_int_distribution<int>& random_distribution) {
  doors_.reset();
  for (int i = 0; i < 4; ++i) {
    doors_[i] = random_distribution(random_engine);
  }
  free_doors_ = doors_;
  if (in_direction != -1) {
    doors_[in_direction] = true;
    free_doors_[in_direction] = true;
  }
}
void RoomLayout::reset() {
  doors_.reset();
  free_doors_.reset();
  special_ = false;
}