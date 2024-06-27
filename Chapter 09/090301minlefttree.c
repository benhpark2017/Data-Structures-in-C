/**Solutions to Chapter 9, Section 3, numbered exercises 1 and 2 of Horowitz's
 * Fundamentals of Data Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct leftist *leftistTree;

struct leftist {
    leftistTree leftChild;
    leftistTree rightChild;
    leftistTree parent;
    element data;
    int shortest;
};

void initializeShortest(leftistTree t);
leftistTree convertToLeftist(leftistTree t);
void printLeftistTree(leftistTree root);
void insertSort(int n, int list[]);
leftistTree initializeMinimumLeftistTree(int n, int arr[]);
int compare(const void *a, const void *b);
leftistTree deleteElement(leftistTree a, leftistTree x);
leftistTree insert(leftistTree root, element data); 
int getHeight(leftistTree node);
int max(int a, int b);

int main() {
    int arr[] = {5, 3, 8, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Initialize minimum leftist tree
    leftistTree root = initializeMinimumLeftistTree(n, arr);

    printf("Leftist Tree Elements: ");
    printLeftistTree(root);
    printf("\n");

    // Test deletion
    leftistTree node_to_delete = root->leftChild->leftChild; // Deleting node with key 1
    printf("Deleting node with key %d\n", node_to_delete->data.key);
    root = deleteElement(root, node_to_delete);

    printf("Leftist Tree Elements after deletion: ");
    printLeftistTree(root);
    printf("\n");

    return 0;
}

leftistTree merge(leftistTree h1, leftistTree h2) {
    if (h1 == NULL) // Base case: If the first tree is empty, return the second tree
        return h2;
    if (h2 == NULL) // Base case: If the second tree is empty, return the first tree
        return h1;

    // Choose the smaller root as the root of the merged tree
    if (h1->data.key > h2->data.key) {
        leftistTree temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // Recursively merge the smaller root's right subtree with the other tree
    h1->rightChild = merge(h1->rightChild, h2);

    // Ensure leftist property: Swap left and right children if necessary
    if (h1->leftChild == NULL || h1->rightChild == NULL) {
        leftistTree temp = h1->leftChild;
        h1->leftChild = h1->rightChild;
        h1->rightChild = temp;
    } else {
        if (h1->leftChild->shortest < h1->rightChild->shortest) {
            leftistTree temp = h1->leftChild;
            h1->leftChild = h1->rightChild;
            h1->rightChild = temp;
        }
        h1->shortest = h1->rightChild->shortest + 1;
    }

    return h1; // Return the merged tree
}


/**Solution to Chapter 9 Section 3 Exercise 1(a) of Horowitz's Data Structures*/
void initializeShortest(leftistTree t) {
    if (t == NULL) {
        return;
    }
    
    // Initialize the shortest field of the current node
    t->shortest = 1;
    
    // Recursively initialize the shortest field of the left and right children
    initializeShortest(t->leftChild);
    initializeShortest(t->rightChild);
}

/**Solution to Chapter 9 Section 3 Exercise 1(b) of Horowitz's Data Structures*/
leftistTree convertToLeftist(leftistTree t) {
    // Base case: if the tree is empty, return NULL
    if (t == NULL) {
        return NULL;
    }
    
    // Traverse the binary tree in an in-order manner
    convertToLeftist(t->leftChild);
    
    // Compare the key of the current node with its left and right children
    if (t->leftChild != NULL && t->data.key > t->leftChild->data.key) {
        // Swap the current node with its left child
        leftistTree temp = t->leftChild;
        t->leftChild = temp->rightChild;
        temp->rightChild = t;
        t = temp;
    }
    
    // Repeat step 3 for the right child
    if (t->rightChild != NULL && t->data.key > t->rightChild->data.key) {
        // Swap the current node with its right child
        leftistTree temp = t->rightChild;
        t->rightChild = temp->rightChild;
        temp->rightChild = t;
        t = temp;
    }
    
    // Update the shortest field of the current node
    t->shortest = 1;
    
    return t;
}

// Function to print the elements of the leftist tree
void printLeftistTree(leftistTree root) {
    if (root == NULL) {
        return;
    }
    
    printf("%d ", root->data.key);
    printLeftistTree(root->leftChild);
    printLeftistTree(root->rightChild);
}

void insertSort(int n, int list[]) {
    int t;
    for (int i = 1; i < n; i++ ) {
        t = list[i];
        int j = i;
        while (list[j - 1] > t && j > 0) {
            list[j] = list[j-1];
            j--;
        }
        list[j] = t;
    }
}

leftistTree initializeMinimumLeftistTree(int n, int arr[]) {
    // Sort the array in ascending order
    insertSort(n, arr);
    
    // Initialize the root of the leftist tree as NULL
    leftistTree root = NULL;
    
    for (int i = 0; i < n; i++) {
        // Allocate memory for a new node
        leftistTree newNode = (leftistTree)malloc(sizeof(struct leftist));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        // Assign key value
        newNode->data.key = arr[i];
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        newNode->parent = NULL;
        newNode->shortest = 1;
        
        // Insert the new node into the leftist tree
        root = merge(root, newNode);
    }
    
    return root;
}


//Helper function of initializeMinimumLeftistTree(n, arr) function
int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

leftistTree deleteElement(leftistTree a, leftistTree x) {
    // Base case: if the tree is empty or x is NULL, return NULL
    if (a == NULL || x == NULL) {
        return NULL;
    }
    
    // If x is the root of the tree
    if (a == x) {
        // If x has no children, simply free x and return NULL
        if (x->leftChild == NULL && x->rightChild == NULL) {
            free(x);
            return NULL;
        }
        // If x has only one child, update the root and free x
        if (x->leftChild == NULL) {
            a = x->rightChild;
            free(x);
            return a;
        }
        if (x->rightChild == NULL) {
            a = x->leftChild;
            free(x);
            return a;
        }
        // If x has two children
        // Find the inorder successor of x (the leftmost node in its right subtree)
        leftistTree successor = x->rightChild;
        while (successor->leftChild != NULL) {
            successor = successor->leftChild;
        }

        // Replace x with its inorder successor's data
        x->data = successor->data;

        // If the successor is a direct child of x, remove it from the tree
        if (x->rightChild == successor) {
            x->rightChild = NULL;
        } else {
    // Recursively delete the inorder successor from the right subtree
            x->rightChild = deleteElement(x->rightChild, successor);
        }

        return a;
    }
    
    // If x has no parent (i.e., it's not in the tree), return the root
    if (x->parent == NULL) {
        return a;
    }
    
    // If x has no children
    if (x->leftChild == NULL && x->rightChild == NULL) {
        // Remove x from its parent's child list
        if (x->parent->leftChild == x) {
            x->parent->leftChild = NULL;
        } else {
            x->parent->rightChild = NULL;
        }
        // Free the memory of x
        free(x);
        return a;
    }
    
    // If x has only one child
    if (x->leftChild == NULL) {
        // Replace x with its right child
        if (x->parent->leftChild == x) {
            x->parent->leftChild = x->rightChild;
        } else {
            x->parent->rightChild = x->rightChild;
        }
        x->rightChild->parent = x->parent;
        free(x);
        return a;
    }
    if (x->rightChild == NULL) {
        // Replace x with its left child
        if (x->parent->leftChild == x) {
            x->parent->leftChild = x->leftChild;
        } else {
            x->parent->rightChild = x->leftChild;
        }
        x->leftChild->parent = x->parent;
        free(x);
        return a;
    }
    
    // If x has two children
    // Find the inorder successor of x (the leftmost node in its right subtree)
    leftistTree successor = x->rightChild;
    while (successor->leftChild != NULL) {
        successor = successor->leftChild;
    }
    
    // Replace x with its inorder successor's data
    x->data = successor->data;
    
    // Recursively delete the inorder successor from the right subtree
    x->rightChild = deleteElement(x->rightChild, successor);
    
    return a;
}


leftistTree insert(leftistTree root, element data) {
    // Create a new node with the given data
    leftistTree newNode = (leftistTree)malloc(sizeof(struct leftist));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;
    newNode->shortest = 1;
    
    // If the tree is empty, set the new node as the root and return
    if (root == NULL) {
        root = newNode;
        return root;
    }
    
    // Compare the key of the new node with the keys of the current node and its children
    while (root != NULL) {
        if (data.key < root->data.key) {
            if (root->leftChild == NULL) {
                root->leftChild = newNode;
                newNode->parent = root;
                break;
            } else {
                root = root->leftChild;
            }
        } else if (data.key > root->data.key) {
            if (root->rightChild == NULL) {
                root->rightChild = newNode;
                newNode->parent = root;
                break;
            } else {
                root = root->rightChild;
            }
        } else {
            // If the key of the new node is equal to the key of the current node, compare the heights of the left and right subtrees
            if (getHeight(root->leftChild) > getHeight(root->rightChild)) {
                root->rightChild = newNode;
                newNode->parent = root;
            } else {
                root->leftChild = newNode;
                newNode->parent = root;
            }
            break;
        }
    }
    
    // Update the shortest field of each node to 1
    initializeShortest(root);
    
    return root;
}

int getHeight(leftistTree node) {
    if (node == NULL) {
        return 0;
    }
    
    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);
    
    return max(leftHeight, rightHeight) + 1;
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

