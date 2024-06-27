/**Solutions to Chapter 4, Section 3, Exercise 2 of Horowitz's Fundamentals of Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdbool.h>

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

// Function to check for matching parentheses
bool isMatchingParentheses(char expression[]) {
    struct Stack stack;
    initialize(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char currentChar = expression[i];

        if (currentChar == '(' || currentChar == '[' || currentChar == '{') {
            // Push opening parentheses onto the stack
            push(&stack, currentChar);
        } else if (currentChar == ')' || currentChar == ']' || currentChar == '}') {
            // Check if there's a matching opening parenthesis on the stack
            if (stack.top == -1 || !isMatchingPair(pop(&stack), currentChar)) {
                return false;
            }
        }
    }

    // Check if the stack is empty (all parentheses are matched)
    return stack.top == -1;
}

// Function to check if two parentheses form a matching pair
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

int main() {
    char input[MAX_SIZE];
    printf("Enter a nested parenthesis expression: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    if (isMatchingParentheses(input)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are not balanced.\n");
    }

    return 0;
}

