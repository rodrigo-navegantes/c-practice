//  gcc main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./main
#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    const float L = 100.0f; 
    const float gravity = -9.81f * 10.0f;
    const float theta_initial = (45.0f) * (3.1415f) / (180.0f);

    float time = 0.0f; 
    Vector2 ball;

    InitWindow(screenWidth, screenHeight, "Simple Pendulum Physics");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    { 
        time  += GetFrameTime();
        float theta = theta_initial * cos(time * sqrt(-gravity/L));

        ball.x = sin(theta) * L + (screenWidth/2.0f);
        ball.y = -(1-cos(theta))* L + (screenHeight/4.0f) + 100;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawLine(ball.x, ball.y, (float)screenWidth/2.0f, ((float)screenHeight/4.0f), BLACK);
            DrawText(TextFormat("Gravidade: %.1f g", (-gravity)/(9.81f)), 10, 30, 20, DARKGRAY);
            DrawText(TextFormat("Comprimento: %.1f m", L), 10, 60, 20, DARKGRAY);

            DrawCircleV(ball, 10.0f, RED);
        EndDrawing();
    }

    CloseWindow();       
    return 0;
}
