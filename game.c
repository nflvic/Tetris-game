#include <raylib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CELL_SIZE       30
#define NUM_COLS        10
#define NUM_ROWS        20
#define NUM_COLOURS     8
#define NUM_POSITIONS   4
#define NUM_STATES      4

typedef enum BlockID BlockID;
enum BlockID {
    L_BLOCK  = 200,
    J_BLOCK,
    I_BLOCK,
    S_BLOCK,
    T_BLOCK,
    Z_BLOCK,
    O_BLOCK,
};

typedef struct Position Position;
struct Position {
    int     x; 
    int     y;
};

typedef struct Block Block ;
struct Block {
    BlockID id;

    int rotationState;
    int rowOffset;
    int columnOffset;

    Position cells[NUM_STATES][NUM_POSITIONS];

    Color color;
};

int grid[NUM_ROWS][NUM_COLS] = { 0 };

Color colors[] = {
    DARKGRAY, GREEN, RED, ORANGE, YELLOW, PURPLE, PINK, BLUE
};

void PrintGrid(){
    printf("[\n");

    for(int i = 0; i < NUM_ROWS; i++) {

        printf("    ");
        for(int j = 0; j < NUM_COLS; j++) {
            printf("%d ", grid[i][j]);
        }

        printf("\n");
    }

    printf("]\n");
}

void moveBlock(Block *b, int rows, int columns) {
    b->rowOffset += rows;
    b->columnOffset += columns;
}

void getCellPositions(Block *b, Position cells[]) {
    Position *tiles = b->cells[b->rotationState];

    for(int i = 0; i < NUM_POSITIONS; i++) {
        cells[i].x = tiles[i].x + b->rowOffset;
        cells[i].y = tiles[i].y + b->columnOffset;
    }
}

void DrawBlock(Block *b) {
    Position poss[NUM_POSITIONS] = { 0 };

    getCellPositions(b, poss);

    for(int i = 0; i < NUM_POSITIONS; i++) {
        printf("(%d, %d)\n",poss[i].x, poss[i].y);

        DrawRectangle(poss[i].x * CELL_SIZE + 1, poss[i].y * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1, b->color);
        //break;
    }
}

void DisplayGrid() {
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int column = 0; column < NUM_COLS; column++){

            int cellvalue = grid[row][column];

            DrawRectangle((column * CELL_SIZE) + 1, (row * CELL_SIZE) + 1, CELL_SIZE - 1, CELL_SIZE - 1, colors[cellvalue]);
        }
    }
}

void InitTBlock(Block *lb) {
        Block tmp = {
            .color = RED,
            .columnOffset = 0,
            .rowOffset = 0,
            .rotationState = 0,
            .id = T_BLOCK,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 1, .y = 2 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 1 }
                },
                [2] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 1 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 2, .y = 1 }
                },
            }

        };

        memcpy(lb, &tmp, sizeof(Block));
}

void InitLBlock(Block *lb) {
        Block tmp = {
            .color = RED,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = L_BLOCK,
            .rotationState = 2,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 2 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 1, .y = 2 }
                },
                [1] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 2 }
                },
                [2] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 2, .y = 1 },
                    [3] = { .x = 0, .y = 2 }
                },

                [3] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 0, .y = 0 }
                },
            }

        };

        memcpy(lb, &tmp, sizeof(Block));
}

int main() {

    InitWindow(300, 600, "Tetris");

    SetTargetFPS(60);


    //grid.grid[10][9] = 4;
    //grid.grid[10][8] = 4;
    //grid.grid[10][7] = 4;

    PrintGrid();

    Block test = {};

    InitLBlock(&test);
    moveBlock(&test, 5, 1);


    while(WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(BLACK);
        DisplayGrid();

        DrawBlock(&test);
        
        

        EndDrawing();
    }

    CloseWindow();
    
}