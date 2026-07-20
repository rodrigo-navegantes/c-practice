#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include "raylib.h"

int main()
{
	const float screenWidth = 800;
	const float screenHeight = 450;
    const float fruitPadding = 80;

    int   direction = 0;
    int   score = 0;
    bool  gameOver = false; 
    float speed = 3.0f;

    srand(time(NULL));
    
	InitWindow(screenWidth, screenHeight, "Snake");
    
	Vector2 square_size = { 20.0f, 20.0f };
	Vector2 fruit_size = { 20.0f, 20.0f };
    Vector2 head_position = { screenWidth/2.0f, screenHeight/2.0f};
    Vector2 fruit_position = { fruitPadding + rand() % (int)(screenWidth - 2 * fruitPadding), fruitPadding + rand() % (int)(screenHeight - 2 * fruitPadding)};
    
    SetTargetFPS(60);
    
	while(!WindowShouldClose() && !gameOver)
	{
        
	// Key Detection
	if (IsKeyDown(KEY_RIGHT)) direction = 1;
    if (IsKeyDown(KEY_UP))    direction = 2;
    if (IsKeyDown(KEY_LEFT))  direction = 3;
    if (IsKeyDown(KEY_DOWN))  direction = 4;

	// Check if snake went out of bounds
	if (head_position.x < 0 || head_position.x > screenWidth || head_position.y < 0 || head_position.y > screenHeight) gameOver = true;  

    // Snake movement
    if (direction == 1) head_position.x += speed;
    if (direction == 2) head_position.y -= speed;
    if (direction == 3) head_position.x -= speed;
    if (direction == 4) head_position.y += speed;
    
    for (int size = 1; size <= (score + 1); size++)
    {
        
    }
    // Detect if snake ate fruit
    if (   head_position.x  - fruit_position.x > -20 && head_position.x -  fruit_position.x < 20  
        && fruit_position.y - head_position.y  > -20 && fruit_position.y - head_position.y  < 20)
    {
        score++;
        fruit_position.x = fruitPadding + rand() % (int)(screenWidth -  2 * fruitPadding);
        fruit_position.y = fruitPadding + rand() % (int)(screenHeight - 2 * fruitPadding);
    }


	DrawText(TextFormat("SCORE: %d", score), screenWidth/2.0f - 80, 30, 40, BLACK);
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawRectangleV(head_position,  square_size, BLACK);
	DrawRectangleV(fruit_position, fruit_size,  RED);
	EndDrawing();

	}

	CloseWindow();

	return 0; 
}
