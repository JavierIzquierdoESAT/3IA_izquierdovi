#include <array>
#include <iostream>
#include <vector>
#include "MazeDigger.hpp"
#include "Replace.hpp"

MazeGenerator m(11, 11);
MazeRooms r;

Maze maze(10, 10, 5);

int main(int argc, char* argv[]) {
  // m.generate();
  // m.print();
  // r.draw(m);
  // r.print();

  maze.Generate();
  return 0;
}
