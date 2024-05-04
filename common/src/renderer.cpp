#include "renderer.hpp"

#include <bitset>

#include "generator.hpp"
#include "room_layout.hpp"

void Renderer::FetchRenderer(const Generator& generator) {
  auto grid_size = generator.getGridSize();
  size_ = grid_size;
  asset_grid_.clear();
  asset_grid_.reserve(grid_size.x_ * grid_size.y_);

  for (int y = 0; y < grid_size.y_; ++y) {
    for (int x = 0; x < grid_size.x_; ++x) {
      const RoomLayout& room_layout = generator.getRoom(Vec2<int>(x, y));
      int i = 0;
      std::bitset<4> mask;
      switch (room_layout.doors_.count()) {
        case 1:
          if (room_layout.special_ != 0) {
            switch (room_layout.special_) {
              case 1:
                asset_grid_.emplace_back(
                  starting_rooms_[room_pool_.getRandomLevelOfType(kStart)]
                );
                break;
              case 2:
                asset_grid_.emplace_back(
                  starting_rooms_[room_pool_.getRandomLevelOfType(kEnd)]
                );
                break;
              case 3:
                asset_grid_.emplace_back(
                  starting_rooms_[room_pool_.getRandomLevelOfType(kShop)]
                );
                break;
              default: break;
            }
          } else {
            asset_grid_.emplace_back(
              starting_rooms_[room_pool_.getRandomLevelOfType(kDeadEnd)]
            );
          }
          break;
        case 2:
          mask = 5;
          if (room_layout.doors_ == mask || room_layout.doors_ == mask << 1) {
            asset_grid_.emplace_back(
              starting_rooms_[room_pool_.getRandomLevelOfType(kCorridor)]
            );
          } else {
            asset_grid_.emplace_back(
              starting_rooms_[room_pool_.getRandomLevelOfType(kTurn)]
            );
          }
          break;
        case 3:
          asset_grid_.emplace_back(
            starting_rooms_[room_pool_.getRandomLevelOfType(kSplit)]
          );
          break;
        case 4:
          asset_grid_.emplace_back(
            starting_rooms_[room_pool_.getRandomLevelOfType(kCross)]
          );
          break;
        default:
          asset_grid_.emplace_back(Level());
          break;
      }
    }
  }
}

void Renderer::render(const Generator& generator) const {
  for (int y = 0; y < size_.y_; ++y) {
    for (int x = 0; x < size_.x_; ++x) {
      const RoomLayout& room = generator.getRoom(Vec2<int>(x, y));
      const Level& level = asset_grid_[x + y * size_.x_];
      esat::SpriteTransform t = esat::SpriteTransform();
      SpriteTransformInit(&t);
      t.x = static_cast<float>(x * 32);
      t.y = static_cast<float>(y * 32);
      t.scale_x = 0.125f;
      t.scale_y = 0.125f;

      if (room.getRotations() == 1) {
        t.angle = 3.14f / 2.0f;
        t.x += 32;
      } else if (room.getRotations() == 2) {
        t.angle = 3.14f;
        t.x += 32;
        t.y += 32;
      } else if (room.getRotations() == 3) {
        t.angle = -3.14f / 2.0f;
        t.y += 32;
      }

      if (level.sprite_ != "") {
        esat::SpriteHandle sh = room_pool_.assets_.at(level.sprite_);
        esat::DrawSprite(sh, t);
      }
    }
  }
}
