/**Solutions to Chapter 1, Section 3, Exercise 8 of Horowitz's Fundamentals of
 * Data Structures in C.
 */

#include <stdio.h>

#define MAX_SIZE 15 /* Maximum size of square */
int square[MAX_SIZE][MAX_SIZE];

void init(); /* array initialization function */
void magic_square(int n, int row, int column);

int size; /* square size */

void main() {
    int i, j;

    printf("If you want to quit, enter a negative integer.\n");

    while(1) {
        printf("Enter the size of the square: ");
        scanf("%d", &size);

        if(size < 1)
            break;

        /* Exception handling for out of range size */
        if(size > MAX_SIZE + 1) {
            printf("Error! Size is out of range. Please re-enter!\n");
            continue;
        }

        /* Size must be odd */
        if(!(size % 2)) {
            printf("Error! Size is even. Please re-enter!\n");
            continue;
        }

        init(); /* Initialization */

        /* Initially place 1 */
        magic_square(1, 0, (size - 1) / 2);

        /* Print magic_square */
        for(i = 0; i < size; i++) {
            for(j = 0; j < size; j++)
                printf("%4d", square[i][j]);
            printf("\n");
        }
    }
}

void magic_square(int n, int row, int column) {
    int r, c;

    /* Store values in the passed row and column */
    square[row][column] = n;

    /* New position */
    r = (row - 1 < 0) ? (size - 1) : (row - 1);
    c = (column - 1 < 0) ? (size - 1) : (column - 1);

    /* If there's a value in the new position, move to the next row below the previous position */
    if(square[r][c]) {
        r = (++row) % size;
        c = column;
    }

    if(n >= size * size)
        return;

    magic_square(n + 1, r, c);
}

void init() {
    int i, j;

    for(i = 0; i < MAX_SIZE; i++)
        for(j = 0; j < MAX_SIZE; j++)
            square[i][j] = 0;
}

