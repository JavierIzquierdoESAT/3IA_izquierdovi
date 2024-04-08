#pragma once

#include <array>
#include <unordered_map>
#include <vector>
#include <esat/sprite.h>

enum RoomType {
  kNone = -1,
  kSpecial = 0,
  kDeadEnd,
  kCorridor,
  kTurn,
  kSplit,
  kCross,
  kSize
};

struct Level {
  RoomType room_type_;
  std::string sprite_;
  Level():room_type_(kNone), sprite_(""){}
  Level(const RoomType rt, const std::string& sp):room_type_(rt), sprite_(sp) {}
};

inline const std::array starting_rooms_ = {
  Level(kSpecial,   "../../../assets/Start.png"),
  Level(kSpecial,   "../../../assets/Boss.png"),
  Level(kSpecial,   "../../../assets/Shop.png"),
  Level(kDeadEnd,   "../../../assets/AEnd.png"),
  Level(kDeadEnd,   "../../../assets/BEnd.png"),
  Level(kDeadEnd,   "../../../assets/CEnd.png"),
  Level(kCorridor,  "../../../assets/ACorridor.png"),
  Level(kCorridor,  "../../../assets/BCorridor.png"),
  Level(kCorridor,  "../../../assets/CCorridor.png"),
  Level(kTurn,      "../../../assets/ATurn.png"),
  Level(kTurn,      "../../../assets/BTurn.png"),
  Level(kTurn,      "../../../assets/CTurn.png"),
  Level(kSplit,     "../../../assets/ASplit.png"),
  Level(kSplit,     "../../../assets/BSplit.png"),
  Level(kSplit,     "../../../assets/CSplit.png"),
  Level(kCross,     "../../../assets/ACross.png"),
  Level(kCross,     "../../../assets/BCross.png"),
  Level(kCross,     "../../../assets/CCross.png"),
};


class LevelPool {
public:
  LevelPool();
  int getRandomLevelOfType(RoomType rt);
  std::unordered_map<std::string, esat::SpriteHandle> assets_;
private:
  std::vector<int> room_type_count_;

  
};
