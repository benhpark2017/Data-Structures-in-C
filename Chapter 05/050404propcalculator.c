#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 100 // Maximum stack size
#define MAX_EXPR_SIZE 100 // Maximum expression size

// Boolean and logical operations
typedef enum {false, true, and, or, rparen, not, lparen, eos} logical;

typedef struct _Node* nodePtr; // Node pointer
typedef struct _Node { // Node structure
    nodePtr left_child; // Left child node
    logical data; // Data
    short value; // Result value when evaluating the proposition
    nodePtr right_child; // Right child node
} Node;

// Global Variables
nodePtr expr[MAX_EXPR_SIZE]; // Array to store expressions
nodePtr stack[MAX_STACK_SIZE]; // Stack for expressions
nodePtr expr_post[MAX_EXPR_SIZE] = {0,}; // Array to store expressions in postfix notation
nodePtr root = NULL; // Root pointer of the proposition
// in-stack precedence
const int isp[] = { 0,0,2,3,4,5,0,0 };
// incoming precedence
const int icp[] = { 0,0,2,3,4,5,6,0 };

/************************************************************************
* Function Prototype Declaration.
*************************************************************************/
// Stack push
void addToStack(int* top , nodePtr item );
nodePtr deleteFromStack(int* top); // Stack pop
// Print operators in postfix notation
nodePtr print_token(logical token);
// Get the priority of a token
logical get_token(nodePtr expr[], nodePtr* symbol , int* n );
void convert_to_nodePtr(char* str); // Convert a string to a Node pointer
void postfix(void); // Convert the expression to postfix notation
void convert_to_tree(void); // Convert to a tree
void post_order_eval(nodePtr node); // Evaluate the tree in post-order and store the result in node

//////////////////////////////////////////////////////////////////////////
// Main function
int main()
{
    char str[MAX_EXPR_SIZE] = {0,}; // String containing the expression
    int i = 0; // Temporary index variable
    printf("----------------------------------\n");
    printf("| Propositional calculus |\n");
    printf("----------------------------------\n\n");
    printf("T for True, F for False, U for or, ^ for and, - for not.\n");
    printf("Please enter a proposition (e.g. \"(T^F)^-F(ENTER)\" )\nInput : ");
    scanf("%s", str); // Input the expression
    convert_to_nodePtr(str);

    postfix(); // Convert to postfix notation
    convert_to_tree(); // Convert to a tree
    post_order_eval(root); // Evaluate in post-order
    
    if (root->value == 1) printf("Result: T\n"); // Print the result
    else if (root->value == 0) printf("Result: F\n"); 
    
    // Free malloc allocations
    for( i = 0 ; i < MAX_EXPR_SIZE ; i++ )
        if ( expr[i] ) free(expr[i]) , expr[i] = NULL ;
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// Convert string to Node pointer array
void convert_to_nodePtr(char* str ) {
    int i = 0; // Temporary index variable
    // Until reaching the end of the string
    while(*str) {
        // Insert a node (allocate memory)
        expr[i] = (nodePtr)malloc(sizeof(Node));
        // Assign data value according to the character
        switch( *str++ ) {
            case 'T': expr[i]->data = true; break; //changed from 1 to T
            case 'F': expr[i]->data = false; break; //changed from 0 to F
            case '^': expr[i]->data = and; break;
            case 'u':
            case 'U': expr[i]->data = or; break;
            case '-': expr[i]->data = not; break;
            case '(': expr[i]->data = lparen; break;
            case ')': expr[i]->data = rparen; break;
            // Error handling for other characters
            default: printf("Invalid input.\n"); exit(1);
        }
        // Initialize value, child nodes of each node
        expr[i]->value = 0 ;
        expr[i]->left_child = expr[i]->right_child = NULL;
        i++; // Next index
    }
    // When reaching the end of the string
    // Mark the end of the expression converted to nodes as eos.
    expr[i] = (nodePtr)malloc(sizeof(Node));
    expr[i]->data = eos;
    expr[i]->value = 0 ;
    expr[i]->left_child = expr[i]->right_child = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Evaluate the proposition represented by the tree in post-order.
void post_order_eval(nodePtr node) {
    if ( node ) { // If not NULL
        // Evaluate the left subtree first
        post_order_eval( node->left_child );
        // Evaluate the right subtree
        post_order_eval( node->right_child );
        // If the node's data type is
        switch( node->data ) {
            case not: // If it's a logical negation
                // Store the complement of the right child's value in the current node's value
                node->value = !node->right_child->value;
                break;
            case and: // If it's an AND operation
                // Store the logical AND of the values of the right and left children in the current node's value
                node->value =
                    node->right_child->value && node->left_child->value;
                break;
            case or: // If it's an OR operation
                // Store the logical OR of the values of the right and left children in the current node's value
                node->value =
                    node->right_child->value || node->left_child->value;
                break;
            case true: // If it's true
                // Set the current node's value to TRUE
                node->value = TRUE;
                break;
            case false: // If it's false
                // Set the current node's value to FALSE
                node->value = FALSE;
                break;
            default:
                break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// Convert the expression to postfix notation
void postfix(void) {
    nodePtr symbol; // Current node to receive the token value
    nodePtr* str = expr_post; // Pointer to remember where it was saved
    logical token; // Variable to receive the token
    int n = 0 , top = 0; // Index of the string, stack top
    // The first item in the stack is eos
    stack[0] = (nodePtr)malloc(sizeof(Node));
    (stack[0])->data = eos;
    (stack[0])->left_child = (stack[0])->right_child =NULL;
    (stack[0])->value = 0;
    // Reference a book for the algorithm of converting infix to postfix
    // Repeat until the token is eos, meaning the end of the string
    for (token = get_token(expr, &symbol , &n); token != eos ;
         token = get_token(expr, &symbol , &n) ) {
        if ( token == true || token == false ) // If it's an operand, save it
            *str++ = symbol;
        else if (token == rparen ) { // If it's a closing parenthesis
            // While the top of the stack is not a left parenthesis
            while( stack[top]->data != lparen )
                *str++ = deleteFromStack(&top); // Output the contents of the stack in order
            deleteFromStack(&top); // Discard the top of the stack, i.e., the left parenthesis
        } else { // If it's not a closing parenthesis
            // Check the operator precedence
            // While the incoming token has higher or equal precedence than the one in the stack
            while ( isp[(stack[top])->data] > icp[token] )
                *str++ = deleteFromStack(&top); // Output the stack contents
            addToStack( &top , symbol ); // Insert the token to be pushed
        }
    }
    // Save the remaining contents of the stack to the string
    while (top > -1)
        *str++ = deleteFromStack(&top);
}

// Get the current node's token value
logical get_token(nodePtr* list , nodePtr* symbol , int* n) {
    *symbol = list[(*n)++];
    switch( (*symbol)->data) {
        case true : case false : case and: case or: case not: case lparen: case rparen:
            return (*symbol)->data;
        default: return eos;
    }
}

// Convert the expression in postfix notation to a tree
void convert_to_tree(void) {
    logical token; // Token
    nodePtr symbol; // Character
    nodePtr op1, op2; // Operand 1, 2
    int n = 0; // Index of the string
    int top = -1; // Stack top
    // Get the token
    token = get_token( expr_post , &symbol , & n );
    while (token != eos) {
        // If token is an operand or the root, push it onto the stack
        // (From the perspective of the ancestor, the root of the subtree is an operand.)
        if (token == true || token == false || symbol == root )
            addToStack( &top , symbol);
        // If the operator is a logical negation, the operand goes to the left
        else {
            if ( token == not ) { // Get only one operand
                op1 = deleteFromStack(&top);
                // Attach the operand node to the left of the current node ('not' node)
                symbol->right_child = op1;
            } else {
                // Retrieve the operands stored in the stack.
                // For example, in the expression "1 ^ - 0", in the array of nodes, it is "10^".
                // The top of the stack and the operand just below it.
                // The stack stores 1 and 0 in reverse order.
                // Therefore, they need to be retrieved in reverse order.
                op2 = deleteFromStack(&top);
                op1 = deleteFromStack(&top);
                symbol->left_child = op1; // Operand 1 is on the left
                symbol->right_child = op2; // Operand 2 is on the right
            }
            root = symbol; // Set the node with the operator in the middle as the root
            addToStack(&top , root ); // Store the root in the stack
            // (From the perspective of the ancestor, the root of the subtree is an operand.)
        }
        // After the operation, get the token value of the corresponding character
        token = get_token( expr_post, &symbol , &n );
    }//end while
    // When reaching the end, the stack contains the root of the expression.
    if (top == 0) root = stack[top];
}

// Adds an item to the stack.
void addToStack(int* top , nodePtr item ) {
    if ( (*top) == MAX_STACK_SIZE ) {
        fprintf(stderr, "The stack is full.\n" );
        exit(1);
    }
    stack[++(*top)] = item;
}

// Deletes the top from the stack.
nodePtr deleteFromStack(int* top) {
    if ( (*top) == -1 ) {
        fprintf(stderr, "The stack is empty.\n" );
        exit(1);
    }
    return stack[(*top)--];
}

