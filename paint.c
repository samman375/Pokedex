// Assignment 1 19T3 COMP1511: CS Paint
// paint.c

// This program was written by Samuel Thorley (z5257239) 11-10-2019

// Version 1.0.0 (2019-10-08): Assignment released.

// Final Version up to end of copy and paste


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// The dimensions of the canvas
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define DARK 1
#define GREY 2
#define LIGHT 3
#define WHITE 4

// Prototype functions
void displayCanvas(int canvas[N_ROWS][N_COLS]);
void clearCanvas(int canvas[N_ROWS][N_COLS]);
double distance(int row1, int col1, int row2, int col2);
void drawLine(
    int length, 
    int start_col, 
    int start_row, 
    int direction,
    int canvas[N_ROWS][N_COLS],
    int colour,
    int colourDiff
);
void drawSquare( 
    int length, 
    int start_col, 
    int start_row, 
    int direction,
    int canvas[N_ROWS][N_COLS],
    int colour,
    int colourDiff
);
int shade(int colourDiff, int colour);
void copyPaste(
    int start_row,
    int start_col,
    int length,
    int direction,
    int target_row,
    int target_col,
    int canvas[N_ROWS][N_COLS]
);



int main(void) {
    int canvas[N_ROWS][N_COLS];
    int instruction;
    int start_row;
    int start_col;
    int length;
    int direction;
    int colourDiff = 0;
    int colour = BLACK;
    int target_row;
    int target_col;

    clearCanvas(canvas);
        
    while (scanf("%d", &instruction) == 1) {
        if (instruction == 1) {
            scanf("%d %d %d %d", &start_row, &start_col, &length, &direction);
            if (length < 0) {
                length = abs(length);
                direction = direction + 180;    
            }
            drawLine(
                length, 
                start_col, start_row, 
                direction, 
                canvas, 
                colour, 
                colourDiff
            );
        } else if (instruction == 2) {
            scanf("%d %d %d %d", &start_row, &start_col, &length, &direction);
            if (length < 0) {
                length = abs(length);
                direction = direction + 180;    
            }
            drawSquare(
                length, 
                start_col, start_row, 
                direction, 
                canvas, 
                colour, 
                colourDiff
            );    
        } else if (instruction == 3) {
            scanf("%d", &colourDiff);
            if (colour + colourDiff >= 0 && colour + colourDiff <= 4) {
                colour = shade(colourDiff, colour);
            }
        } else if (instruction == 4) {
            scanf(
                "%d %d %d %d %d %d", 
                &start_row, &start_col, 
                &length, 
                &direction, 
                &target_row, &target_col
            );
            if (length < 0) {
                length = abs(length);
                direction = direction + 180;    
            }
            copyPaste(
                start_row, start_col, 
                length, 
                direction, 
                target_row, target_col, 
                canvas
            );
        }
    }
    displayCanvas(canvas);
    return 0;
}



void drawLine(
    int length, 
    int start_col, 
    int start_row, 
    int direction,
    int canvas[N_ROWS][N_COLS],
    int colour,
    int colourDiff
) {
    if (
        length > 0 &&
        start_row >= 0 && start_row < N_ROWS &&
        start_col >= 0 && start_col < N_COLS
    ) {
        int i = 0;
        while (i < length) {
            if (direction % 360 == 0 && start_row - length + 1 >= 0) {
                canvas[start_row - i][start_col] = colour;
            } else if (direction % 360 == 180 && start_row + length <= N_ROWS) {
                canvas[start_row + i][start_col] = colour;
            } else if (direction % 360 == 270 && start_col - length + 1 >= 0) {
                canvas[start_row][start_col - i] = colour;
            } else if (direction % 360 == 90 && start_col + length <= N_COLS) {
                canvas[start_row][start_col + i] = colour;
            } else if (
                direction % 360 == 135 &&
                start_col + length <= N_COLS &&
                start_row + length <= N_ROWS
            ) {
                canvas[start_row + i][start_col + i] = colour;
            } else if (
                direction % 360 == 315 &&
                start_col - length + 1 >= 0 &&
                start_row - length + 1 >= 0
            ) {
                canvas[start_row - i][start_col - i] = colour;
            } else if (
                direction % 360 == 225 &&
                start_col - length + 1 >= 0 &&
                start_row + length <= N_ROWS
            ) {
                canvas[start_row + i][start_col - i] = colour;
            } else if (
                direction % 360 == 45 &&
                start_col + length <= N_COLS &&
                start_row - length + 1 >= 0
            ) {
                canvas[start_row - i][start_col + i] = colour;
            }
            i++;
        }
    }
}

void drawSquare(
    int length, 
    int start_col, 
    int start_row, 
    int direction,
    int canvas[N_ROWS][N_COLS],
    int colour,
    int colourDiff
) {
    int i = 0;
    if (
        length > 0 &&
        start_col >= 0 && start_col < N_COLS &&
        start_row >= 0 && start_row < N_ROWS
    ) {
        // If draw line is required
        if (direction == 0 || 
            direction % 360 == 0 ||
            direction % 270 == 0 ||
            direction % 90 == 0
        ) {
            drawLine(
                length, 
                start_col, 
                start_row, 
                direction, 
                canvas, 
                colour, 
                colourDiff
            );
        }
        // Drawing Squares
        else if (
            direction % 360 == 315 &&
            start_col - length + 1 >= 0 && 
            start_row - length + 1 >= 0
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[start_row - i][start_col - j] = colour;
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 135 &&
            start_col + length <= N_COLS && 
            start_row + length <= N_ROWS
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[start_row + i][start_col + j] = colour;
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 225 &&
            start_col - length + 1 >= 0 && 
            start_row + length <= N_ROWS
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[start_row + i][start_col - j] = colour;
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 45 &&
            start_col + length <= N_COLS && 
            start_row - length + 1 >= 0
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[start_row - i][start_col + j] = colour;
                    j++;
                }
                i++;
            }
        }
    }
}

int shade(int colourDiff, int colour) {
    return colour + colourDiff;
}

void copyPaste(
    int start_row, 
    int start_col,
    int length,
    int direction,
    int target_row, 
    int target_col,
    int canvas[N_ROWS][N_COLS]
) {
    if (
        length > 0 &&
        start_row >= 0 && start_row < N_ROWS &&
        start_col >= 0 && start_col < N_COLS &&
        target_row >= 0 && target_row < N_ROWS &&
        target_col >= 0 && target_col < N_COLS
    ) {
        int i = 0;
        if (
            direction % 360 == 0 &&
            start_row - length + 1 >= 0 &&
            target_row - length + 1 >= 0
        ) {
            while (i < length) {
                canvas[target_row - i][target_col] = 
                canvas[start_row - i][start_col];
                i++;
            }
        } else if (
            direction % 360 == 90 &&
            start_col + length <= N_COLS &&
            target_col + length <= N_COLS
        ) {
            while (i < length) {
                canvas[target_row][target_col + i] =
                canvas[start_row][start_col + i];
                i++;
            }
        } else if (
            direction % 360 == 180 &&
            start_row + length <= N_ROWS &&
            target_row + length <= N_ROWS
        ) {
            while (i < length) {
                canvas[target_row + i][target_col] =
                canvas[start_row + i][start_col];
                i++;
            }
        } else if (
            direction % 360 == 270 &&
            start_col - length + 1 >= 0 &&
            target_col - length + 1 >= 0
        ) {
            while (i < length) {
                canvas[target_row][target_col - i] =
                canvas[start_row][start_col - i];
                i++;
            }
        } else if (
            direction % 360 == 45 &&
            start_col + length <= N_COLS &&
            start_row - length + 1 >= 0 &&
            target_col + length <= N_COLS &&
            target_row - length + 1 >= 0
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[target_row - i][target_col + j] =
                    canvas[start_row - i][start_col + j];
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 135 &&
            start_col + length <= N_COLS &&
            start_row + length <= N_ROWS &&
            target_col + length <= N_COLS &&
            target_row + length <= N_ROWS
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[target_row + i][target_col + j] =
                    canvas[start_row + i][start_col + j];
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 225 &&
            start_col - length + 1 >= 0 &&
            start_row + length <= N_ROWS &&
            target_col - length + 1 >= 0 &&
            target_row + length <= N_ROWS
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[target_row + i][target_col - j] =
                    canvas[start_row + i][start_col - j];
                    j++;
                }
                i++;
            }
        } else if (
            direction % 360 == 315 &&
            start_col - length + 1 >= 0 &&
            start_row - length + 1 >= 0 &&
            target_col - length + 1 >= 0 &&
            target_row - length + 1 >= 0
        ) {
            while (i < length) {
                int j = 0;
                while (j < length) {
                    canvas[target_row - i][target_col - j] =
                    canvas[start_row - i][start_col - j];
                    j++;
                }
                i++;
            }
        }
    }
}

// Provided Functions
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}

void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

// Calculate the distance between two points (row1, col1) and (row2, col2).
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}
