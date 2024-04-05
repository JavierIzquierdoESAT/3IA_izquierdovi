#include <esat/draw.h>

#include "generator.hpp"
#include "renderer.hpp"
#include "esat/window.h"
#include "esat/input.h"
#include "esat/time.h"

Generator generator(10, 10, 15, 1);

int esat::main(int, char **) {
  WindowInit(500, 500);
  
  Renderer renderer;
  while (WindowIsOpened()) {
    if(generator.findNextPosition()) {
      generator.placeRoom();
      renderer.FetchRenderer(generator);
    }
    else if(!generator.ended()) {
      generator.clear();
    }
    else {
      generator.closeMaze();
      renderer.FetchRenderer(generator);
    }
    if(IsSpecialKeyPressed(kSpecialKey_Space)) {
      generator.clear();
      renderer.FetchRenderer(generator);
    }

    
    DrawBegin();
    DrawClear(0.0f, 0.0f, 0.0f);
    renderer.render(generator);
    DrawEnd();
    WindowFrame();
    
    Sleep(200);
  }
  return 0;
}
