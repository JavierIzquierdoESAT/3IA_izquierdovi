#include <esat/draw.h>

#include "generator.hpp"
#include "renderer.hpp"
#include "esat/window.h"
#include "esat/input.h"
#include "esat/time.h"

Generator generator(12, 12, 30);

int esat::main(int, char **) {
  WindowInit(500, 500);
  
  Renderer renderer;
  bool running = true;
  while (WindowIsOpened()) {
    if(running) {
      if(generator.findNextPosition()) {
        generator.placeRoom();
        renderer.FetchRenderer(generator);
      }
      else if(!generator.ended()) {
        generator.clear();
      }
      else {
        generator.closeMaze();
        generator.findSpecialRoomCandidates();
        renderer.FetchRenderer(generator);
        running = false;
      }
    }
    if(IsSpecialKeyPressed(kSpecialKey_Space)) {
      generator.clear();
      renderer.FetchRenderer(generator);
      running = true;
    }

    
    DrawBegin();
    DrawClear(0.0f, 0.0f, 0.0f);
    renderer.render(generator);
    DrawEnd();
    WindowFrame();
    
    Sleep(0);
  }
  return 0;
}
