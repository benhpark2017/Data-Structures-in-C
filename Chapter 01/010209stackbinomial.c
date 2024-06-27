/**Solutions to Chapter 1, Section 2, Exercise 9 of Horowitz's Data Structures
 * in C.
 */

#include <stdio.h>
#define MAX_STACK_SIZE 100

typedef struct {
    int key;
    /*insert other members*/
} element;

element iterativeStack[MAX_STACK_SIZE];
element recursiveStack[MAX_STACK_SIZE];
int iterativeTop = -1;
int recursiveTop = -1;

void addToIterativeStack(element item);

void addToRecursiveStack(element item);

element deleteFromIterativeStack(); 

element deleteFromRecursiveStack();

int peekAtIterativeTop();

int peekAtRecursiveTop();

element iterativeStackEmpty();

element recursiveStackEmpty();

int iterativeStackFull(); 

int recursiveStackFull(); 
        
int iterativeBinomialCoeff(int n, int m);

int recursiveBinomialCoeff(int n, int m);

int main() {
    element item;
    int n, m;
    printf("Enter the indices for the binomial coefficient you wish to calculate.\n");
    printf("Please enter two numbers in decreasing order: \n");
    scanf("%d %d", &n, &m);
    printf("The iterative coefficient %d choose %d is %d\n", n, m, iterativeBinomialCoeff(n, m));
    printf("The recursive coefficient %d choose %d is %d\n", n, m, recursiveBinomialCoeff(n, m));
    return 0;
}

void addToIterativeStack(element item) {
    /* Add an item to the global stack */
    if (iterativeTop >= MAX_STACK_SIZE - 1) {
        iterativeStackFull();
        return;
    }
    iterativeStack[++iterativeTop] = item;
}

void addToRecursiveStack(element item) {
    /* Add an item to the recursive stack */
    if (recursiveTop >= MAX_STACK_SIZE - 1) {
        recursiveStackFull();
        return;
    }
    recursiveStack[++recursiveTop] = item;
}

element deleteFromIterativeStack() {
    /* return the top element from the stack */
    if (iterativeTop == -1) return iterativeStackEmpty(); /* returns an error key */
    return iterativeStack[iterativeTop--];
}

element deleteFromRecursiveStack() {
    /* return the top element from the stack */
    if (recursiveTop == -1) return recursiveStackEmpty(); /* returns an error key */
    return recursiveStack[recursiveTop--];
}

int peekAtIterativeTop() {
    if (iterativeTop == -1) return -1; // Return some error value when the stack is empty
    return iterativeStack[iterativeTop].key;
}

int peekAtRecursiveTop() {
    if (recursiveTop == -1) return -1; // Return some error value when the stack is empty
    return recursiveStack[recursiveTop].key;
}

element iterativeStackEmpty() {
    if (iterativeTop == -1) {
        printf("The stack is empty. No item deleted.\n");
        element errorIterativeItem = {-1};        
        return errorIterativeItem; // Return some error value
    };
}

element recursiveStackEmpty() {
    if (recursiveTop == -1) {
        printf("The stack is empty. No item deleted.\n");
        element errorRecursiveItem = {-1};        
        return errorRecursiveItem; // Return some error value
    };
}

int iterativeStackFull() {
    if (iterativeTop == MAX_STACK_SIZE - 1)
        printf("The iterative stack is full. No item added.\n");
}

int recursiveStackFull() {
    if (recursiveTop == MAX_STACK_SIZE - 1)
        printf("The recursive stack is full. No item added.\n");
}
        
int iterativeBinomialCoeff(int n, int m) {
    if (m < 0 || m > n) return 0; //invalid input, return 0
    int result = 1;
    for (int i = 1; i <= m; i++){
        result *= n - (m - i);
        result /= i;
        element currentItem;
        currentItem.key = result;  // You may need to initialize other members if present
        addToIterativeStack(currentItem);
        printf("The top of the iterative stack is %d\n", peekAtIterativeTop());
    }
    return result;
}

int recursiveBinomialCoeff(int n, int m){
    if (m < 0 || m > n) return 0; //invalid input, return 0

    int result = 1;
    if (m == 0 || m == n) return 1; //basis case

    result = recursiveBinomialCoeff(n - 1, m)
              + recursiveBinomialCoeff(n - 1, m - 1);
    element currentRecursiveItem;
    currentRecursiveItem.key = result;
    addToRecursiveStack(currentRecursiveItem);
    printf("The top of the recursive stack is %d\n", peekAtRecursiveTop());
    return result;
}
