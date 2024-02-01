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

bool GAME_OVER = false;

typedef enum BlockID BlockID;
enum BlockID {
    T_BLOCK,
    I_BLOCK,
    L_BLOCK,
    J_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    O_BLOCK,
};

typedef struct Position Position;
struct Position {
    int     row;//x
    int     column;//y
};

typedef struct Block Block ;
struct Block {
    BlockID id;

    int rotationState;
    int rowOffset;
    int colOffset;

    Position cells[NUM_STATES][NUM_POSITIONS];

    Color color;
};

int grid[NUM_ROWS][NUM_COLS] = { 0 };

Block currentBlock = {};
Block nextBlock = {};

Color colors[] = {
    BROWN, GREEN, RED, ORANGE, YELLOW, PURPLE, PINK, BLUE, MAROON
};

Block blocks[7] = { 0 };

void PrintGrid(){
    return;
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
    b->colOffset += columns;
}

void getCellPositions(Block *b, Position cells[]) {
    Position *tiles = b->cells[b->rotationState];

    for(int i = 0; i < NUM_POSITIONS; i++) {
        cells[i].row = tiles[i].row + b->rowOffset;
        cells[i].column = tiles[i].column + b->colOffset;
    }
}

void DrawBlock(Block *b) {
    Position poss[NUM_POSITIONS] = { 0 };

    getCellPositions(b, poss);

    for(int i = 0; i < NUM_POSITIONS; i++) {
        printf("(%d, %d)\n",poss[i].row, poss[i].column);

        DrawRectangle(poss[i].column * CELL_SIZE + 1, poss[i].row * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1, b->color);
        //break;
    }
}

void DisplayGrid() {
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int column = 0; column < NUM_COLS; column++){

            int cellvalue = grid[row][column];

            /*bug*/
            if(cellvalue == 0) {
                //cellvalue = 8;
            }

            DrawRectangle((column * CELL_SIZE) + 1, (row * CELL_SIZE) + 1, CELL_SIZE - 1, CELL_SIZE - 1, colors[cellvalue]);
        }
    }
}

void InitTBlock(Block *lb) {
        Block tmp = {
            .color = VIOLET,
            .colOffset = 0,
            .rowOffset = 0,
            .rotationState = 0,
            .id = T_BLOCK,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 1, .column = 2 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 1 }
                },
                [2] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 1 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 2, .column = 1 }
                },
            }

        };

        moveBlock(&tmp, -1, 3);

        memcpy(lb, &tmp, sizeof(Block));
}

void InitLBlock(Block *lb) {
        Block tmp = {
            .color = GREEN,
            .colOffset = 0,
            .rowOffset = 0,
            .id = L_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 2 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 1, .column = 2 }
                },
                [1] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 2 }
                },
                [2] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 2, .column = 1 },
                    [3] = { .row = 0, .column = 2 }
                },

                [3] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 0, .column = 0 }
                },
            }

        };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitIBlock(Block *lb) {
        Block tmp = {
            .color = RED,
            .colOffset = 0,
            .rowOffset = 0,
            .id = I_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 1, .column = 3 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 2 },
                    [1] = { .row = 1, .column = 2 },
                    [2] = { .row = 2, .column = 2 },
                    [3] = { .row = 3, .column = 2 }
                },
                [2] = {
                    [0] = { .row = 2, .column = 0 },
                    [1] = { .row = 2, .column = 1 },
                    [2] = { .row = 2, .column = 2 },
                    [3] = { .row = 2, .column = 3 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 2, .column = 1 },
                    [3] = { .row = 3, .column = 1 }
                },
            }

        };
        moveBlock(&tmp, -2, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitOBlock(Block *lb) {
        Block tmp = {
            .color = PURPLE,
            .colOffset = 0,
            .rowOffset = 0,
            .id = O_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 0, .column = 1 },
                    [2] = { .row = 1, .column = 0 },
                    [3] = { .row = 1, .column = 1 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 0, .column = 1 },
                    [2] = { .row = 1, .column = 0 },
                    [3] = { .row = 1, .column = 1 }
                },
                [2] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 0, .column = 1 },
                    [2] = { .row = 1, .column = 0 },
                    [3] = { .row = 1, .column = 1 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 0, .column = 1 },
                    [2] = { .row = 1, .column = 0 },
                    [3] = { .row = 1, .column = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 4);
        memcpy(lb, &tmp, sizeof(Block));
}


void InitSBlock(Block *lb) {
        Block tmp = {
            .color = YELLOW,
            .colOffset = 0,
            .rowOffset = 0,
            .id = S_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 0, .column = 2 },
                    [2] = { .row = 1, .column = 0 },
                    [3] = { .row = 1, .column = 1 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 2 }
                },
                [2] = {
                    [0] = { .row = 1, .column = 1 },
                    [1] = { .row = 1, .column = 2 },
                    [2] = { .row = 2, .column = 0 },
                    [3] = { .row = 2, .column = 1 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 2, .column = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}

void InitZBlock(Block *lb) {
        Block tmp = {
            .color = BLUE,
            .colOffset = 0,
            .rowOffset = 0,
            .id = Z_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 0, .column = 1 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 1, .column = 2 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 2 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 1 }
                },
                [2] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 2, .column = 1 },
                    [3] = { .row = 2, .column = 2 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 2, .column = 0 }
                },
                }
            };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}


void InitJBlock(Block *lb) {
        Block tmp = {
            .color = PINK,
            .colOffset = 0,
            .rowOffset = 0,
            .id = J_BLOCK,
            .rotationState = 0,
            .cells = {
                [0] = {
                    [0] = { .row = 0, .column = 0 },
                    [1] = { .row = 1, .column = 0 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 1, .column = 2 }
                },
                [1] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 0, .column = 2 },
                    [2] = { .row = 1, .column = 1 },
                    [3] = { .row = 2, .column = 1 }
                },
                [2] = {
                    [0] = { .row = 1, .column = 0 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 1, .column = 2 },
                    [3] = { .row = 2, .column = 2 }
                },

                [3] = {
                    [0] = { .row = 0, .column = 1 },
                    [1] = { .row = 1, .column = 1 },
                    [2] = { .row = 2, .column = 0 },
                    [3] = { .row = 2, .column = 1 }
                },
            }

        };
        moveBlock(&tmp, -1, 3);
        memcpy(lb, &tmp, sizeof(Block));
}


//last

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
        for(int i = 0; i <= 6; i++) {
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



void drawGame() {
    PrintGrid();
    DisplayGrid();
    DrawBlock(&currentBlock);
}

bool isCellOutSide(int row, int col) {
    if(row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        return false;
    }

    return true;
}


bool isBlockOutside() {
    Position p[NUM_POSITIONS];
    getCellPositions(&currentBlock, p);
    for(int i = 0; i < NUM_POSITIONS; i++) {
        if(isCellOutSide(p[i].row, p[i].column)) {
            return true;
        }
    }
    return false;
}

void lockBlock();

bool isCellEmpty(int row, int col);

bool blockFits();

void moveBlockLeft(){
    moveBlock(&currentBlock, 0, -1);

    if(isBlockOutside() || blockFits() == false) {
        moveBlock(&currentBlock, 0, 1);
    }
}

void moveBlockRight(){
    moveBlock(&currentBlock, 0, 1);
    if(isBlockOutside() || blockFits() == false) {
        moveBlock(&currentBlock, 0, -1);
    }
}



void moveBlockDown(){
    moveBlock(&currentBlock, 1, 0);
    if(isBlockOutside() || blockFits() == false) {
        moveBlock(&currentBlock, -1, 0);
        lockBlock();
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

bool rowIsFull(int row) {
    for(int i = 0; i < NUM_COLS; i++) {
        if(grid[row][i] == 0) {
            return false;
        }
    }

    return true;
}


void clearRow(int row) {
    for(int i = 0; i < NUM_COLS; i++) {
        grid[row][i] = 0;
    }
}

void moveRowDown(int row, int numRows) {
    for(int i = 0; i < NUM_COLS; i++){
        grid[row+ numRows][i] = grid[row][i];
        grid[row][i] = 0;
    }
}

int clearFullRows() {
    int completed = 0;

    for(int i = NUM_ROWS - 1; i >= 0; i--) {
        if(rowIsFull(i)) {
            clearRow(i);
            completed++;
        } else if(completed > 0) {
            moveRowDown(i, completed);
        }
    }

    return completed;
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

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}


/*bug*/
void lockBlock() {
    Position p[NUM_POSITIONS];
    getCellPositions(&currentBlock, p);


    for(int i = 0; i < NUM_POSITIONS; i++) {
        if(currentBlock.id == 0) {
            grid[p[i].row][p[i].column] = 4;
        } else {
            grid[p[i].row][p[i].column] = currentBlock.id;
        }
    }

    currentBlock = nextBlock;

    if(blockFits() == false) {
        GAME_OVER = true;
    }

    generateRandomBlock(&nextBlock);
    clearFullRows();

}

bool isCellEmpty(int row, int col) {
    if(grid[row][col] == 0) {
        return true;
    }
    return false;
}

bool blockFits() {
    Position p[NUM_POSITIONS];
    getCellPositions(&currentBlock, p);

    for(int i = 0; i < NUM_POSITIONS; i++) {
        if(isCellEmpty(p[i].row, p[i].column) == false) {
            return false;
        }
    }

    return true;
}



int main() {

    InitWindow(300, 600, "Tetris");

    SetTargetFPS(60);

    fillBlocks();
    generateRandomBlock(&currentBlock);
    generateRandomBlock(&nextBlock);


    while(WindowShouldClose() == false && GAME_OVER == false) {
        handleInput();

        if(eventTriggered(0.2)) {
            moveBlockDown();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        drawGame();

        EndDrawing();
    }

    CloseWindow();
    
}