#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600

// structs

// protos
// void draw_obj();
// void wave_emission();
// void draw_waves();
// void wave_propagation(float dt);

int main(void){

  InitWindow(WIDTH, HEIGHT, "Doppler Sim");
  while (!WindowShouldClose()){
    BeginDrawing();
    EndDrawing();
  }

  return 0;
}
