#include <raylib.h>
#include <vector>
#include <random>
#include <sstream>

#define CELL_SIZE 40

using namespace std;

class Minesweeper {
private:
    vector<vector<int>> board;
    vector<vector<bool>> revealed;
    int rows, cols, numMines;
    bool gameOver = false;

public:
    Minesweeper(int rows, int cols, int numMines) : rows(rows), cols(cols), numMines(numMines) {
        board.assign(rows, vector<int>(cols, 0));
        revealed.assign(rows, vector<bool>(cols, false));
        placeMines();
        calculateNumbers();
    }

    void draw() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int x = j * CELL_SIZE;
                int y = i * CELL_SIZE;

                if (revealed[i][j]) {
                    if (board[i][j] == -1) {
                        DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, RED);
                    }
                    else {
                        DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
                        if (board[i][j] > 0) {
                            DrawText(std::to_string(board[i][j]).c_str(), x + 10, y + 10, 30, BLACK);
                        }
                    }
                }
                else {
                    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, GRAY);
                }

                // Draw cell outline
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }
    }

    void revealCell(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || revealed[row][col]) return;
        revealed[row][col] = true;
        if (board[row][col] == -1) {
            gameOver = true;
        }
        else if (board[row][col] == 0) {
            revealNeighbors(row, col);
        }
    }

    bool isGameOver() {
        return gameOver;
    }

private:
    void placeMines() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> disRows(0, rows - 1);
        uniform_int_distribution<> disCols(0, cols - 1);

        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int row = disRows(gen);
            int col = disCols(gen);
            if (board[row][col] != -1) {
                board[row][col] = -1; // -1 represents a mine
                minesPlaced++;
            }
        }
    }

    void calculateNumbers() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] != -1) {
                    int count = 0;
                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            int ni = i + k, nj = j + l;
                            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == -1) {
                                count++;
                            }
                        }
                    }
                    board[i][j] = count;
                }
            }
        }
    }

    void revealNeighbors(int row, int col) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int ni = row + i, nj = col + j;
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                    revealCell(ni, nj);
                }
            }
        }
    }
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    int rows = 10;
    int cols = 10;
    int numMines = 15;

    InitWindow(screenWidth, screenHeight, "Minesweeper");

    SetTargetFPS(60);

    Minesweeper game(rows, cols, numMines);

    while (!WindowShouldClose() && !game.isGameOver()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.draw();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX() / CELL_SIZE;
            int mouseY = GetMouseY() / CELL_SIZE;
            game.revealCell(mouseY, mouseX);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
