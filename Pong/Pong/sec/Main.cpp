#include <iostream>
#include "raylib.h"

int PlayerScore;
int CpuScore;

class Ball
{

public:
	float x, y;
	int XSpeed, YSpeed;
	int radius;

	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}
	void Update()
	{
		x += XSpeed;
		y += YSpeed;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			YSpeed *= -1;
		}
		if (x + radius >= GetScreenWidth())
		{
			CpuScore++;
			ResetBall();
		}
		if (x - radius <= 0)
		{
			PlayerScore++;
			ResetBall();
		}

	}

	void ResetBall()
	{
		x = GetScreenHeight() / 2;
		y = GetScreenWidth() / 2;

		int SpeedChoices[2] = { -1, 1 };
		XSpeed *= SpeedChoices[GetRandomValue(0, 1)];
		YSpeed *= SpeedChoices[GetRandomValue(0, 1)];
	}
};

class Paddle
{
protected:
	void LimitMovement()
	{
		if (y <= 0)
		{
			y = 0;
		}
		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}

	}

public:
	float x, y;
	float width, height;
	int speed;

	void Draw()
	{
		DrawRectangle(x, y, 25, 120, WHITE);
	}
	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;
		}
		LimitMovement();

	}
};


class CpuPaddle : public Paddle
{
public:
	void Update(int YBall)
	{
		if (y + height / 2 > YBall)
		{
			y = y - speed;
		}
		if (y + height / 2 <= YBall)
		{
			y = y + speed;
		}
	}
};

Ball b;
Paddle player;
CpuPaddle cpu;
int main()
{
	std::cout << "Game Started";
	const int ScreenWidth = 1920;
	const int ScreenHeight = 1080;
	InitWindow(ScreenWidth, ScreenHeight, "pong");

	b.radius = 30;
	b.x = ScreenWidth / 2;
	b.y = ScreenHeight / 2;
	b.XSpeed = 2;
	b.YSpeed = 2;

	player.width = 25;
	player.height = 120;
	player.x = ScreenWidth - player.width - 10;
	player.y = ScreenHeight / 2 - player.height / 2;
	player.speed = 6;

	cpu.height = 120;
	cpu.width = 25;
	cpu.x = 10;
	cpu.y = ScreenHeight / 2 - cpu.height / 2;
	cpu.speed = 2;

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		b.Update();
		player.Update();
		cpu.Update(b.y);

		if (CheckCollisionCircleRec(Vector2{ b.x,b.y }, b.radius, Rectangle{ player.x, player.y, player.width,player.height }))
		{
			b.XSpeed *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ b.x,b.y }, b.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height }))
		{
			b.XSpeed *= -1;
		}

		ClearBackground(BLACK);
		DrawLine(ScreenWidth / 2, 0, ScreenWidth / 2, ScreenHeight, WHITE);
		b.Draw();
		cpu.Draw();
		player.Draw();
		DrawText(TextFormat("%i", CpuScore), ScreenWidth / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", PlayerScore), 3 * ScreenWidth / 4 - 20, 20, 80, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}