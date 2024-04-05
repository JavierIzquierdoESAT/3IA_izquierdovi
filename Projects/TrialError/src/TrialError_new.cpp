#include <esat/draw.h>

#include "generator.hpp"
#include "room_layout.hpp"
#include "esat/window.h"
#include "esat/input.h"
#include "esat/time.h"


Generator generator(10, 10, 30, 2);
int esat::main(int, char **) {
  WindowInit(500, 500);

  //get random pos
  //get random room layout


  while (WindowIsOpened()) {
    if(generator.findNextPosition()) {
      generator.placeRoom();
    }
    if(IsSpecialKeyPressed(kSpecialKey_Space)) {
        generator.clear();
    }

    
    
    DrawBegin();
    DrawClear(0.0f, 0.0f, 0.0f);
    DrawEnd();
    WindowFrame();
    
    Sleep(500);
  }


  
  // SpriteTransform t = SpriteTransform();
  // SpriteTransformInit(&t);
  // t.x = 64;
  // t.y = 32;
  // t.scale_x = 0.125f;
  // t.scale_y = 0.125f;
  // t.angle = 3.14f;
  // while (WindowIsOpened()) {
  //
  //   if(IsSpecialKeyDown(kSpecialKey_Space)) {
  //     maze.clear();
  //     maze.Generate();
  //     maze.setSprites();
  //   }
  //   
  //   DrawBegin();
  //   DrawClear(0.0f, 0.0f, 0.0f);
  //   render(maze);
  //   DrawEnd();
  //   WindowFrame();
  //}

  return 0;
}
