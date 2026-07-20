#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "raylib.h"

const float   screenWidth   = 800;
const float   screenHeight  = 450;
const float   fruitPadding  = 80;
const Vector2 square_size   = { 20.0f, 20.0f };
const Vector2 fruit_size    = { 20.0f, 20.0f };

void draw(Vector2 fruit_position, int score, Vector2 snake[])
{
    usleep(150000);
    DrawText(TextFormat("SCORE: %d", score), screenWidth/2.0f - 80, 30, 40, BLACK);
	BeginDrawing();
	ClearBackground(RAYWHITE);
    for (int i = 0; i <= score; i++) DrawRectangleV(snake[i],  square_size, BLACK);
    DrawRectangleV(fruit_position, fruit_size,  RED);
	EndDrawing();
}

bool hit_detection(Vector2 a, Vector2 b) {return (a.x  - b.x > -20 && a.x -  b.x < 20 && b.y - a.y  > -20 && b.y - a.y  < 20); }

int main()
{
    int   direction = 0;
    int   score = 0;
    bool  gameOver = false; 
    float speed = 20.0f;

    srand(time(NULL));
    
	InitWindow(screenWidth, screenHeight, "Snake");
    
    Vector2 snake[100];
    Vector2 head_position =  { screenWidth/2.0f, screenHeight/2.0f};
    Vector2 fruit_position = { fruitPadding + rand() % (int)(screenWidth - 2 * fruitPadding), fruitPadding + rand() % (int)(screenHeight - 2 * fruitPadding)};
    
    SetTargetFPS(60);
    
	while(!WindowShouldClose() && !gameOver)
	{
     
	if (IsKeyDown(KEY_RIGHT)) direction = 1;
    if (IsKeyDown(KEY_UP))    direction = 2;
    if (IsKeyDown(KEY_LEFT))  direction = 3;
    if (IsKeyDown(KEY_DOWN))  direction = 4;

	if (head_position.x < 0 || head_position.x > screenWidth || head_position.y < 0 || head_position.y > screenHeight) gameOver = true;  

    if (direction == 1) head_position.x += speed;
    if (direction == 2) head_position.y -= speed;
    if (direction == 3) head_position.x -= speed;
    if (direction == 4) head_position.y += speed;

    if (hit_detection(head_position, fruit_position))
    {
        score++;
        fruit_position.x = fruitPadding + rand() % (int)(screenWidth -  2 * fruitPadding);
        fruit_position.y = fruitPadding + rand() % (int)(screenHeight - 2 * fruitPadding);
    }

    for (int i = score; i > 0; i--)
    { 
        for (int j = 0; j < i; j++) if (hit_detection(snake[j], snake[i])) gameOver = true;
        snake[i] = snake[i-1];
    }
        
    snake[0].x = head_position.x;
    snake[0].y = head_position.y;
    
    draw(fruit_position, score, snake);

    }

    CloseWindow();
    printf("Game Over!");

	return 0; 
}