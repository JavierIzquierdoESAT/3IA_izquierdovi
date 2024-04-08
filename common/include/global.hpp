#pragma once

template<typename T>
struct Vec2 {
  T x_ = 0;
  T y_ = 0;

  void reset() {x_ = 0; y_= 0;}
  
  bool operator==(const Vec2& o) const {
    return x_ == o.x_ && y_ == o.y_;
  }
};

inline Vec2<int> getAdjacentPosition(const Vec2<int>& pos, int direction) {
  Vec2<int> res = pos;
  switch (direction) {
    case 0:
      res.y_--;
    break;
    case 1:
      res.x_++;
    break;
    case 2:
      res.y_++;
    break;
    case 3:
      res.x_--;
    break;
    default:break;
  }
  return res;
}

inline int DistanceBetweenPoints(Vec2<int> a, Vec2<int> b) {
  int x = (b.x_ - a.x_) * (b.x_ - a.x_);
  int y = (b.y_ - a.y_) * (b.y_ - a.y_);
  return x + y;
}


inline int getOpositeDir(const int dir) {
  int res = -1;
  switch (dir) {
    case 0:
      res = 2;
    break;
    case 1:
      res = 3;
    break;
    case 2:
      res = 0;
    break;
    case 3:
      res = 1;
    break;
    default:
      break;
  }
  return res;
}