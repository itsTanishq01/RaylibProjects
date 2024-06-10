
#include "raylib.h"
#include "Pixel.h"

Color canvas[canvasWidth][canvasHeight];

Color drawColor = WHITE;

// Function to draw the canvas
void DrawCanvas()
{
    for (int x = 0; x < canvasWidth; x++)
    {
        for (int y = 0; y < canvasHeight; y++)
        {
            DrawRectangle(x * pixelSize, y * pixelSize, pixelSize, pixelSize, canvas[x][y]);
        }
    }
}


// Function to draw the toolbar
void DrawToolbar()
{
    DrawRectangle(0, 0, screenWidth, 50, GRAY);
    DrawText("Toolbar:", 10, 10, 20, BLACK);

    // Color buttons
    DrawRectangle(200, 10, 80, 30, RED);
    DrawText("Red", 210, 20, 20, WHITE);

    DrawRectangle(300, 10, 80, 30, GREEN);
    DrawText("Green", 310, 20, 20, WHITE);

    DrawRectangle(400, 10, 80, 30, BLUE);
    DrawText("Blue", 410, 20, 20, WHITE);

    DrawRectangle(500, 10, 80, 30, BLACK);
    DrawText("BLACK", 510, 20, 20, WHITE);

    DrawRectangle(600, 10, 80, 30, BLACK);
    DrawText("Eraser", 610, 20, 20, WHITE);
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Pixel Art Editor");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Check for mouse input
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            int canvasX = mouseX / pixelSize;
            int canvasY = mouseY / pixelSize;

            if (canvasX >= 0 && canvasX < canvasWidth && canvasY >= 0 && canvasY < canvasHeight)
            {
                canvas[canvasX][canvasY] = drawColor;
            }
        }

        // Check for toolbar button clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Check if any color button is clicked
            if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, { 200, 10, 80, 30 }))
            {
                drawColor = Red; // Set drawing color to red
            }
            else if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, { 300, 10, 80, 30 }))
            {
                drawColor = Green; // Set drawing color to green
            }
            else if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, { 400, 10, 80, 30 }))
            {
                drawColor = Blue; // Set drawing color to blue
            }
            else if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, { 500, 10, 80, 30 }))
            {
                drawColor = BLACK;
            }
            else if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, { 600, 10, 80, 30 }))
            {
                drawColor = WHITE;
            }
        }

        // Draw canvas and toolbar
        DrawCanvas();
        DrawToolbar();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}