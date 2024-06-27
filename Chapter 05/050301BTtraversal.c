/**Solutions to Chapter 5, Section 3, numbered exercises 1, 5, 6, 7, and 8 of
 * Horowitz's Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct treeNode *treePtr;

typedef struct treeNode {
    treePtr left_child;
    int data;
    treePtr right_child;
} node;

int top1 = -1;
int top2 = -1;

treePtr stack[MAX_STACK_SIZE];
treePtr queue[MAX_QUEUE_SIZE];

void insertNode(treePtr *root, int data) {
    if (*root == NULL) {
        treePtr newNode = (treePtr)malloc(sizeof(struct treeNode));
        newNode->data = data;
        newNode->left_child = NULL;
        newNode->right_child = NULL;
        (*root) = newNode;
    } else if (data < (*root)->data) {
        insertNode(&((*root)->left_child), data);
    } else if (data >= (*root)->data) {
        insertNode(&((*root)->right_child), data);
    }
}

void addToStack(int *top, treePtr stack[], treePtr treeNode) {
    (*top)++;
    stack[*top] = treeNode;
}

treePtr deleteFromStack(int *top, treePtr stack[]) {
    treePtr currentNode = NULL;
    if (*top == -1) {
        return currentNode;
    }
    currentNode = stack[*top];
    (*top)--;
    return currentNode;
}

void addToQueue(int *rear, treePtr treeNode) {
    if (*rear == MAX_QUEUE_SIZE - 1)
        printf("Queue is full.\n");
    else {
        (*rear)++;
        queue[*rear] = treeNode;
    }
}

treePtr deleteFromQueue(int *front, int rear) {
    treePtr currentNode = NULL;
    if (*front == rear) return currentNode;
    (*front)++;
    currentNode = queue[*front];
    return currentNode;
}

void inorder(treePtr root) {
    if (root){
        inorder(root->left_child);
        printf("%d ", root->data);
        inorder(root->right_child);
    }
}

void iterativeInOrder(treePtr root) {
    if (root == NULL) return;
    int top = -1;
    treePtr currentNode = root;
    for (;;) {
        for (; currentNode; currentNode = currentNode->left_child)
            addToStack(&top, stack, currentNode);
        currentNode = deleteFromStack(&top, stack);
        if (!currentNode) break;
        printf("%d ", currentNode->data);
        currentNode = currentNode->right_child;
    }
}

void preorder(treePtr root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left_child);
        preorder(root->right_child);
    }
}

void iterativePreOrder(treePtr root) {
    if (root == NULL) return;
    int top = -1;
    while (1) {
        while (root) {
            printf("%d ", root->data);
            if (root->right_child)
                addToStack(&top, stack, root->right_child);
            root = root->left_child;
        }
        if (top == -1) break;
        root = deleteFromStack(&top, stack);
    }
}

void postorder(treePtr root) {
    if (root) {
        postorder(root->left_child);
        postorder(root->right_child);
        printf("%d ", root->data);
    }
}

void iterativePostOrder(treePtr root) {
    if (root == NULL) return;

    int top = -1;
    treePtr lastVisited = NULL;

    do {
        while (root) {
            addToStack(&top, stack, root);
            root = root->left_child;
        }

        while (!root && top != -1) {
            treePtr peekNode = stack[top];

            if (peekNode->right_child && lastVisited != peekNode->right_child) {
                root = peekNode->right_child;
            } else {
                printf("%d ", peekNode->data);
                lastVisited = deleteFromStack(&top, stack);
            }
        }
    } while (top != -1);
}

void levelOrder(treePtr root) {
    int front = 0;
    int rear = 0;
    //treePtr queue[MAX_QUEUE_SIZE]
    if (!root) return;
    addToQueue(&rear, root);
    for (;;){
        root = deleteFromQueue(&front, rear);
        if (root) {
            printf("%d ", root->data);
            if (root->left_child)
                addToQueue(&rear, root->left_child);
            if (root->right_child)
                addToQueue(&rear, root->right_child);
        } else break;
    }
}


int main() {
    treePtr root = NULL;

    insertNode(&root, 5);
    insertNode(&root, 8);
    insertNode(&root, 4);
    insertNode(&root, 2);
    insertNode(&root, 1);
    insertNode(&root, 3);
    insertNode(&root, 9);
    insertNode(&root, 6);
    insertNode(&root, 7);
    
    printf("Recursive In-order: ");
    inorder(root);
    printf("\n");
    
    printf("Iterative In-order: ");
    iterativeInOrder(root);
    printf("\n");    
    
    printf("Recursive Pre-order: ");
    preorder(root);
    printf("\n");
    
    printf("Iterative Pre-order: ");
    iterativePreOrder(root);
    printf("\n");
    
    printf("Recursive Post-order: ");
    postorder(root);
    printf("\n");
    
    printf("Iterative Post-order: ");
    iterativePostOrder(root);
    printf("\n");
    
    printf("Level order: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
