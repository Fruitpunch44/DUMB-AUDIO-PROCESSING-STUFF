#include"raylib.h"
#include"style.h"

int main()
{
    const int screenWidth = 800;
    Music music = LoadMusicStream("resources/audio.wav");
    const int screenHeight = 450;
  
    InitWindow(screenWidth, screenHeight, "raylib wip - audio visualizer");
    SetTargetFPS(60);
  
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to raylib!", 200, 200, 40, DARKGRAY);
        EndDrawing();
    }
  
    CloseWindow();
    return 0;
}