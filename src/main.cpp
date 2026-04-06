#include <raylib.h>
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920
#define TARGET_FPS 120


int main() 
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(TARGET_FPS);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }
    
    CloseWindow();
}