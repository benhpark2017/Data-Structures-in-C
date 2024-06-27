/**Solutions to Chapter 10 Section 2 of Horowitz's Data Structures, 
 * numbered exercises 3 and 10.
 */

#include <stdio.h>
#include <stdlib.h> //malloc

#define IS_FULL(ptr) (!(ptr))
#define FALSE 0
#define TRUE 1

typedef struct {
    int key;
} element;

struct treeNode {
    struct treeNode *leftChild;
    element data;
    short int bf; //balance factor
    struct treeNode *rightChild;
} treeNode;

typedef struct treeNode *treePtr;

//Function prototypes
void AVLinsertElement(treePtr *parent, int key, int *unbalanced);
void AVLinsert(treePtr *parent, element x, int *unbalanced);
void leftRotation(treePtr *parent, int *unbalanced);
void rightRotation(treePtr *parent, int *unbalanced);
int maxHeight(int a, int b);
int AVLtreeHeight(treePtr node);
void AVLtreePreOrder(treePtr node);
void AVLtreeInOrder(treePtr node);
void AVLtreePostOrder(treePtr node);
treePtr deleteNode(treePtr root, int key, int *unbalanced);
void freeTree(treePtr root);

int unbalanced = FALSE;
treePtr root = NULL;

int main() {
    element elements[] = {
        {5}, {3}, {7}, {2}, {4}, {6}, {8}
    };
    
    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); ++i) {
        AVLinsertElement(&root, elements[i].key, &unbalanced);
    }
    
    printf("AVL Tree in Pre-order: ");
    AVLtreePreOrder(root);
    printf("\n");

    printf("AVL Tree in In-order: ");
    AVLtreeInOrder(root);
    printf("\n");

    printf("AVL Tree in Post-order: ");
    AVLtreePostOrder(root);
    printf("\n");

    // Delete a node from the AVL tree
    int key_to_delete = 3;
    root = deleteNode(root, key_to_delete, &unbalanced);

    printf("AVL Tree after deleting node with key %d in Pre-order: ", key_to_delete);
    AVLtreePreOrder(root);
    printf("\n");

    freeTree(root);

    return 0;
}

void AVLinsertElement(treePtr *parent, int key, int *unbalanced) {
    element x;
    x.key = key;
    AVLinsert(parent, x, unbalanced);
}

//This code is correct. It works now!
void AVLinsert(treePtr *parent, element x, int *unbalanced) {
    if (*parent == NULL) {
        // Insert element into null tree
        *unbalanced = TRUE;
        *parent = (treePtr)malloc(sizeof(treeNode));
        if (IS_FULL(*parent)) {
            fprintf(stderr, "The memory is full.\n");
            exit(1);
        }
        (*parent)->leftChild = (*parent)->rightChild = NULL;
        (*parent)->bf = 0;
        (*parent)->data = x;
    } else if (x.key < (*parent)->data.key) {
        AVLinsert(&(*parent)->leftChild, x, unbalanced);
        if (*unbalanced) {
            // The left branch has grown higher.
            switch ((*parent)->bf) {
                case -1: (*parent)->bf = 0;
                         *unbalanced = FALSE;
                         break;
                case 0:  (*parent)->bf = 1;
                         break;
                case 1:  leftRotation(parent, unbalanced);
            }
        }
    } else if (x.key > (*parent)->data.key) {
        AVLinsert(&(*parent)->rightChild, x, unbalanced);
        if (*unbalanced) {
            // The right branch has grown higher.
            switch ((*parent)->bf) {
                case 1: (*parent)->bf = 0;
                         *unbalanced = FALSE;
                         break;
                case 0:  (*parent)->bf = -1;
                         break;
                case -1:  rightRotation(parent, unbalanced);
            }
        }
    } else {
        *unbalanced = FALSE;
        printf("The key is already in the tree.\n");
    }
}


void leftRotation(treePtr *parent, int *unbalanced) {
    treePtr grandchild, child;
    child = (*parent)->leftChild;
    if (child->bf == 1) {
        //LL rotation
        (*parent)->leftChild = child->rightChild;
        child->rightChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;
    } else {
        //LR rotation
        grandchild = child->rightChild;
        child->rightChild = grandchild->leftChild;
        grandchild->leftChild = child;
        (*parent)->leftChild = grandchild->rightChild;
        grandchild->rightChild = *parent;
        
        switch(grandchild->bf) {
            case 1:  (*parent)->bf = -1;
                     child->bf = 0;
                     break;
            case 0:  (*parent)->bf = child->bf = 0;
                     break;
            case -1: (*parent)->bf = 0;
                     child->bf = 1;
        }
        *parent = grandchild;
    }
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}

void rightRotation(treePtr *parent, int *unbalanced) {
    treePtr grandchild, child;
    child = (*parent)->rightChild;
    if (child->bf == -1) {
        // RR rotation
        (*parent)->rightChild = child->leftChild;
        child->leftChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;
    } else {
        // RL rotation
        grandchild = child->leftChild;
        child->leftChild = grandchild->rightChild;
        grandchild->rightChild = child;
        (*parent)->rightChild = grandchild->leftChild;
        grandchild->leftChild = *parent;
        
        switch(grandchild->bf) {
            case -1: (*parent)->bf = 1;
                     child->bf = 0;
                     break;
            case 0:  (*parent)->bf = child->bf = 0;
                     break;
            case 1:  (*parent)->bf = 0;
                     child->bf = -1;
        }
        *parent = grandchild;
    }
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}

int maxHeight(int a, int b) {
    return (a > b) ? a : b;
}

int treeHeight(treePtr node) {
    if (node == NULL)
        return -1; // Height of empty tree is -1
    else {
        int leftHeight = treeHeight(node->leftChild);
        int rightHeight = treeHeight(node->rightChild);
        return 1 + maxHeight(leftHeight, rightHeight);
    }
}

void AVLtreePreOrder(treePtr node) {
    if (node) {
        printf("%d ", node->data.key); // Print the current node's key
        AVLtreePreOrder(node->leftChild); // Recursively print the left subtree
        AVLtreePreOrder(node->rightChild); // Recursively print the right subtree
    }
}

void AVLtreeInOrder(treePtr node) {
    if (node) {
        AVLtreeInOrder(node->leftChild); // Recursively print the left subtree
        printf("%d ", node->data.key); // Print the current node's key
        AVLtreeInOrder(node->rightChild); // Recursively print the right subtree
    }
}

void AVLtreePostOrder(treePtr node) {
    if (node) {
        AVLtreePostOrder(node->leftChild); // Recursively print the left subtree
        AVLtreePostOrder(node->rightChild); // Recursively print the right subtree
        printf("%d ", node->data.key); // Print the current node's key
    }
}

treePtr deleteNode(treePtr root, int key, int *unbalanced) {
    if (root == NULL) {
        // Node with key not found
        printf("Node with key %d not found\n", key);
        return root;
    }

    if (key < root->data.key) {
        // Key is smaller than current node's key, move to left subtree
        root->leftChild = deleteNode(root->leftChild, key, unbalanced);
    } else if (key > root->data.key) {
        // Key is greater than current node's key, move to right subtree
        root->rightChild = deleteNode(root->rightChild, key, unbalanced);
    } else {
        // Node with key found
        treePtr temp;
        if (root->leftChild == NULL || root->rightChild == NULL) {
            // Node has at most one child
            temp = root->leftChild ? root->leftChild : root->rightChild;
            if (temp == NULL) {
                // No child
                temp = root;
                root = NULL;
            } else {
                // Copy the contents of the non-empty child
                *root = *temp;
            }
            free(temp);
        } else {
            // Node has two children, find the inorder successor
            temp = root->rightChild;
            while (temp->leftChild != NULL) {
                temp = temp->leftChild;
            }
            // Copy the inorder successor's data to this node
            root->data = temp->data;
            // Delete the inorder successor
            root->rightChild = deleteNode(root->rightChild, temp->data.key, unbalanced);
        }
    }
    // If the tree is empty after deletion
    if (root == NULL) {
        return root;
    }
    // Update balance factor and check for unbalance
    if (*unbalanced) {
        if (root->bf > 1 && root->leftChild->bf >= 0) {
            // Left Left Case: Perform right rotation
            rightRotation(&root, unbalanced);
        } else if (root->bf > 1 && root->leftChild->bf < 0) {
            // Left Right Case: Perform left rotation on left child, then right rotation on root
            leftRotation(&(root->leftChild), unbalanced);
            rightRotation(&root, unbalanced);
        } else if (root->bf < -1 && root->rightChild->bf <= 0) {
            // Right Right Case: Perform left rotation
            leftRotation(&root, unbalanced);
        } else if (root->bf < -1 && root->rightChild->bf > 0) {
            // Right Left Case: Perform right rotation on right child, then left rotation on root
            rightRotation(&(root->rightChild), unbalanced);
            leftRotation(&root, unbalanced);
        }
    }
    return root;
}

void freeTree(treePtr root) {
    if (root != NULL) {
        freeTree(root->leftChild); // Recursively free left subtree
        freeTree(root->rightChild); // Recursively free right subtree
        free(root); // Free current node
    }
}
