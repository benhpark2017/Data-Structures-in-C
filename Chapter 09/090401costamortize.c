/**Solution to Horowitz's Data Structures, Chapter 9 Section 4 Exercise 1.
 * Let S be an initially empty stack. We wish to perform two kinds of
 * operations on S: add(x) and delete_until(x), which are defined as
 * follows:
 * a. 'add(x)' adds the element x to the top of S, taking O(1) time per
      function call.
 * b. 'delete_until(x)' deletes the elements from the top of the stack
      upto and including the first x encountered. If p elements are
      deleted, the time taken is O(p).
 * Consider any sequence of stack operations (any number of 'add(x)' and
 * 'delete_until(x)'). How can I write a C code that amortizes the cost of
 * 'add(x)' and 'delete_until(x)' operations so that the amortized cost of
 * each is O(1)? */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for the stack node
struct StackNode {
    int data;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add an element to the stack
void add(struct StackNode** top_ref, int x) {
    struct StackNode* newNode = createNode(x);
    if (!newNode) {
        return;
    }
    newNode->next = *top_ref;
    *top_ref = newNode;
}

// Function to delete elements from the stack until the first occurrence of x
void delete_until(struct StackNode** top_ref, int x) {
    struct StackNode* temp = *top_ref;
    struct StackNode* prev = NULL;
    while (temp != NULL && temp->data != x) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        *top_ref = temp->next;
        free(temp);
    }
    else {
        *top_ref = NULL;
    }
}

// Function to print the stack elements
void printStack(struct StackNode* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct StackNode* top = NULL;

    // Perform some stack operations
    add(&top, 0);
    add(&top, 5);
    add(&top, 10);
    add(&top, 15);
    add(&top, 20);
    add(&top, 25);
    add(&top, 30);
    delete_until(&top, 15);
    printStack(top);

    return 0;
}
