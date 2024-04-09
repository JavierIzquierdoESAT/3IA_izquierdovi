#include "generator.hpp"

#include <chrono>

Generator::Generator(int width, int height, int room_count, int seed)
  : grid_(width, height),
    last_dir_(-1),
    special_room_count_(0),
    room_count_(room_count),
    curren_room_count_(0),
    seed_(seed) {
  if (seed == 0) {
    seed_ = std::chrono::system_clock::now().time_since_epoch().count();
  }
  random_engine_ = std::default_random_engine(seed_);
  random_bool_ = std::uniform_int_distribution(0, 1);
  random_x_ = std::uniform_int_distribution(0, width - 1);
  random_y_ = std::uniform_int_distribution(0, height - 1);
}

bool Generator::findNextPosition() {
  if (current_position_ == start_position_ && room_queue_.empty()) {
    start_position_.x_ = random_x_(random_engine_);
    start_position_.y_ = random_y_(random_engine_);
    current_position_ = start_position_;
  } else if (!room_queue_.empty()) {
    //get room with empty paths
    Vec2<int> base_pos = room_queue_.front();
    RoomLayout* last_room = &grid_.getRoom(base_pos);
    while (last_room->free_doors_.none()) {
      room_queue_.pop();
      if (room_queue_.empty()) { return false; }
      base_pos = room_queue_.front();
      last_room = &grid_.getRoom(base_pos);
    }
    //find avilable path
    int next_dir = 0;
    while (!last_room->free_doors_[next_dir]) {
      next_dir++;
    }
    current_position_ = getAdjacentPosition(base_pos, next_dir);
    last_dir_ = getOpositeDir(next_dir);
  } else {
    return false;
  }
  if (ended()) return false;
  return true;
}

bool Generator::placeRoom() {
  RoomLayout& current = grid_.getRoom(current_position_);
  current.randomize(last_dir_, random_engine_, random_bool_);

  bool res = true;
  //check for all adyacent positions to se if the random generated room fits the rooms already generated
  for (int i = 0; i < 4; i++) {
    Vec2 go_to = getAdjacentPosition(current_position_, i);
    if (!grid_.posInGrid(go_to)) {
      res = false;
      break;
    }
    //delete free doors of connected rooms
    RoomLayout& checking_room = grid_.getRoom(go_to);
    if(checking_room.valid()) {
      current.doors_[i] = true;
      current.free_doors_[i] = false;
      checking_room.doors_[getOpositeDir(i)] = true;
      checking_room.free_doors_[getOpositeDir(i)] = false;
    }
    curren_room_count_++;
    room_queue_.push(current_position_);
  }
  if (!res) current.reset();
  return res;
}

void Generator::clear() {
  grid_.reset();
  special_room_candidates_.clear();
  start_position_.reset();
  current_position_.reset();
  last_dir_ = -1;
  curren_room_count_ = 0;
}
