#include "grid.hpp"
#include "esat/sprite.h"
#include "esat/draw.h"
#include "esat/window.h"
#include "esat/helpers.h"
#include "esat/time.h"

Maze maze(5, 5, 5);
char ** a;
int esat::main(int, char **) {
  WindowInit(500, 500);

  SpriteHandle empty = SpriteFromFile("../../../assets/Empty.png");
  SpriteHandle dead_end = SpriteFromFile("../../../assets/DeadEnd.png");
  SpriteHandle corridor = SpriteFromFile("../../../assets/Corridor.png");
  SpriteHandle turn = SpriteFromFile("../../../assets/Turn.png");
  SpriteHandle split = SpriteFromFile("../../../assets/Split.png");
  SpriteHandle cross = SpriteFromFile("../../../assets/Cross.png");
  maze.Generate();

  
  SpriteTransform t = SpriteTransform();
  SpriteTransformInit(&t);
  t.x = 64;
  t.y = 32;
  t.scale_x = 0.125f;
  t.scale_y = 0.125f;
  t.angle = 3.14f;
  while (WindowIsOpened()) {
    DrawBegin();
    DrawClear(0.0f, 0.0f, 0.0f);
    DrawSprite(dead_end, t);
    DrawEnd();
    WindowFrame();
  }

  return 0;
}
