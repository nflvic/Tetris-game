#include <raylib.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#define CELL_SIZE   30
#define NUM_COLS    10
#define NUM_ROWS    20
#define NUM_COLOURS 7

typedef struct Grid Grid;
struct Grid{
    int numRows;
    int numCols;
    int cellSize;

    Color colors[NUM_COLOURS];

    int grid[NUM_ROWS][NUM_COLS];
};


void PrintGrid(Grid *g){
    printf("[\n");

    for(int i = 0; i < g->numRows; i++) {

        printf("    ");
        for(int j = 0; j < g->numCols; j++) {
            printf("%d ", g->grid[i][j]);
        }

        printf("\n");
    }

    printf("]\n");
}

void drawGrid(Grid *g) {
    
}


int main() {

    InitWindow(300, 600, "Tetris");

    SetTargetFPS(60);


    Grid grid = {
        .cellSize = CELL_SIZE,
        .numCols = NUM_COLS,
        .numRows = NUM_ROWS,
        .grid = { 0 },
        .colors = {
            DARKGRAY, GREEN, RED, ORANGE, YELLOW, PURPLE, PINK, BLUE
        }
    };

    PrintGrid(&grid);

    while(WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    
}