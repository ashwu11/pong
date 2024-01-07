#include <stdio.h>
#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"

using namespace std;

int player_score = 0;
int cpu_score = 0;

class Ball { 
    public: 
    float x, y;
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
    protected:
    void WallCollision() {
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }

        if (y <= 0) {
            y = 0;
        }
    }

    public:
    float x, y; // top left corner of paddle
    float width, height;
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

        WallCollision();
    }
};

class CpuPaddle: public Paddle {
    public:

    void Update(int ball_y) {
        if (y + height/2 > ball_y) {
            y -= speed;
        }

        if (y + height/2 <= ball_y) {
            y += speed;
        }

        WallCollision();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

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

    // initialize paddles
    player.width = 25;
    player.height = 120;
    player.x = WIDTH - player.width - 10;
    player.y = HEIGHT/2 - player.height/2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = HEIGHT/2 - cpu.height/2;
    cpu.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Update elements
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check for collision
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(BLACK); // must clear every time we draw or it will leave trace
        DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
        ball.Draw();
        player.Draw();
        cpu.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}