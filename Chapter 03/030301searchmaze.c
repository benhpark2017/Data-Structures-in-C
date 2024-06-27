/**Solutions to Chapter 3, Section 3, Exercise 1 of Fundamentals of
 * Data Structures in C by Horowitz, Sahni, and Anderson-Freed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct{
    short row;
    short col;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

//Function that initiailizes stack
void init_stack(StackType* s){
    s->top = -1;
}

//Determines if the stack is empty
int is_empty(StackType* s){
    return (s->top == -1);
}

//Determines if the stack is full
int is_full(StackType* s){
    return (s->top == (MAX_STACK_SIZE - 1));
}

//Insert an element into stack
void push(StackType* s, element item){
    if (is_full(s)){
        fprintf(stderr, "Error: The stack is full.\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

//Delete element from stack
element pop(StackType* s){
    if (is_empty(s)){
        fprintf(stderr, "Error: The stack is empty.\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = 
{
    { '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' },
};

//Inserts an element into the stack s
void push_loc(StackType* s, int row, int col){
    if (row < 0 || col < 0) return;
    if (maze[row][col] != '1' && maze[row][col] != '.') {
        element tmp;
        tmp.row = row;
        tmp.col = col;
        push(s, tmp);
    }
}

//Prints maze on the output screen
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]){
    printf("\n");
    for (int row = 0; row < MAZE_SIZE; row++) {
        for (int col = 0; col < MAZE_SIZE; col++) {
            printf("%c", maze[row][col]);
        }
    printf("\n");
    }
}

int main(void){
    int r, c;
    StackType s;

    init_stack(&s);
    here = entry;
    while (maze[here.row][here.col] != 'x') {
        r = here.row;
        c = here.col;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
	if (is_empty(&s)) {
            printf("Failed to find a path in the maze.\n");
            return 0;
        } else here = pop(&s);
	maze_print(maze);
        printf("Next move: \n");
    }
    printf("Success!\n");
    return 0;
}
