/**Solutions to Chapter 4, Section 3, Exercise 1 of Horowitz's Fundamentals
 * of Data Structures in C.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to initialize the stack
void initialize(struct Stack* stack) {
    stack->top = -1;
}

// Function to push an item onto the stack
void push(struct Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

// Function to check if a string is a palindrome using a stack
bool isPalindrome(char str[]) {
    struct Stack stack;
    initialize(&stack);

    int length = strlen(str);

    // Push the first half of the string onto the stack
    for (int i = 0; i < length / 2; i++) {
        if (str[i] != ' ') {  // Skip spaces
            push(&stack, tolower(str[i]));  // Convert to lowercase before pushing
        }
    }

    // Pop and compare with the second half of the string
    for (int i = (length + 1) / 2; i < length; i++) {
        if (str[i] != ' ' && tolower(str[i]) != pop(&stack)) {  // Skip spaces and compare in lowercase
            return false;
        }
    }

    return true;
}

int main() {
    char input[MAX_SIZE];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    if (isPalindrome(input)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is not a palindrome.\n");
    }

    return 0;
}

