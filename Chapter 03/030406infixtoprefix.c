/**Solutions to Chapter 3, Section 4, Exercises 6 and 11 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 100 // Maximum stack size
#define MAX_EXPR_SIZE 100 // Maximum expression size

typedef enum {
    LPAREN, RPAREN, PLUS, MINUS, TIMES, DIVIDE, MOD,
    LOGICAL_AND, LOGICAL_OR, LEFT_SHIFT, RIGHT_SHIFT,
    EQUAL, NOT_EQUAL, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL,
    EOS, OPERAND
} PRECEDENCE; // Precedence

PRECEDENCE stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char expr_prefix[MAX_EXPR_SIZE];

// In-stack precedence
const int isp[] = {19, 0, 12, 12, 13, 13, 13, 5, 4, 11, 11, 9, 9, 10, 10, 10, 10, 0};
// Incoming precedence
const int icp[] = {19, 20, 12, 12, 13, 13, 13, 5, 4, 11, 11, 9, 9, 10, 10, 10, 10, 0};

// Function Prototype Declarations
PRECEDENCE get_infix_token(char *symbol, int *n); // Returns the precedence of a token in infix notation
PRECEDENCE get_prefix_token(char *symbol, int *n); // Returns the precedence of a token in prefix notation
void print_token(PRECEDENCE token, char **str); // Prints the token as a string
void prefix(void); // Converts infix expression to prefix expression
int eval(void); // Evaluates the prefix expression
void stack_push(int *top, int item); // Stack push operation
int stack_pop(int *top); // Stack pop operation
void stack_full(); // Displays message when stack is full
void stack_empty(); // Displays message when stack is empty

// Main function
int main(void) {
    printf("---------------------------------\n");
    printf("| Converting infix to prefix |\n");
    printf("---------------------------------\n\n");
    printf("Enter the expression, e.g.: \n3*9/2+3\nInput: ");
    scanf("%s", expr); // Input expression
    prefix(); // Convert to prefix
    printf("\n\nResult: %d \n\n", eval()); // Evaluate prefix expression
    return 0;
}

// Function to get infix tokens from input expression
PRECEDENCE get_infix_token(char *symbol, int *n) {
    if (*n < 0) return EOS;
    *symbol = expr[(*n)--];
    switch (*symbol) {
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return DIVIDE;
        case '*': return TIMES;
        case '%': return MOD;
        case '\0': return EOS;
        case '<':
            if (expr[*n] == '<') {
                --*(n);
                return LEFT_SHIFT;
            }
            return LESS;
        case '>':
            if (expr[*n] == '>') {
                --*(n);
                return RIGHT_SHIFT;
            }
            return GREATER;
        case '&':
            if (expr[*n] == '&') {
                --*(n);
                return LOGICAL_AND;
            }
            return EOS;
        case '|':
            if (expr[*n] == '|') {
                --*(n);
                return LOGICAL_OR;
            }
            return EOS;
        case '=':
            if (expr[*n] == '=') {
                --*(n);
                return EQUAL;
            } else if (expr[*n] == '<') {
                --*(n);
                return LESS_EQUAL;
            } else if (expr[*n] == '>') {
                --*(n);
                return GREATER_EQUAL;
            } else if (expr[*n] == '!') {
                --*(n);
                return NOT_EQUAL;
            }
            return EOS;
        default: return OPERAND;
    }
}

// Function to get prefix tokens from input expression
PRECEDENCE get_prefix_token(char *symbol, int *n) {
    if (*n >= MAX_EXPR_SIZE) return EOS;
    switch (*symbol = expr[(*n)++]) {
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return DIVIDE;
        case '*': return TIMES;
        case '%': return MOD;
        case '\0': return EOS;
        case '<':
            if (expr[*n] == '<') {
                ++*(n);
                return LEFT_SHIFT;
            } else if (expr[*n] == '=') {
                ++*(n);
                return LESS_EQUAL;
            }
            return LESS;
        case '>':
            if (expr[*n] == '>') {
                ++*(n);
                return RIGHT_SHIFT;
            } else if (expr[*n] == '=') {
                ++*(n);
                return GREATER_EQUAL;
            }
            return GREATER;
        case '&':
            if (expr[*n] == '&') {
                ++*(n);
                return LOGICAL_AND;
            }
            return EOS;
        case '|':
            if (expr[*n] == '|') {
                ++*(n);
                return LOGICAL_OR;
            }
            return EOS;
        case '=':
            if (expr[*n] == '=') {
                ++*(n);
                return EQUAL;
            }
            return EOS;
        case '!':
            if (expr[*n] == '=') {
                ++*(n);
                return NOT_EQUAL;
            }
            return EOS;
        default: return OPERAND;
    }
}

// Function to convert infix expression to prefix expression
void prefix(void) {
    PRECEDENCE token;
    int n = strlen(expr) - 1;
    int top = 0;
    char symbol;
    char expr_prefix[MAX_EXPR_SIZE] = {0};
    char *str = expr_prefix;

    stack[0] = EOS;

    for (token = get_infix_token(&symbol, &n); token != EOS; token = get_infix_token(&symbol, &n)) {
        if (token == OPERAND)
            *str++ = symbol;
        else if (token == LPAREN) {
            while (stack[top] != RPAREN)
                print_token(stack_pop(&top), &str);
            stack_pop(&top);
        } else {
            while (isp[stack[top]] > icp[token])
                print_token(stack_pop(&top), &str);
            stack_push(&top, token);
        }
    }

    while ((token = stack_pop(&top)) != EOS && top > -1)
        print_token(token, &str);

    memset(expr, 0, sizeof(char) * MAX_EXPR_SIZE);
    printf("Prefix expression: ");
    for (top = MAX_EXPR_SIZE - 1; top >= 0; top--) {
        if (expr_prefix[top]) {
            printf("%c", expr_prefix[top]);
            expr[top] = expr_prefix[top];
        }
    }
}

// Function to print tokens as strings
void print_token(PRECEDENCE token, char **str) {
    switch (token) {
        case LPAREN: *(*str)++ = '('; return;
        case RPAREN: *(*str)++ = ')'; return;
        case PLUS: *(*str)++ = '+'; return;
        case MINUS: *(*str)++ = '-'; return;
        case TIMES: *(*str)++ = '*'; return;
        case DIVIDE: *(*str)++ = '/'; return;
        case MOD: *(*str)++ = '%'; return;
        case LOGICAL_AND: *(*str)++ = '&'; *(*str)++ = '&'; return;
        case LOGICAL_OR: *(*str)++ = '|'; *(*str)++ = '|'; return;
        case LEFT_SHIFT: *(*str)++ = '<'; *(*str)++ = '<'; return;
        case RIGHT_SHIFT: *(*str)++ = '>'; *(*str)++ = '>'; return;
        case EQUAL: *(*str)++ = '='; *(*str)++ = '='; return;
        case NOT_EQUAL: *(*str)++ = '!'; *(*str)++ = '='; return;
        case LESS: *(*str)++ = '<'; return;
        case GREATER: *(*str)++ = '>'; return;
        case LESS_EQUAL: *(*str)++ = '<'; *(*str)++ = '='; return;
        case GREATER_EQUAL: *(*str)++ = '>'; *(*str)++ = '='; return;
    }
}

// Function to evaluate the prefix expression
int eval(void) {
    PRECEDENCE token;
    char symbol;
    int op1, op2;
    int n = 0;
    int top = -1;

    token = get_prefix_token(&symbol, &n);

    while (token != EOS) {
        if (token == OPERAND)
            stack_push(&top, symbol - '0');
        else {
            op1 = stack_pop(&top);
            op2 = stack_pop(&top);
            switch (token) {
                case PLUS: stack_push(&top, op1 + op2); break;
                case MINUS: stack_push(&top, op1 - op2); break;
                case TIMES: stack_push(&top, op1 * op2); break;
                case DIVIDE: stack_push(&top, op1 / op2); break;
                case MOD: stack_push(&top, op1 % op2); break;
                case LOGICAL_AND: stack_push(&top, op1 && op2); break;
                case LOGICAL_OR: stack_push(&top, op1 || op2); break;
                case LEFT_SHIFT: stack_push(&top, op1 << op2); break;
                case RIGHT_SHIFT: stack_push(&top, op1 >> op2); break;
                case EQUAL: stack_push(&top, op1 == op2); break;
                case NOT_EQUAL: stack_push(&top, op1 != op2); break;
                case LESS: stack_push(&top, op1 < op2); break;
                case GREATER: stack_push(&top, op1 > op2); break;
                case LESS_EQUAL: stack_push(&top, op1 <= op2); break;
                case GREATER_EQUAL: stack_push(&top, op1 >= op2); break;
                default: break;
            }
        }
        token = get_prefix_token(&symbol, &n);
    }
    return stack[top];
}

// Stack push operation
void stack_push(int *top, int item) {
    if ((*top) >= MAX_STACK_SIZE - 1) {
        stack_full();
        return;
    }
    ((int *)stack)[++(*top)] = item;
}

// Stack pop operation
int stack_pop(int *top) {
    if ((*top) == (-1))
        stack_empty();
    return stack[(*top)--];
}

// Display message when stack is full
void stack_full() {
    fprintf(stderr, "The stack is full. \n");
}

// Display message when stack is empty
void stack_empty() {
    fprintf(stderr, "The stack is empty. \n");
}

