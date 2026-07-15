#include <stdio.h> 
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

int main()
{
	const float screenWidth = 800;
	const float screenHeight = 450;
	const float square_length = 100;


 	int board[3][3] = {0}; //0 for empty, 1 for X, 2 for O
	int turn = 0;
	bool gameOver = false;

	InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
	
	Vector2 center = { screenWidth/2, screenHeight/2 };

	Image x_image = LoadImage("Images/cross.png");
	Texture2D x_texture = LoadTextureFromImage(x_image);
	UnloadImage(x_image);
x'
	Image o_image = LoadImage("Images/circle.png");
	Texture2D o_texture = LoadTextureFromImage(o_image);
	UnloadImage(o_image);

	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		
	if (!gameOver && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		int i, j;
		turn += 1;
		for (i = -1; i < 3; i++) if (GetTouchPosition(0).x < (center.x - 0.5 * square_length + i * square_length)) break; 
		for (j = -1; j < 3; j++) if (GetTouchPosition(0).y < (center.y - 0.5 * square_length + j * square_length)) break; 
		if(board[i][j] == 0) board[i][j] = (turn % 2 == 0) ? 2 : 1;
		//printf("Turn %d: i: %d, j: %d\n", turn, i, j);
		printf("\n");
		printf("Turn %d: User pressed square [%d, %d]\n", turn, i, j);
		for (int i = 0 ; i < 3; i++) printf("%d %d %d\n", board[i][j], board[i][j+1], board[i][j+1]);
		printf("\n");
	}

	BeginDrawing();

	ClearBackground(WHITE);

	// Draw Board	
	DrawLine(center.x - 0.5 * square_length,center.y + 1.5 * square_length,center.x - 0.5 * square_length,center.y - 1.5 * square_length,BLACK);
	DrawLine(center.x + 0.5 * square_length,center.y + 1.5 * square_length,center.x + 0.5 * square_length,center.y - 1.5 * square_length,BLACK);
	DrawLine(center.x - 1.5 * square_length,center.y + 0.5 * square_length,center.x + 1.5 * square_length,center.y + 0.5 * square_length,BLACK);
	DrawLine(center.x - 1.5 * square_length,center.y - 0.5 * square_length,center.x + 1.5 * square_length,center.y - 0.5 * square_length,BLACK);

	//DrawTexture(o_texture, screenWidth/2 - o_texture.width/2, screenHeight/2 - o_texture.height/2, WHITE);

	//for (int n = 0; n < turn; n++) DrawTexture(x_texture, 10 + center.x - 2.5 * square_length + i * square_length, 10 + center.y - 2.5 * square_length + j * square_length, WHITE);		
	//for (int n = 0; n < turn; n++) printf("Turn %d: i: %d, j: %d\n", turn, [turn][0], [turn][1]);	
	

	EndDrawing();

	}

	CloseWindow();
	return 0; 
}
