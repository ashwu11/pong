#include <stdio.h>
#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"

using namespace std;

int main()
{
    cout << "Starting the game!" << endl;

    const int WIDTH = 1280;
    const int HEIGHT = 800;
    InitWindow(WIDTH, HEIGHT, "My Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}