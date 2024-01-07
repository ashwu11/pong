#include <stdio.h>
#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"

using namespace std;

int main()
{
    cout << "Starting the game!" << endl;

    const int WIDTH = 1200;
    const int HEIGHT = 800;
    const int GAP = 10;
    
    InitWindow(WIDTH, HEIGHT, "My Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();

        DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
        DrawCircle(WIDTH/2, HEIGHT/2, 20, WHITE);
        DrawRectangle(GAP, HEIGHT/2 - 60, 25, 120, WHITE);
        DrawRectangle(WIDTH - 25 - GAP, HEIGHT/2 - 60, 25, 120, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}