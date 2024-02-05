#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>

Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };

class Box
{
public:
    int width;
    int height;
    int offsetX;
    int offsetY;

    Box(int screenWidth, int screenHeight, int boxWidth, int boxHeight)
    {
        width = boxWidth;
        height = boxHeight;
        offsetX = (screenWidth - boxWidth) / 2;
        offsetY = (screenHeight - boxHeight) / 2;
    }

    void Draw(Color color)
    {
        DrawRectangleLines(offsetX, offsetY, width, height, color);
    }
};

class Target
{
public:
    float x, y;
    int radius;

    Target(int minX, int maxX, int minY, int maxY, int targetRadius)
    {
        x = GetRandomValue(minX + targetRadius, maxX - targetRadius);
        y = GetRandomValue(minY + targetRadius, maxY - targetRadius);
        radius = targetRadius;
    }

    void Draw(Color color)
    {
        DrawCircle(x, y, radius, color);
    }
};

class Game
{
public:
    int screenWidth;
    int screenHeight;
    Box box;
    Target target;
    int hits;
    int timer;
    bool gameover;

    Game(int width, int height, int boxWidth, int boxHeight, int targetRadius)
        : screenWidth(width), screenHeight(height), box(width, height, boxWidth, boxHeight),
        target(box.offsetX, box.offsetX + box.width, box.offsetY, box.offsetY + box.height, targetRadius),
        hits(0), timer(60), gameover(false)
    {
        InitWindow(screenWidth, screenHeight, "Aim");
        SetTargetFPS(60);
    }

    ~Game()
    {
        CloseWindow();
    }

    void Run()
    {
        while (!gameover)
        {
            Update();
            Draw();
        }

        ShowScoreScreen();
    }

private:
    void Update()
    {
        static float timeAccumulator = 0.0f;

        timeAccumulator += GetFrameTime();

        if (timeAccumulator >= 1.0f)
        {
            timer--;
            timeAccumulator -= 1.0f;
        }

        if (timer <= 0)
        {
            gameover = true;
        }

        if (!gameover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointCircle(mousePos, { target.x, target.y }, target.radius))
            {
                hits++;
                target = Target(box.offsetX, box.offsetX + box.width, box.offsetY, box.offsetY + box.height, target.radius);
            }
        }
    }

    void Draw()
    {
        BeginDrawing();
        ClearBackground(green);
        box.Draw(darkGreen);
        target.Draw(darkGreen);
        DrawText(TextFormat("Hits: %d", hits), screenWidth - 150, screenHeight - 40, 20, darkGreen);
        DrawText(TextFormat("Time: %d", timer), screenWidth - 150, screenHeight - 70, 20, darkGreen);
        DrawText("AimTrainer", 10, 10, 30, darkGreen);
        EndDrawing();
    }

    void ShowScoreScreen()
    {
        // Display score screen
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(green);
            DrawText("Game Over!", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, darkGreen);
            DrawText(TextFormat("Hits: %d", hits), screenWidth / 2 - 100, screenHeight / 2, 30, darkGreen);
            EndDrawing();
        }
    }
};

int main()
{
    std::cout << "Window Generated" << std::endl;

    int screenWidth = 800;
    int screenHeight = 800;
    int boxWidth = 600;
    int boxHeight = 600;
    int targetRadius = 30;

    Game game(screenWidth, screenHeight, boxWidth, boxHeight, targetRadius);
    game.Run();

    return 0;
}
