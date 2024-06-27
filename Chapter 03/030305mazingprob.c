/**Solutions to Chapter 3, Section 3, Exercise 5 of Horowitz's Data
 * Structures in C.
 */

#include <stdio.h>
#define NUM_ROWS 5
#define NUM_COLS 3
#define BOUNDARY_COLS 5
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct{
    short int row;
    short int col;
    short int dir;
} element;

element stack[MAX_STACK_SIZE];

typedef struct {
    short int vert;
    short int horiz;
} offsets;

offsets move[9]; //Array of moves for each direction

static short int maze[][BOUNDARY_COLS] = {{1,1,1,1,1}, //top boundary
                                          {1,0,0,0,1},
                                          {1,1,1,0,1},
                                          {1,0,0,0,1},
                                          {1,0,1,1,1},
                                          {1,0,0,0,1},
                                          {1,1,1,1,1}}; //bottom boundary

short int mark[][BOUNDARY_COLS] = {{0,0,0,0,0},
                                   {0,0,0,0,0},
                                   {0,0,0,0,0},
                                   {0,0,0,0,0},
                                   {0,0,0,0,0},
                                   {0,0,0,0,0},
                                   {0,0,0,0,0}};

int top;
void initialMove();
void add(int *top, element item);
element deleteFromStack();
void stackFull();
void stackEmpty();
void path();
void printRecord(int, int, int);
void printMaze();

void initialMove(){
/* initial the table for the next row and column moves */
  //move[0].vert = 0; move[0].horiz = 0;      /*do nothing*/
    move[1].vert = -1;  move[1].horiz =  0;   /*  N */
    move[2].vert = -1;  move[2].horiz =  1;   /* NE */
    move[3].vert =  0;  move[3].horiz =  1;   /*  E */
    move[4].vert =  1;  move[4].horiz =  1;   /* SE */
    move[5].vert =  1;  move[5].horiz =  0;   /*  S */
    move[6].vert =  1;  move[6].horiz =  -1;   /* SW */
    move[7].vert =  0;  move[7].horiz = -1;   /*  W */
    move[8].vert = -1;  move[8].horiz = -1;   /* NW */
}

void printMaze(){
    int i, j;
    printf("Your maze, with the boundaries is: \n\n");
    for (i = 0; i <= NUM_ROWS+1; i++) {
        for(j = 0; j <= NUM_COLS+1; j++)
            printf("%3d",maze[i][j]);
        printf("\n");
    }
    printf("\n");
}

void stackFull(){
    printf("The stack is full.  No item added \n");
}

void stackEmpty(){
    printf("The stack is empty.  No item deleted \n");
}


/* add an item to the global stack
top (also global) is the current top of the stack,
MAX_STACK_SIZE is the maximum size */
void add(int* top, element item){
    if (*top == MAX_STACK_SIZE) stackFull();
    else stack[++(*top)] = item;
}

/* remove top element from the stack and put it in item */
element deleteFromStack(){
    if (top < 0) stackEmpty();
    else return stack[top--];
}

/* print out the row, column, and the direction, the direction
   is printed out with its numeric equivvalent */
void printRecord(int row, int col, int dir){
    printf("%3d%3d", row, col);
    switch (dir - 1) {
        case 1: printf("    N");
                break;
        case 2: printf("    NE");
	        break;
        case 3: printf("    E ");
	        break;
        case 4: printf("    SE");
	        break;
        case 5: printf("    S ");
	        break;
        case 6: printf("    SW");
	        break;
        case 7: printf("    W ");
	        break;
        case 8: printf("    NW");
	        break;
    }
    printf("\n");
}

void path(void){
    int i, row, col, next_row, next_col, dir, found = FALSE;
    element position;
    mark[1][1] = 1;
    /*Place the starting position, maze[1][1] onto the stack*/
    /*Starting direction is 2*/
    top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
    while (top > -1 && !found){
        position = deleteFromStack(&top);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found){
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;
            if (next_row == NUM_ROWS && next_col == NUM_COLS)
                found = TRUE;
            else if (!maze[next_row][next_col] && !mark[next_row][next_col]){
                /*Current position has not been checked, so place it on the
                 *stack and continue*/
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                add(&top, position);
                row = next_row;
                col = next_col;
                dir = 0;
            } else ++dir;
        }
    }
    if (found){
        printf("The path is: \n");
        printf("row col \n");
        for (i = 0; i <= top; i++)
           printRecord(stack[i].row, stack[i].col, stack[i].dir);
        printf("%3d%3d\n", row, col);
        printf("%3d%3d\n", NUM_ROWS, NUM_COLS);
    } else printf("The maze does not have a path.\n");
}

int main(){
    initialMove();
    printMaze();
    path();
    return 0;
}

/**Algorithm of the path() function
 * Initialize the stack to maze's entrance coordinates and direction
 * to the north
 * while (stack is not empty)
 *    move to the position at the top of stack
 *    <row, col, dir> = delete from top of stack
 *    while (there are more moves from current position)
 *        <next_row, next_col> = coordinates of the next move
 *        dir = direction of move;
 *        if ((next_row == EXIT_ROW) && (next_col = EXIT_COL))
 *            success;
 *        if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0)
 *            //legal move and have not been there
 *            mark[next_row][next_col] = 1;
 *            //save current position and direction
 *            add <row, col, dir> to the top of the stack
 *            row = next_row;
 *            col = next_col;
 *            dir = north;
 * No path found
 */
