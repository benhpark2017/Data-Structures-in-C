/**Solutions to Chapter 2, Section 4, Exercise 6 of Horowitz's
 * Data Structures in C.*/

#include <stdio.h>
#define MAX_SIZE 100
#define ROW_SIZE 6
#define COL_SIZE 6

typedef struct {
    int row;
    int col;
    int value;
} term;

term d[MAX_SIZE];

int one_dimension_array_a[] = {15, 22, -15, 11, 3, -6, 91, 28};
int two_dimension_array_a[ROW_SIZE][COL_SIZE] = {
    {1, 0, 0, 1, 0, 1},
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0}
};

int one_dim_array_b[] = {1, 2, 3, 4, 5, 6};
int two_dim_array_b[ROW_SIZE][COL_SIZE] ={
    {1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1},
};

int sum();

int main() {
    int i, print_count;
    print_count = sum();
    for (i = 0; i < print_count; ++i)
        printf("%d, %d, %d\n", d[i].row, d[i].col, d[i].value);
    return 0;
}

int sum() {
    int row, col;
    int start_a = 0, start_b = 0, start_d = 0;
    for (row = 0; row < ROW_SIZE; ++row) {
        for (col = 0; col < COL_SIZE; ++col) {
            if (two_dimension_array_a[row][col] || two_dim_array_b[row][col]) {
                if (two_dimension_array_a[row][col] && two_dim_array_b[row][col]) {
                    d[start_d].row = row;
                    d[start_d].col = col;
                    d[start_d++].value = one_dimension_array_a[start_a++] + one_dim_array_b[start_b++];
                } else if (two_dimension_array_a[row][col]) {
                    d[start_d].row = row;
                    d[start_d].col = col;
                    d[start_d++].value = one_dimension_array_a[start_a++];
                } else {
                    d[start_d].row = row;
                    d[start_d].col = col;
                    d[start_d++].value = one_dim_array_b[start_b++];
                }
            }
        }
    }
    return start_d;
}

