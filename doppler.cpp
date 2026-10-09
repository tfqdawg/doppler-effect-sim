#include <raylib.h>
#include <algorithm>

using namespace std;

// constants.
constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;
constexpr int MAX_WAVES = 50;
constexpr float WAVE_SPEED = 50;
constexpr float OBJ_SPEED = 0.6f;
constexpr int WAVE_FREQ = 4;

int current_waves = 0;

// structs.
struct Obj{ float x, y; };
struct SoundWave{ float x, y, r; };
struct Obj obj;
struct SoundWave waves[MAX_WAVES];

// protos.
void draw_obj(void);
void wave_emission(void);
void draw_waves(void);
void wave_propagation(float dt);

int main(){
  InitWindow(WIDTH, HEIGHT, "Doppler Sim");
  
  obj = Obj{WIDTH/2, HEIGHT/2};

  SetTargetFPS(60);
  float interval = 0;
  wave_emission();
  while(!WindowShouldClose()){
    
    float dt = GetFrameTime();
    
    interval += dt;
    if(interval > 1.0f / WAVE_FREQ){
      wave_emission();
      interval = 0.0f;
    };
    wave_propagation(dt);
    
    if (IsKeyDown(KEY_RIGHT)) obj.x += OBJ_SPEED;
    if (IsKeyDown(KEY_LEFT)) obj.x -= OBJ_SPEED;
    if (IsKeyDown(KEY_UP)) obj.y -= OBJ_SPEED;
    if (IsKeyDown(KEY_DOWN)) obj.y += OBJ_SPEED;

    BeginDrawing();
    
    ClearBackground(BLACK);

    draw_obj();
    draw_waves();
    EndDrawing();
  }
  return 0;
}

void draw_obj(void){
    DrawCircle(obj.x, obj.y, 20, SKYBLUE);
}

void wave_emission(void){
  int count = min(current_waves + 1, MAX_WAVES);
  copy_backward(waves, waves + count - 1, waves + count);
  waves[0] = SoundWave{obj.x, obj.y, 0};
  current_waves = count;
}

void draw_waves(void){
  for(int i = 0; i < current_waves; i++){
    DrawCircleLines(waves[i].x, waves[i].y, waves[i].r, SKYBLUE);
  };
};

void wave_propagation(float dt){
  for(int i = 0; i < current_waves; i++){
    waves[i].r += WAVE_SPEED * dt;
  };
}
