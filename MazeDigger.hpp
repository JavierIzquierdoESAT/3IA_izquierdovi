enum class rooms {
  none,
  plaza,
  tJunction,
  corridor,
  turn,
  deadEnd
};

// Straight
std::array<int, 9> HorizontalStraightPattern = {5,1,5,
                                                0,0,0,
                                                5,1,5};

std::array<int, 9> VerticalStraightPattern = {5,0,5,
                                              1,0,1,
                                              5,0,5};

// T Junctions	
std::array<int, 9> TJunctionUpPattern = {1,0,1,
                                         0,0,0,
                                         5,1,5};

std::array<int, 9> TJunctionDownPattern = {5,1,5,
                                           0,0,0,
                                           1,0,1};

std::array<int, 9> TJunctionLeftPattern = {1,0,5,
                                           0,0,1,
                                           1,0,5};

std::array<int, 9> TJunctionRightPattern = {5,0,1,
                                            1,0,0,
                                            5,0,1};

// Crossroad
std::array<int, 9> CrossroadPattern = {1,0,1,
                                       0,0,0,
                                       1,0,1};

// Turns
std::array<int, 9> TurnLeftUpPattern = {1,0,5,
                                        0,0,1,
                                        5,1,5};

std::array<int, 9> TurnLeftDownPattern = {5,1,5,
                                          0,0,1,
                                          1,0,5};

std::array<int, 9> TurnRightUpPattern = {5,0,1,
                                         1,0,0,
                                         5,1,5};

std::array<int, 9> TurnRightDownPattern = {5,1,5,
                                           1,0,0,
                                           5,0,1};

// Dead ends
std::array<int, 9> DeadEndUpPattern = {5,0,5,
                                       1,0,1,
                                       5,1,5};

std::array<int, 9> DeadEndDownPattern = {5,1,5,
                                         1,0,1,
                                         5,0,5};

std::array<int, 9> DeadEndLeftPattern = {5,1,5,
                                         0,0,1,
                                         5,1,5};

std::array<int, 9> DeadEndRightPattern = {5,1,5,
                                          1,0,0,
                                          5,1,5};



class MazeGenerator {

public:
  MazeGenerator(const int w, const int h) : w_(w), h_(h), dirs_{0,1,2,3},
                                            start_x_(0 + rand() % w),
                                            start_y_(0 + rand() % h) {
    for (int i = 0; i < w * h; ++i) {
      maze_.emplace_back(1);
    }
    start_x_ = 1;
    start_y_ = 1;
  }

  int get(const int x, const int y) const{
    return maze_[x + y * w_];
  }

  void set(const int x, const int y, const int value) {
    maze_[x + y * w_] = value;
  }

  void print() const{
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        std::cout << " " << maze_[x + y * w_] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "----------------------------------------------" << std::endl;
  }
  void ShuffleDirs() {
    for (int i = 3; i != 0; i--) {
      int j = rand() % i;
      //swap
      int aux = dirs_[j];
      dirs_[j] = dirs_[i];
      dirs_[i] = aux;
    }
  }
  void generate() {
    step(start_x_, start_y_);
  }
  void step(const int x, const int y) {
    print();
    ShuffleDirs();
    for (auto dir : dirs_) {
      switch (dir) {
        case 0: // Up
          if (x + 2 >= w_ - 1 || get(x + 2, y) == 0)
            continue;

          set(x + 2, y, 0);
          set(x + 1, y, 0);
          step(x + 2, y);
          break;

        case 1: // Right
          if (y + 2 >= h_ - 1 || get(x, y + 2) == 0)
            continue;

          set(x, y + 2, 0);
          set(x, y + 1, 0);
          step(x, y + 2);
          break;

        case 2: // Down
          if (x - 2 <= 0 || get(x - 2, y) == 0)
            continue;

          set(x - 2, y, 0);
          set(x - 1, y, 0);
          step(x - 2, y);
          break;

        case 3: // Left
          if (y - 2 <= 0 || get(x, y - 2) == 0)
            continue;

          set(x, y - 2, 0);
          set(x, y - 1, 0);
          step(x, y - 2);
          break;
        default:
          break;
      }
    }
  }


  int w_, h_;
  int start_x_, start_y_;
  std::vector<int> maze_;
  std::array<int, 4> dirs_;
};

class MazeRooms {
public:
  MazeRooms(){}
  
  bool IsPatternMatching(const MazeGenerator& paths, const int path_x, const int path_y,
                         const std::array<int, 9>& pattern) const{
    int Count = 0;
    int i = 0;
    for (int y = 1; y > -2; y--)
    {
      for (int x = -1; x < 2; x++)
      {
        if (pattern[i] == paths.get(path_x + x, path_y + y) || pattern[i] == 5)
        {
          Count++;
        }

        i++;
      }
    }

    return Count == 9;
  }
  void PlacePiece(const int x, const int y, const float rotation,const rooms r) {
    int x_pos = (x - 1) / 2;
    int y_pos = (y - 1) / 2;
    maze_[x_pos + y_pos * width] = r;
  }

  void draw(const MazeGenerator& paths) {
    heitght = (paths.h_ - 1) / 2;
    width = (paths.w_ - 1) / 2;
    for (int i = 0; i < width * heitght; ++i) {
      maze_.emplace_back(rooms::none);
    }
    
    for (int x = 1; x < paths.w_ - 1; x+=2) {
      for (int y = 1; y < paths.h_ - 1; y+=2) {
        // Straight
        if (IsPatternMatching(paths, x, y, HorizontalStraightPattern)) {
          PlacePiece(x, y, 90.f, rooms::corridor);
        } else if (IsPatternMatching(paths, x, y, VerticalStraightPattern)) {
          PlacePiece(x, y, 0.f, rooms::corridor);
        }

        // Turns
        else if (
          IsPatternMatching(paths, x, y, TurnLeftUpPattern)) {
          PlacePiece(x, y, 0.f, rooms::turn);
        } else if (
          IsPatternMatching(paths, x, y, TurnLeftDownPattern)) {
          PlacePiece(x, y, 90.f, rooms::turn);
        } else if (IsPatternMatching(paths, x, y, TurnRightUpPattern)) {
          PlacePiece(x, y, -90.f, rooms::turn);
        } else if (IsPatternMatching(paths, x, y, TurnRightDownPattern)) {
          PlacePiece(x, y, 180.f, rooms::turn);
        }

        // T Junctions	
        else if (
          IsPatternMatching(paths, x, y, TJunctionUpPattern)) {
          PlacePiece(x, y, -90.f, rooms::tJunction);
        } else if (
          IsPatternMatching(paths, x, y, TJunctionDownPattern)) {
          PlacePiece(x, y, 90.f, rooms::tJunction);
        } else if (IsPatternMatching(paths, x, y, TJunctionLeftPattern)) {
          PlacePiece(x, y, 0.f, rooms::tJunction);
        } else if (IsPatternMatching(paths, x, y, TJunctionRightPattern)) {
          PlacePiece(x, y, 180.f, rooms::tJunction);
        }

        // Dead ends
        else if (
          IsPatternMatching(paths, x, y, DeadEndUpPattern)) {
          PlacePiece(x, y, 90.f, rooms::deadEnd);
        } else if (
          IsPatternMatching(paths, x, y, DeadEndDownPattern)) {
          PlacePiece(x, y, -90.f, rooms::deadEnd);
        } else if (IsPatternMatching(paths, x, y, DeadEndLeftPattern)) {
          PlacePiece(x, y, 180.f, rooms::deadEnd);
        } else if (IsPatternMatching(paths, x, y, DeadEndRightPattern)) {
          PlacePiece(x, y, 0.f, rooms::deadEnd);
        }

        // Crossroad
        else if (IsPatternMatching(paths, x, y, CrossroadPattern)) {
          PlacePiece(x, y, 0.f, rooms::plaza);
        }
      }
    }
  }

  void print() {
    for (int y = 0; y < heitght; ++y) {
      for (int x = 0; x < width; ++x) {
        char str = 0;
        switch (maze_[x + y * width]) {
          case rooms::none:
            str = ' ';
            break;
          case rooms::plaza:
            str = '+';
            break;
          case rooms::tJunction:
            str = 'T';
            break;
          case rooms::corridor:
            str = '-';
            break;
          case rooms::turn:
            str = 'L';
            break;
          case rooms::deadEnd:
            str = '\'';
            break;
        }
        std::cout << " " << char(str) << " ";
      }
      std::cout << "\n";
    }
    std::cout << "----------------------------------------------" << std::endl;
  }
private:
  int width;
  int heitght;
  std::vector<rooms> maze_;
};