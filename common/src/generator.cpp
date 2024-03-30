#include "generator.hpp"

#include <chrono>
#include <queue>

#include "room_layout.hpp"

/**
 * \brief 
 * \param width 
 * \param height 
 * \param room_count 
 * \param seed 
 */
Generator::Generator(const int width, const int height,
                     const int room_count, const int seed)
  : grid_size_{width,height},
    last_dir_(-1),
    special_room_count_(0),
    room_count_(room_count),
    seed_(seed){
  if (seed == 0) {
    seed_ = std::chrono::system_clock::now().time_since_epoch().count();
  }
  for (int i = 0; i < width*height; ++i) {
    maze_.emplace_back(RoomLayout());
  }
  
  random_engine_ = std::default_random_engine(seed);
  random_door_count_ = std::discrete_distribution({1,1,1,97});
  random_rotation_ = std::uniform_int_distribution(1, 3);
  random_x_ = std::uniform_int_distribution(0, width - 1);
  random_y_ = std::uniform_int_distribution(0, height - 1);
}


bool Generator::findNextPosition() {
  if(current_position_ == start_position_) {
    start_position_.x_ = random_x_(random_engine_);
    start_position_.y_ = random_y_(random_engine_);
    current_position_ = start_position_;
  }
  else if(!room_queue_.empty()) {
    //get room with empty paths
    Vec2<int> base_pos = room_queue_.front();
    RoomLayout& last_room = getRoom(base_pos);
    while (last_room.free_doors_.none()) {
      room_queue_.pop();
      if (room_queue_.empty()) { return false; }
      base_pos = room_queue_.front();
      last_room = getRoom(base_pos);
    }
    //find avilable path
    int next_dir = 0;
    while (!last_room.free_doors_[next_dir]) {
      next_dir++;
    }
    current_position_ = getAdjacentPosition(base_pos, next_dir);
    last_dir_ = getOpositeDir(next_dir);
  }
  return true;
}
void Generator::clear() {
  for (auto& room_layout : maze_) {
    room_layout.reset();
  }
  start_position_.reset();
  current_position_.reset();
  last_dir_ = -1;
}

bool Generator::posInGrid(const Vec2<int>& pos) const {
  return !(pos.x_ < 0 || pos.x_ >= grid_size_.x_ ||
           pos.y_ < 0 || pos.y_ >= grid_size_.y_);
}

RoomLayout& Generator::getRoom(const Vec2<int>& pos) {
  return maze_.at(pos.x_ + pos.y_ * grid_size_.x_);
}

bool Generator::placeRoom() {
  RoomLayout& current = getRoom(current_position_);
  current.randomize(last_dir_, random_engine_, random_door_count_);

  bool res = true;
  //check for all adyacent positions to se if the random generated room fits the rooms already generated
  for (int i = 0; i < 4; i++) {
    if (!isPathValid(i, current.free_doors_[i])) {
      res = false;
      break;
    }
  }
  if (res) {
    //delete free doors of connected rooms
    for (int i = 0; i < 4; i++) {
      Vec2 go_to = getAdjacentPosition(current_position_, i);
      if(posInGrid(go_to)) {
        RoomLayout& checking_room = getRoom(go_to);
        if (checking_room.doors_[getOpositeDir(i)]) {
          current.free_doors_[i] = false;
          checking_room.free_doors_[getOpositeDir(i)] = false;
        }
      }
    }
    room_queue_.push(current_position_);
  }
  else current.reset();
  return res;
}
bool Generator::isPathValid(int direction, bool has_going_path) {
  Vec2 go_to = getAdjacentPosition(current_position_, direction);
  
  //rooom we want to go to is in bounds
  if (!posInGrid(go_to)) {
    if (has_going_path) return false;
    return true;
  }
  RoomLayout& checking_room = getRoom(go_to);

  //no room in the direction we are going
  if (checking_room.doors_.none()) {
    return true;
  }
  //next room has path towards current room
  bool has_comming_path = checking_room.free_doors_[getOpositeDir(direction)];
  return has_going_path && has_comming_path ||
         !has_going_path && !has_comming_path;
}
