#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

int main()
{
	const float screenWidth = 800;
	const float screenHeight = 450;
	const float playerPadding = 80;

	float x_speed = 3.0f;
	float y_speed = 3.0f;
	int score[2] = {0, 0};

	InitWindow(screenWidth, screenHeight, "Pong");

	Vector2 player_size = { 20.0f, 60.0f };

	Vector2 player1 = { playerPadding,  screenHeight/2  };
	Vector2 player2 = { screenWidth - playerPadding - player_size.x, screenHeight/2  };
	Vector2 ball = { screenWidth/2, screenHeight/2 };

	SetTargetFPS(60);

	while(!WindowShouldClose())
	{

	// Key Detection
	if (IsKeyDown(KEY_S)) player1.y += 4.0f;
        if (IsKeyDown(KEY_W)) player1.y -= 4.0f;
        if (IsKeyDown(KEY_UP)) player2.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN)) player2.y += 4.0f;

	// Prevent player from going out of bounds
	if (player1.y > screenHeight - player_size.y) player1.y = screenHeight - player_size.y;  
	if (player2.y > screenHeight - player_size.y) player2.y = screenHeight - player_size.y;  
	if (player1.y < 0) player1.y = 0;  
	if (player2.y < 0) player2.y = 0;  
	
	// Moves ball
	ball.x += x_speed;
	ball.y += y_speed;
		
	// Wall Detection
	if (ball.x > screenWidth)
	{
		x_speed *= -1;
		score[0] += 1;
	}
	if (ball.x < 0) 
	{	
		x_speed *= -1;
		score[1] += 1;
	}
	if (ball.y > screenHeight || ball.y < 0) y_speed *= -1;

	//Player detection
	if (abs(ball.x - player1.x - player_size.x) <= 3 && ball.y >= player1.y && ball.y <= player1.y + 80) x_speed *= -1;
	if (abs(ball.x - player2.x) <= 3 && ball.y >= player2.y && ball.y <= player2.y + 80) x_speed *= -1;

	DrawText(TextFormat("%d", score[0]), 150, 30, 80, BLACK);
        DrawText(TextFormat("%d", score[1]), screenWidth - 200, 30, 80, BLACK);

	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawRectangleV(player1, player_size, BLACK);
	DrawRectangleV(player2, player_size, BLACK);
	DrawCircleV(ball, 10.0f, BLACK);	

	EndDrawing();

	}

	CloseWindow();

	return 0; 
}
