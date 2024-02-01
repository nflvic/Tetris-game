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
    L_BLOCK,
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

void moveBlock(Block *b, int columns, int rows) {
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
            .color = VIOLET,
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

        moveBlock(&tmp, -1, 3);

        memcpy(lb, &tmp, sizeof(Block));
}

void InitLBlock(Block *lb) {
        Block tmp = {
            .color = GREEN,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = L_BLOCK,
            .rotationState = 0,
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
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitIBlock(Block *lb) {
        Block tmp = {
            .color = RED,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = I_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 1, .y = 3 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 2 },
                    [1] = { .x = 1, .y = 2 },
                    [2] = { .x = 2, .y = 2 },
                    [3] = { .x = 3, .y = 2 }
                },
                [2] = {
                    [0] = { .x = 2, .y = 0 },
                    [1] = { .x = 2, .y = 1 },
                    [2] = { .x = 2, .y = 2 },
                    [3] = { .x = 2, .y = 3 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 2, .y = 1 },
                    [3] = { .x = 3, .y = 1 }
                },
            }

        };
        moveBlock(&tmp, -2, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitOBlock(Block *lb) {
        Block tmp = {
            .color = PURPLE,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = O_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 0, .y = 1 },
                    [2] = { .x = 1, .y = 0 },
                    [3] = { .x = 1, .y = 1 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 0, .y = 1 },
                    [2] = { .x = 1, .y = 0 },
                    [3] = { .x = 1, .y = 1 }
                },
                [2] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 0, .y = 1 },
                    [2] = { .x = 1, .y = 0 },
                    [3] = { .x = 1, .y = 1 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 0, .y = 1 },
                    [2] = { .x = 1, .y = 0 },
                    [3] = { .x = 1, .y = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 4);
        memcpy(lb, &tmp, sizeof(Block));
}


void InitSBlock(Block *lb) {
        Block tmp = {
            .color = YELLOW,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = S_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 0, .y = 2 },
                    [2] = { .x = 1, .y = 0 },
                    [3] = { .x = 1, .y = 1 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 2 }
                },
                [2] = {
                    [0] = { .x = 1, .y = 1 },
                    [1] = { .x = 1, .y = 2 },
                    [2] = { .x = 2, .y = 0 },
                    [3] = { .x = 2, .y = 1 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 2, .y = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitZBlock(Block *lb) {
        Block tmp = {
            .color = BLUE,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = Z_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 0, .y = 1 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 1, .y = 2 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 2 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 1 }
                },
                [2] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 2, .y = 1 },
                    [3] = { .x = 2, .y = 2 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 2, .y = 0 }
                },
                }
            };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}


void InitJBlock(Block *lb) {
        Block tmp = {
            .color = PINK,
            .columnOffset = 0,
            .rowOffset = 0,
            .id = J_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .x = 0, .y = 0 },
                    [1] = { .x = 1, .y = 0 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 1, .y = 2 }
                },
                [1] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 0, .y = 2 },
                    [2] = { .x = 1, .y = 1 },
                    [3] = { .x = 2, .y = 1 }
                },
                [2] = {
                    [0] = { .x = 1, .y = 0 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 1, .y = 2 },
                    [3] = { .x = 2, .y = 2 }
                },

                [3] = {
                    [0] = { .x = 0, .y = 1 },
                    [1] = { .x = 1, .y = 1 },
                    [2] = { .x = 2, .y = 0 },
                    [3] = { .x = 2, .y = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}


Block blocks[7] = { 0 };

void initBlock(Block *b, int id) {
    switch(id) {
        case I_BLOCK: InitIBlock(b); break;
        case O_BLOCK: InitOBlock(b); break;
        case J_BLOCK: InitJBlock(b); break;
        case Z_BLOCK: InitZBlock(b); break;
        case T_BLOCK: InitTBlock(b); break;
        case S_BLOCK: InitSBlock(b); break;
        case L_BLOCK: InitLBlock(b); break;
        default: exit(1);
    }
}
int NUM_BLOCKS = 7;

void fillBlocks() {
        for(int i = L_BLOCK; i <= O_BLOCK; i++) {
            Block test = {};

            initBlock(&test, i);
            blocks[i] = test;
        }
}

void generateRandomBlock(Block *b) {

    if(NUM_BLOCKS == 0) {
        fillBlocks();
        NUM_BLOCKS = 7;
    }

    int index = (rand() % NUM_BLOCKS); 
    memcpy(b, &(blocks[index]), sizeof(Block));

    NUM_BLOCKS--;

    for(int i = index; i < 6; i++) {
        memmove(&blocks[i], &blocks[i+1], sizeof(Block));
    }


}

Block currentBlock = {};
Block nextBlock = {};

void drawGame() {
    PrintGrid();
    DisplayGrid();
    DrawBlock(&currentBlock);
}

bool isCellOutSide(int col, int row) {
    if(row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        return false;
    }

    return true;
}


bool isBlockOutside() {
    Position p[NUM_POSITIONS];
    getCellPositions(&currentBlock, p);
    for(int i = 0; i < NUM_POSITIONS; i++) {
        if(isCellOutSide(p[i].x, p[i].y)) {
            return true;
        }
    }
    return false;
}


void moveBlockLeft(){
    moveBlock(&currentBlock, 0, -1);

    if(isBlockOutside()) {
        moveBlock(&currentBlock, 0, 1);
    }
}

void moveBlockRight(){
    moveBlock(&currentBlock, 0, 1);
    if(isBlockOutside()) {
        moveBlock(&currentBlock, 0, -1);
    }
}

void moveBlockDown(){
    moveBlock(&currentBlock, 1, 0);
    if(isBlockOutside()) {
        moveBlock(&currentBlock, -1, 0);
    }
}

void rotateBlock() {
    if(currentBlock.rotationState < 3) {
        currentBlock.rotationState++;
        return;
    }

    currentBlock.rotationState = 0;
}

void unRotateBlock() {
    currentBlock.rotationState--;

    if(currentBlock.rotationState < 0) {
        currentBlock.rotationState = 3;
    }
}

void handleInput() {
    int keyCode = GetKeyPressed();

    switch(keyCode) {
        case KEY_LEFT: 
            moveBlockLeft();
        break;
        case KEY_RIGHT:
            moveBlockRight();
         break;
        case KEY_DOWN: 
            moveBlockDown();
        break;

        case KEY_UP:
            rotateBlock();
            if(isBlockOutside()) {
                unRotateBlock();
            }
        break;
        default: break;
    }
}


int main() {

    InitWindow(300, 600, "Tetris");

    SetTargetFPS(60);

    fillBlocks();
    generateRandomBlock(&currentBlock);
    generateRandomBlock(&nextBlock);


    while(WindowShouldClose() == false) {
        handleInput();
        BeginDrawing();
        ClearBackground(BLACK);

        drawGame();

        EndDrawing();
    }

    CloseWindow();
    
}