#pragma once
#include <vector>

#include "global.hpp"
#include "room_pool.hpp"

class Generator;

class Renderer{
public:
  Renderer() = default;

  void FetchRenderer(Generator& generator);
  void render(Generator& grid) const;

private:
  std::vector<Level> asset_grid_;
  Vec2<int> size_;
  LevelPool room_pool_;
};