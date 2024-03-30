#include "room_layout.hpp"
#include "room.hpp"

// void RotateLeft(std::bitset<4>& rot, int num) {
//   for (int i = 0; i < num; ++i) {
//     bool set_first = rot[3]?true:false;
//     rot <<= 1;
//     if(set_first) rot[0] = true;
//   }
// }
// void RotateRight(std::bitset<4>& rot, int num) {
//   for (int i = 0; i < num; ++i) {
//     bool set_first = rot[0]?true:false;
//     rot >>= 1;
//     if(set_first) rot[3] = true;
//   }
// }

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
  rotations_ = 0;
  doors_.reset();
  free_doors_.reset();
  special_ = false;
}
