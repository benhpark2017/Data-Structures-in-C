/**Solutions to Chapter 2, Section 4, Exercise 1 of Horowitz's
 * Data Structures.*/


#include <stdio.h>
#include <conio.h> // getch()
#define MAX_TERMS 101 // Size of the array storing the sparse matrix
#define MAX_COLUMN 10
#define MAX_ROW 10

typedef struct {
    int col;
    int row;
    int value;
} term;

term sparse_matrix[MAX_TERMS];

void read_matrix();
int insert_sort(int input_num);
void print_matrix();
int search();

int main() {
    read_matrix();
    print_matrix();
    search();
    return 0;
}

void read_matrix() {
    int input_counter;
    char yorn;
    printf("Enter the size of the sparse matrix (rows, columns): ");
    scanf("%d %d", &sparse_matrix[0].row, &sparse_matrix[0].col);
    printf("Enter the positions and values of the sparse matrix.\n");
    printf("Values will be added if the row and column are the same.\n");
    printf("If negative values are entered for row or column, the value will be ignored.\n\n");

    for (input_counter = 1; input_counter < MAX_TERMS; ++input_counter) {
        printf("Row Column Value: ");
        scanf("%d %d %d", &sparse_matrix[input_counter].row,
                            &sparse_matrix[input_counter].col, 
                            &sparse_matrix[input_counter].value);
        getchar(); // Clearing the enter value
        
        if (sparse_matrix[input_counter].row < 0 ||
            sparse_matrix[input_counter].col < 0 ||
            sparse_matrix[input_counter].row >= sparse_matrix[0].row ||
            sparse_matrix[input_counter].col >= sparse_matrix[0].col) {
            puts("Invalid input. Please try again.");
            --input_counter; // Re-prompt for input
            continue;
        }
        
        if (input_counter > 1)
            input_counter += insert_sort(input_counter);

        printf("Continue? (y or n): ");
        yorn = getchar();
        puts("");
        if (yorn == 'Y' || yorn == 'y')
            continue;
        else
            break;
    }
    sparse_matrix[0].value = input_counter;
    
    for (input_counter = 0; input_counter < sparse_matrix[0].value; ++input_counter)
        printf("%d %d %d\n", sparse_matrix[input_counter].row,
                             sparse_matrix[input_counter].col,
                             sparse_matrix[input_counter].value);
}

int insert_sort(int input_num) {
    int array_counter, insert_counter;
    term temp;
    
    for (array_counter = 1; array_counter < input_num; ++array_counter) {
        if (sparse_matrix[array_counter].row == sparse_matrix[input_num].row) {
            if (sparse_matrix[array_counter].col == sparse_matrix[input_num].col) {
                sparse_matrix[array_counter].value += sparse_matrix[input_num].value;
                return -1;
            } else if (sparse_matrix[array_counter].col > sparse_matrix[input_num].col)
                break;
        } else if (sparse_matrix[array_counter].row > sparse_matrix[input_num].row)
            break;
    }

    temp.row = sparse_matrix[input_num].row;
    temp.col = sparse_matrix[input_num].col;
    temp.value = sparse_matrix[input_num].value;
    
    for (insert_counter = input_num; insert_counter > array_counter; --insert_counter) {
        sparse_matrix[insert_counter].row = sparse_matrix[insert_counter - 1].row;
        sparse_matrix[insert_counter].col = sparse_matrix[insert_counter - 1].col;
        sparse_matrix[insert_counter].value = sparse_matrix[insert_counter - 1].value;
    }
    
    sparse_matrix[insert_counter].row = temp.row;
    sparse_matrix[insert_counter].col = temp.col;
    sparse_matrix[insert_counter].value = temp.value;
    
    return 0;
}

void print_matrix() {
    int mat_column, mat_row, sparse_array_num = 1;
    
    for (mat_row = 0; mat_row < MAX_ROW && mat_row < sparse_matrix[0].row; ++mat_row) {
        for (mat_column = 0; mat_column < MAX_COLUMN && mat_column < sparse_matrix[0].col; ++mat_column) {
            if (sparse_matrix[sparse_array_num].row == mat_row &&
                sparse_matrix[sparse_array_num].col == mat_column) {
                printf("%d\t", sparse_matrix[sparse_array_num].value);
                ++sparse_array_num;
            } else
                printf("0\t");
        }
        puts("");
    }
}

int search() {
    int array_counter, search_col, search_row;
    printf("Enter the row and column values for the search: ");
    scanf("%d %d", &search_row, &search_col);
    
    for (array_counter = 1; search_row >= sparse_matrix[array_counter].row &&
         array_counter <= sparse_matrix[0].value; ++array_counter) {
        if (sparse_matrix[array_counter].row == search_row &&
            sparse_matrix[array_counter].col == search_col) {
            printf("The value at the searched matrix is %d.\n", sparse_matrix[array_counter].value);
            return 1;
        }
    }
    printf("The value is not found in the searched matrix.\n");
    return 0;
}
