#include <stdio.h>
#include <iostream>
#include "include/raylib.h"
#include "include/raymath.h"

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color OtherGreen = Color{195, 226, 194, 255};
Color Yellow = Color{243, 213, 91, 255};

int playerScore = 0;
int cpuScore = 0;
bool multiplayer = false;

class Ball { 
    public: 
    float x, y;
    int speedX, speedY;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update() {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }

        if (x + radius >= GetScreenWidth())  {
            cpuScore++;
            ResetBall();
        }

        if (x - radius <= 0) {
            playerScore++;
            ResetBall();
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (speedX != 0 || speedY != 0) {
                speedX = 0;
                speedY = 0;
            } else {
                speedX = 5;
                speedY = 5;
                ResetBall();
            }
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int choices[2] = {-1, 1};
        speedX *= choices[GetRandomValue(0, 1)];
        speedY *= choices[GetRandomValue(0, 1)];
    }

    void IncreaseSpeed() {
        speedX *= -1;
        speedX++;
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
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
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

    void Update(int ballY) {
        if (y + height/2 > ballY) {
            y -= speed;
        }

        if (y + height/2 <= ballY) {
            y += speed;
        }

        WallCollision();
    }
};

class Player: public Paddle {
    public:

    void Update() {
        if (IsKeyDown(KEY_A)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_Z)) {
            y += speed;
        }

        WallCollision();
    }
};

Ball ball;
Paddle player;
Player player2;
CpuPaddle cpu;

int main() {
    cout << "Starting the game!" << endl;

    const int WIDTH = 1100;
    const int HEIGHT = 700;

    InitWindow(WIDTH, HEIGHT, "The Pong Game");
    SetTargetFPS(60);

    // initialize ball
    ball.radius = 20;
    ball.x = WIDTH/2;
    ball.y = HEIGHT/2;
    ball.speedX = 5;
    ball.speedY = 5;

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
    cpu.speed = 7;

    player2.width = 25;
    player2.height = 120;
    player2.x = 10;
    player2.y = HEIGHT/2 - player2.height/2;
    player2.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Update elements
        ball.Update();
        player.Update();
        if (multiplayer) {
            player2.Update();
        } else {
            cpu.Update(ball.y);
        }
        
        // Check for collision
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.IncreaseSpeed();
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.IncreaseSpeed();
        }
        
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height})) {
            ball.IncreaseSpeed();
        }

        // Game modes
        if (IsKeyPressed(KEY_ONE)) multiplayer = false;
        if (IsKeyPressed(KEY_TWO)) multiplayer = true;
        if (IsKeyPressed(KEY_ZERO)) {
            playerScore = 0;
            cpuScore = 0;
            ball.ResetBall();
        }

        // Drawing
        ClearBackground(DarkGreen); // must clear every time we draw or it will leave trace
        DrawRectangle(WIDTH/2, 0, WIDTH/2, HEIGHT, Green);
        DrawCircle(WIDTH/2, HEIGHT/2, 150, LightGreen);
        DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
        ball.Draw();
        player.Draw();
        if (multiplayer) {
            player2.Draw();
        } else {
            cpu.Draw();
        }
        
        DrawText(TextFormat("%i", cpuScore), WIDTH/4 - 20, 20 , 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * WIDTH/4 - 20, 20 , 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}