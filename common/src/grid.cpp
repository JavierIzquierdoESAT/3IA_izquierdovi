#include "grid.hpp"

Grid::Grid(const int width, const int height)
  : grid_size_{width,height} {
  for (int i = 0; i < width * height; ++i) {
    grid_.emplace_back(RoomLayout());
  }
}

const RoomLayout& Grid::getRoom(const Vec2<int>& pos) const {
  return grid_.at(pos.x_ + pos.y_ * grid_size_.x_);
}

RoomLayout& Grid::getRoom(const Vec2<int>& pos) {
  return grid_.at(pos.x_ + pos.y_ * grid_size_.x_);
}

void Grid::reset() {
  for (auto& room_layout : grid_) {
    room_layout.reset();
  }
}

bool Grid::posInGrid(const Vec2<int>& pos) const {
  return !(pos.x_ < 0 || pos.x_ >= grid_size_.x_ ||
           pos.y_ < 0 || pos.y_ >= grid_size_.y_);
}
