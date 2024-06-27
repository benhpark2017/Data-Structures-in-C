/**Solutions to Chapter 3, Section 1, Exercise 1 of Horowitz's
 * Fundamentals of Data Structures in C.*/

#include <stdio.h>
#define MAX_STACK_SIZE 100

typedef struct {
    int key;
    /*insert other members*/
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void addToStack(element item);
element deleteFromStack();
int peekAtTop();
int isEmpty();
int isFull();
void stackFull();
element stackEmpty();

int main() {
    int choice;
    element item;

    printf("1. Insert stack\n"
           "2. Delete stack\n"
           "3. Look at Stack\n"
           "0. Quit: \n");
    scanf("%d", &choice);

    while (choice > 0) {
        switch (choice) {
            case 1:
                printf("Insert in stack:");
                scanf("%d", &item.key);
                addToStack(item);
                break;
            case 2:
                item = deleteFromStack();
                if (top >= 0) printf("%d was deleted from the stack.\n", item.key);
                break;
            case 3:
                printf("The top-most element of the stack is %d\n", peekAtTop());
                break;
        }
        printf("1. Insert stack\n"
               "2. Delete stack\n"
               "3. Look at Stack\n"
               "0. Quit: \n");
        scanf("%d", &choice); // Update the choice variable
    }

    return 0;
}

void addToStack(element item) {
    /* Add an item to the global stack */
    if (top >= MAX_STACK_SIZE - 1) {
        stackFull();
        return;
    }
    stack[++top] = item;
}

element deleteFromStack() {
    /* return the top element from the stack */
    if (top == -1) return stackEmpty(); /* returns an error key */
    return stack[top--];
}

int peekAtTop() {
    if (top == -1) return -1; // Return some error value when the stack is empty
    return stack[top].key;
}

int isEmpty() {
    return (top == -1);
}

int isFull() {
    return (top == MAX_STACK_SIZE - 1);
}

void stackFull() {
    if (isFull()) printf("The stack is full. No item added.\n");
}

element stackEmpty() {
    if (isEmpty()) {
        printf("The stack is empty. No item deleted.\n");
        element errorItem = {-1};
        return errorItem; // Return some error value
    }
}
