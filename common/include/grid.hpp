#pragma once
#include <vector>

#include "global.hpp"
#include "room_layout.hpp"

class RoomLayout;

enum class TileState {
  kNone,
  kOccupied
};

class Grid {
public:
  Grid(int width, int height);
  
  const RoomLayout& getRoom(const Vec2<int>& pos) const;
  RoomLayout& getRoom(const Vec2<int>& pos);
  
  const Vec2<int>& getGridSize() const {return grid_size_;}
  bool posInGrid(const Vec2<int>& pos) const;

  void reset();

private:
  
  Vec2<int> grid_size_;
  std::vector<RoomLayout> grid_;
};
