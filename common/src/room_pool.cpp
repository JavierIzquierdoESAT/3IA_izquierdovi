#include "room_pool.hpp"

#include <chrono>
#include "esat/sprite.h"
#include <random>

LevelPool::LevelPool() {
  room_type_count_.assign(kSize, 0);
  for (auto starting_room : starting_rooms_) {
    room_type_count_[starting_room.room_type_]++;
    assets_.emplace(starting_room.sprite_, esat::SpriteFromFile(starting_room.sprite_.c_str()));
  }
}
int LevelPool::getRandomLevelOfType(RoomType rt) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine random_engine (seed);
  std::uniform_int_distribution distribution(0, room_type_count_[rt]-1);
  int skipCount = distribution(random_engine);

  for (int i = 0; i < starting_rooms_.size(); ++i) {
    if(starting_rooms_[i].room_type_ == rt) {
      if(skipCount == 0) return i;
      skipCount--;
    }
  }

  return -1;
}

