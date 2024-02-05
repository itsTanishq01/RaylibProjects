#include <iostream>
#include <raylib.h>
#include <raymath.h>

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
        // Draw four rectangles to make the outline thicker
        DrawRectangleLines(offsetX - 2, offsetY - 2, width + 4, height + 4, color);
        DrawRectangleLines(offsetX - 1, offsetY - 1, width + 2, height + 2, color);
        DrawRectangleLines(offsetX, offsetY, width, height, color);
        DrawRectangleLines(offsetX + 1, offsetY + 1, width - 2, height - 2, color);
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
        while (!gameover && !WindowShouldClose())
        {
            Update();
            Draw();
        }

        if (gameover)
        {
            ShowScoreScreen();
        }
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
        DrawText(TextFormat("Hits: %d", hits), screenWidth - 100, screenHeight - 50, 20, darkGreen);
        DrawText(TextFormat("Time: %d", timer), screenWidth - 100, screenHeight - 30, 20, darkGreen);
        DrawText("Aim Trainer", 10, 10, 40, darkGreen); 
        EndDrawing();
    }

    void ShowScoreScreen()
    {
        // Display score screen
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(green);
            DrawText("Game Over!", 10, 10, 40, darkGreen);
            DrawText(TextFormat("Hits: %d", hits), 10, 60, 30, darkGreen);
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
