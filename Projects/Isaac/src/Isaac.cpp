#include <esat/draw.h>
#include "esat/window.h"
#include "esat/input.h"
#include "esat/time.h"


int esat::main(int, char **) {
  WindowInit(500, 500);
  
  while (WindowIsOpened()) {

    
    DrawBegin();
    DrawClear(0.0f, 0.0f, 0.0f);
    DrawEnd();
    WindowFrame();
    
    Sleep(0);
  }
  return 0;
}
