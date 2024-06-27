/**A recursive solution to Chapter 5, Section 4, Exercise 4 of Horowitz's
 * Fundamentals of Data Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_SIZE 100
#define TRUE 1
#define FALSE 0

typedef enum {not, and, or, true, false} logical;

typedef struct treeNode *treePtr;

typedef struct treeNode {
    treePtr left_child;
    logical data;
    short int value;
    treePtr right_child;
} node;

/*Function prototypes*/
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

treePtr copy(treePtr original) {
    if (original == NULL) return NULL;
    treePtr temp = (treePtr)malloc(sizeof(node));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    temp->data = original->data;
    temp->value = original->value;
    temp->left_child = copy(original->left_child);
    temp->right_child = copy(original->right_child);
    return temp;
}

/**Recursive function that takes in a binary tree and swaps every left
 * and right children of every parent node
 */
void swapTree(treePtr root) {
    if (root == NULL) {
        return;
    }

    // Swap left and right children
    treePtr temp = root->left_child;
    root->left_child = root->right_child;
    root->right_child = temp;

    // Recursively swap the children of the left and right subtrees
    swapTree(root->left_child);
    swapTree(root->right_child);
}

int equal(treePtr first, treePtr second) {
    return ((!first && !second) || (first && second &&
             (first->data == second->data) &&
             equal(first->left_child, second->left_child) &&
             equal(first->right_child, second->right_child)));
}

void postOrderEval(treePtr node) {
    if (node) {
        postOrderEval(node->left_child);
        postOrderEval(node->right_child);
        switch (node->data){
            case not:   node->value = !node->right_child->value;
                        break;
            case and:   node->value = node->right_child->value
                                      && node->left_child->value;
                        break;
            case or:    node->value = node->right_child->value
                                      || node->left_child->value;
                        break;
            case true:  node->value = TRUE; break;
            case false: node->value = FALSE; break;
        }//end switch
    }//end if
}

treePtr createTreeFromExpression(const char *expression, int *index) {

    treePtr newNode = (treePtr)malloc(sizeof(node));

    switch (expression[*index]) {
        case 'N':
            newNode->data = not;
            break;
        case 'A':
            newNode->data = and;
            break;
        case 'O':
            newNode->data = or;
            break;
        case 'T':
            newNode->data = true;
            break;
        case 'F':
            newNode->data = false;
            break;
        default:
            // Handle invalid characters in the expression
            free(newNode);
            return NULL;
    }

    (*index)++;  // Move to the next character

    newNode->left_child = createTreeFromExpression(expression, index);
    newNode->right_child = createTreeFromExpression(expression, index);

    return newNode;
}


void printExpression(treePtr node) {
    if (node) {
        switch (node->data) {
            case not:  printf("N"); break;
            case and:  printf("A"); break;
            case or:  printf("O"); break;
            case true: printf("T"); break;
            case false: printf("F"); break;
        }
        printExpression(node->left_child);
        printExpression(node->right_child);
    }
}

void printPostOrder(treePtr node) {
    if (node) {
        printPostOrder(node->left_child);
        printPostOrder(node->right_child);
        switch (node->data) {
            case not:   printf("N "); break;
            case and:   printf("A "); break;
            case or:    printf("O "); break;
            case true:  printf("T "); break;
            case false: printf("F "); break;
        }
    }
}

int main() {

    printf("Enter a propositional expression without space or newline.\n");
    printf("Press ENTER when you're done. \n");
    char expression[MAX_EXPRESSION_SIZE];
    scanf("%s", expression);
    //fgets(expression, sizeof(expression), stdin);

    int index = 0;
    treePtr root = createTreeFromExpression(expression, &index);

    //Copy the tree and swap the copy
    treePtr copiedTree = copy(root);
    swapTree(copiedTree);
    treePtr swappedTree = copiedTree;

    // Print the original and swapped post-order traversals
    printf("Original post-order: ");
    printPostOrder(root);
    printf("\n");

    printf("Swapped post-order: ");
    printPostOrder(swappedTree);
    printf("\n");

    if (equal(root, swappedTree)) printf("The two trees are equal.\n");
    else printf("The two trees are different.\n");

    // Evaluate the expression
    postOrderEval(root);
    postOrderEval(swappedTree);

    // Display the result
    printf("Original tree result: %s\n", (root->value == TRUE) ? "TRUE" : "FALSE");
    printf("Swapped tree result: %s\n", (swappedTree->value == TRUE) ? "TRUE" : "FALSE");

    return 0;
}


