/**Solutions to Chapter 5, Section 4, Exercise 4 of Horowitz's Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_SIZE 100
#define TRUE 1
#define FALSE 0

typedef enum {not, and, or, leaf } logical;
typedef enum {false=0, true } logicalValue;

typedef struct treeNode {
    struct treeNode * left_child;
    logical data;
    logicalValue  value;
    struct treeNode * right_child;
} node;
typedef struct treeNode *treePtr;

treePtr  stack[MAX_EXPRESSION_SIZE] ;
int stack_top = -1 ;

void push(treePtr node) {
   stack_top++ ;
   stack[stack_top] = node ;
}

treePtr pop() {
  return stack[stack_top--] ;
}

short int isFull(treePtr node){
    if (node == NULL) return 1;

    // If the node is a leaf, it's full by definition
    if (node->left_child == NULL && node->right_child == NULL)
        return 1;

    // If the node has one child but not both, the tree is not full
    if ((node->left_child == NULL && node->right_child != NULL) ||
        (node->left_child != NULL && node->right_child == NULL))
        return 0;

    // Recursively check both subtrees
    return isFull(node->left_child) && isFull(node->right_child);
}

logicalValue postOrderEval(treePtr node) {
    logicalValue left, right ;
    if ( node == NULL ) return false ; // DISCARD return value !!!
    if (node) {
        left = postOrderEval(node->left_child);
        right = postOrderEval(node->right_child);
        switch (node->data){
            case not:   node->value = !node->right_child->value;
                        break;
            case and:   node->value = node->right_child->value
                                      && node->left_child->value;
                        break;
            case or:    node->value = node->right_child->value
                                      || node->left_child->value;
                        break;
            //case true:  node->value = TRUE; break;
            //case false: node->value = FALSE; break;
        }//end switch
    }//end if
    return node->value ;
}

treePtr createTreeFromExpression(const char *expression ) {
    // Skip over spaces and newline characters
    treePtr leftN, rightN, newNode  ;
    int i = 0 ;
  for ( ; expression[i] ; ++i )
  {

    newNode = (treePtr)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    char currentChar = expression[i];
    switch (currentChar) {
        case 'T':
            newNode->data = leaf ;
	    newNode->value = true ;
            newNode->left_child = NULL;
            newNode->right_child = NULL;
	    push(newNode) ;
            break;
        case 'F':
            newNode->data = leaf ;
	    newNode->value = false;
            newNode->left_child = NULL;
            newNode->right_child = NULL;
	    push(newNode) ;
            break;
        case 'N':
	    //leftN = NULL ;
	    rightN = pop() ;
            newNode->data = not;
            newNode->left_child = NULL;
            newNode->right_child = rightN ;
            newNode->value = ! newNode->right_child->value ;
	    push(newNode) ;
            break;
        case 'A':
	    rightN = pop() ;
	    leftN = pop() ;
            newNode->data = and;
            newNode->left_child = leftN ;
            newNode->right_child = rightN ;
            newNode->value = newNode->left_child->value && newNode->right_child->value ;
	    push(newNode) ;
            break;
        case 'O':
	    rightN = pop() ;
	    leftN = pop() ;
            newNode->data = or;
            newNode->left_child = leftN ;
            newNode->right_child = rightN ;
            newNode->value = newNode->left_child->value || newNode->right_child->value ;
	    push(newNode) ;
            break;
        default:
            fprintf(stderr, "Unexpected character '%c' in expression.\n", currentChar);
            exit(1);
    }
  } //for
  return newNode;
}

void printExpression(treePtr node) {
     if ( node == NULL ) return ;
     printExpression(node->left_child);
     printExpression(node->right_child);
     switch (node->data) {
            case not:  printf("N"); break;
            case and:  printf("A"); break;
            case or:  printf("O"); break;
            case leaf:  if ( node->value == true ) printf("T"); else if ( node->value == false ) printf("F"); break;
            //case true: printf("T"); break;
            //case false: printf("F"); break;
     } // switch
}

int main() {

    printf("Enter a propositional expression: ");
    char expression[MAX_EXPRESSION_SIZE];
    logicalValue value ;
    //fgets(expression, sizeof(expression), stdin);
    scanf("%s", expression) ;

    int index = 0;
    treePtr root = createTreeFromExpression(expression );
    printf("Original tree result: %s\n", (root->value == true) ? "TRUE" : "FALSE");

    // Print the original and swapped post-order traversals
    printf("Original post-order: ");
    printExpression(root);
    printf("\n");
    printf("\n");

    // Evaluate the expression
    value = postOrderEval(root);

    // Display the result
    printf("Original tree result: %s\n", (root->value == TRUE) ? "TRUE" : "FALSE");

    return 0;
}
