#include "grid.hpp"

Maze maze(5, 5, 10, 2);
int main(int argc, char* argv[]) {
  maze.Generate();
  return 0;
}
