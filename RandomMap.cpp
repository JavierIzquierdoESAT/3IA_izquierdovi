#include <array>
#include <iostream>
#include <vector>
#include "MazeDigger.hpp"

MazeGenerator m(11, 11);
MazeRooms r;
int main(int argc, char* argv[]) {
  m.generate();
  m.print();
  r.draw(m);
  r.print();
  return 0;
}
