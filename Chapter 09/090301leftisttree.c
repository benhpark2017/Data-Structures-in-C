/**Solutions to Chapter 9, Section 3, Exercise 1 of Horowitz's Data 
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
    /* Other fields */
} element;

struct Leftist {
    struct Leftist* leftChild;
    struct Leftist* rightChild;
    element data;
    int shortest;
};
typedef struct Leftist* LeftistTree;

LeftistTree stack[MAX_SIZE];
int top = 0;
int rear = 0;

void minCombine(LeftistTree *a, LeftistTree *b);
void minUnion(LeftistTree *a, LeftistTree *b);
void initializeNode(LeftistTree *b, int key);
void showTree(LeftistTree a);
void showMidTree(LeftistTree a);
void showPreTree(LeftistTree a);

int main() {
    LeftistTree a = NULL;
    LeftistTree b = NULL;
    LeftistTree c = NULL;
    
    initializeNode(&b, 2);
    minCombine(&a, &b);
    initializeNode(&b, 7);
    minCombine(&a, &b);
    initializeNode(&b, 50);
    minCombine(&a, &b);
    initializeNode(&b, 11);
    minCombine(&a, &b);
    initializeNode(&b, 80);
    minCombine(&a, &b);
    initializeNode(&b, 13);
    minCombine(&a, &b);

    printf("Tree a is: \n");
    showTree(a);
    printf("->NULL\n\n");
    
    initializeNode(&b, 5);
    minCombine(&c, &b);
    initializeNode(&b, 9);
    minCombine(&c, &b);
    initializeNode(&b, 8);
    minCombine(&c, &b);
    initializeNode(&b, 12);
    minCombine(&c, &b);
    initializeNode(&b, 10);
    minCombine(&c, &b);
    initializeNode(&b, 20);
    minCombine(&c, &b);
    initializeNode(&b, 18);
    minCombine(&c, &b);
    initializeNode(&b, 15);
    minCombine(&c, &b);
    
    printf("Tree c is: \n");
    showTree(c);
    printf("NULL\n\n");
    
    minCombine(&a, &c);
    
    printf("The new tree a is: \n");
    showTree(a);
    printf("NULL\n");
    showMidTree(a);
    printf("NULL\n");
    showPreTree(a);
    printf("NULL\n");
    
    return 0;
}

void initializeNode(LeftistTree *b, int key) {
    if (!(*b)) *b = (LeftistTree)malloc(sizeof(struct Leftist));
    (*b)->data.key = key;
    (*b)->leftChild = (*b)->rightChild = NULL;
    (*b)->shortest = 1;
}

void showTree(LeftistTree tree) {
    top = 0;
    rear = 0;
    stack[rear++] = tree;
    while (1) {
        tree = stack[top++];
        if (tree) {
            printf("%d->", tree->data.key);
            if (tree->leftChild) stack[rear++] = tree->leftChild;
            if (tree->rightChild) stack[rear++] = tree->rightChild;
        } else break;
    }
}

void showMidTree(LeftistTree a) {
    if (a) {
        printf("%d->", a->data.key);
        showMidTree(a->leftChild);
        showMidTree(a->rightChild);
    }
}

void showPreTree(LeftistTree a) {
    if (a) {
        showPreTree(a->leftChild);
        printf("%d->", a->data.key);
        showPreTree(a->rightChild);
    }
}

void minCombine(LeftistTree *a, LeftistTree *b) {
    if (!(*a)) *a = *b;
    else if (*b) minUnion(a, b);
    *b = NULL;
}

void minUnion(LeftistTree *a, LeftistTree *b) {
    LeftistTree temp;
    if ((*a)->data.key > (*b)->data.key){
        SWAP(*a, *b, temp);
    }
    
    if (!(*a)->rightChild) {
        (*a)->rightChild = *b;
    } else {
        minUnion(&(*a)->rightChild, b);
    }
    
    if (!(*a)->leftChild) {
        (*a)->leftChild = (*a)->rightChild;
        (*a)->rightChild = NULL;
    } else if ((*a)->leftChild->shortest < (*a)->rightChild->shortest) {
        SWAP((*a)->leftChild, (*a)->rightChild, temp);
    }
    
    if (!(*a)->rightChild) (*a)->shortest = 1;
    else (*a)->shortest = (*a)->rightChild->shortest + 1;
}

