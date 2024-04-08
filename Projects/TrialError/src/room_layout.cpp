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
                 const std::discrete_distribution<int>& random_distribution) {
  std::uniform_int_distribution rotation_distribution(1,3);
  int num_doors = random_distribution(random_engine);

  doors_.reset();
  for(int i=0; i<num_doors; i++) {
    int pos = 0;
    while (doors_[pos]) {pos++;}
    doors_[pos] = true;
    RotateLeft(doors_, rotation_distribution(random_engine));
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
int RoomLayout::getRotations() const {
  int rotations = 0;
  switch (doors_.count()) {
    case 1: {
      while (!doors_[rotations]) { rotations++; }
      break;
    }
    case 2: {
      std::bitset<4> mask = 5;
      unsigned mask_i = 3;
      if (doors_ == mask || doors_ == mask << 1) {
        if (doors_[0] != 1) rotations = 1;
      } else {
        mask_i = 3;
        mask = mask_i;
        while (doors_ != mask && rotations < 3) {
          rotations++;
          mask = std::rotl(mask_i, rotations);
        }
      }
      break;
    }
    case 3: {
      std::bitset<4> mask = 7;
      if (doors_ != mask) {
        rotations = 1;
        mask <<= 1;
        if (doors_ != mask) {
          rotations = 2;
          mask = 13;
          if (doors_ != mask) {
            rotations = 3;
          }
        }
      }
      break;
    }
    default: break;
  }
  return rotations;
}
