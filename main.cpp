#include <stdio.h>
#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"

using namespace std;

class Ball { 
    public: 
    int x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }

        if (x + radius >= GetScreenWidth() || x - radius <= 0)  {
            speed_x *= -1;
        }
    }
};

class Paddle {
    public:
    int x, y; // top left corner of paddle
    int width, height;
    int speed;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }

        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }

        if (y <= 0) {
            y = 0;
        }
    }
};

Ball ball;
Paddle player;

int main() {
    cout << "Starting the game!" << endl;

    const int WIDTH = 1200;
    const int HEIGHT = 800;

    InitWindow(WIDTH, HEIGHT, "My Pong Game");
    SetTargetFPS(60);

    // initialize ball
    ball.radius = 20;
    ball.x = WIDTH/2;
    ball.y = HEIGHT/2;
    ball.speed_x = 5;
    ball.speed_y = 5;

    // initialize paddle
    player.width = 25;
    player.height = 120;
    player.x = WIDTH - player.width - 10;
    player.y = HEIGHT/2 - player.height/2;
    player.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ball.Update();
        player.Update();

        // Drawing
        ClearBackground(BLACK); // must clear every time we draw or it will leave trace
        DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
        ball.Draw();
        player.Draw();
        DrawRectangle(10, HEIGHT/2 - 60, 25, 120, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}