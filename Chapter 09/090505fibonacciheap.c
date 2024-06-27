/**Solutions to Chapter 9, Section 5, Exercise 5 of Horowitz's Data
 * Structures in C. */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for an element in the Fibonacci Heap
typedef struct {
    int key; // or any other data type you want to use as the key
} element;

// Structure for a node in the Fibonacci Heap
typedef struct FibonacciNode {
    struct FibonacciNode *parent;
    struct FibonacciNode *child;
    struct FibonacciNode *left;
    struct FibonacciNode *right;
    int degree;
    int marked;
    element data; // Modified to use 'element' type for key
} FibonacciNode;

// Structure for the Fibonacci Heap
typedef struct FibonacciHeap {
    FibonacciNode *min;
    int num_nodes;
} FibonacciHeap;

// Function to create an empty Fibonacci Heap
FibonacciHeap* createFibonacciHeap();

// Function to create a new Fibonacci node
FibonacciNode* createFibonacciNode(element key);

// Function to insert an element into a Fibonacci Heap
void insert(FibonacciHeap *heap, element key);

FibonacciHeap* heapUnion(FibonacciHeap *heap1, FibonacciHeap *heap2);

// Function to delete the minimum key from a Fibonacci Heap
void deleteMinimum(FibonacciHeap *heap);

// Function to print the keys of the elements in a Fibonacci Heap in order
void printHeap(FibonacciHeap *heap);

void decreaseKey(FibonacciHeap *a, FibonacciNode *b, int c);

// Function to cut a node from its parent
void cut(FibonacciHeap *heap, FibonacciNode *node, FibonacciNode *parent);

// Function to perform cascading cuts
void cascadingCut(FibonacciHeap *heap, FibonacciNode *node);

// Function to delete the element in node 'b' of the Fibonacci heap 'a' and return the deleted element
element deleteElement(FibonacciHeap *a, FibonacciNode *b);

// Function that decreases the key in node 'b' of Fibonacci heap 'a' by some positive amount 'c' 
void decreaseKey(FibonacciHeap *a, FibonacciNode *b, int c);

int main() {
    // Create an empty Fibonacci Heap
    FibonacciHeap *heapFirst = createFibonacciHeap();
    FibonacciHeap *heapSecond = createFibonacciHeap();
    
    // Create elements
    element inputFirst[] = {5, 10, 3, 7, 12, 11, 8};
    element inputSecond[] = {1, 9, 14, 6, 4, 2};
    
    // Insert elements into the first heap
    for (int i = 0; i < sizeof(inputFirst) / sizeof(int); i++) {
        insert(heapFirst, inputFirst[i]);
    }
    
    // Insert elements into the second heap
    for (int i = 0; i < sizeof(inputSecond) / sizeof(int); i++) {
        insert(heapSecond, inputSecond[i]);
    }
    
    // Print the heap before deleting the minimum key
    printf("First and second heaps before deleting the minimum key:\n");
    printHeap(heapFirst);
    printHeap(heapSecond);
    
    // Delete the minimum key from the first heap
    deleteMinimum(heapFirst);
    
    // Delete an element from the second heap
    FibonacciNode *node_to_delete = NULL;
    FibonacciNode *current = heapSecond->min;
    for (int i = 0; current->data.key == 10; i++) {
        node_to_delete = current;
        break;
    }    
    current = current->right;

    // If the node is found, delete it and print the deleted key
    if (node_to_delete != NULL) {
        element deleted_key = deleteElement(heapSecond, node_to_delete);
        printf("Deleted key: %d\n", deleted_key.key);
    } else {
        printf("Node not found!\n");
    }
    
    // Print the heap after deleting the minimum key
    printf("Heap after deleting the minimum key:\n");
    printHeap(heapFirst);
    
    printf("Before decreasing the key 14 in the second heap by 1:\n");
    FibonacciNode *currentSecond = heapSecond->min;
    while (currentSecond != NULL && currentSecond->data.key != 14) {
        currentSecond = currentSecond->right;
    }
    if (currentSecond != NULL) {
        decreaseKey(heapSecond, currentSecond, 1);
        printf("Key '14' decreased by '1'.\n");
    } else {
        printf("Key '14' not found in the heap.\n");
    }
    
    FibonacciHeap *heapCombined = heapUnion(heapFirst, heapSecond);
    printf("Heap after combining two Fibonacci heaps:\n");
    printHeap(heapCombined);
    
    // Frees the allocated memory when done
    free(heapCombined);
    
    return 0;
}

// Function to create an empty Fibonacci Heap
FibonacciHeap* createFibonacciHeap() {
    FibonacciHeap *heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    if (heap == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    heap->min = NULL;
    heap->num_nodes = 0;
    return heap;
}

// Function to create a new Fibonacci node
FibonacciNode* createFibonacciNode(element key) {
    FibonacciNode *node = (FibonacciNode*)malloc(sizeof(FibonacciNode));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->data = key;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->degree = 0;
    node->marked = 0;
    return node;
}

// Function to insert an element into a Fibonacci Heap
void insert(FibonacciHeap *heap, element key) {
    FibonacciNode *node = createFibonacciNode(key);
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        // Merge node with the root list
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        // Compare the keys
        if (node->data.key < heap->min->data.key) {
            heap->min = node;
        }
    }
    heap->num_nodes++;
}

FibonacciHeap* heapUnion(FibonacciHeap *heap1, FibonacciHeap *heap2) {
    FibonacciHeap *heap = createFibonacciHeap();
    
    if (heap1->min == NULL) {
        heap->min = heap2->min;
    } else if (heap2->min == NULL) {
        heap->min = heap1->min;
    } else {
        FibonacciNode *minHeap1 = heap1->min;
        FibonacciNode *minRightHeap1 = minHeap1->right;
        FibonacciNode *minHeap2 = heap2->min;
        FibonacciNode *minRightHeap2 = minHeap2->right;
        
        minHeap1->right = minRightHeap2;
        minRightHeap2->left = minHeap1;
        
        minHeap2->right = minRightHeap1;
        minRightHeap1->left = minHeap2;
        
        if (heap1->min->data.key > heap2->min->data.key){
            heap->min = heap2->min;
        } else {
            heap->min = heap1->min;
        }
    }
    
    heap->num_nodes = heap1->num_nodes + heap2->num_nodes;
    
    free(heap1);
    free(heap2);
    
    return heap;
}


// Function to delete the minimum key from a Fibonacci Heap
void deleteMinimum(FibonacciHeap *heap) {
    if (heap->min == NULL) {
        printf("Heap is empty!\n");
        return;
    }
    
    FibonacciNode *min_node = heap->min;
    FibonacciNode *child = min_node->child;
    FibonacciNode *temp;
    
    // Remove min_node from the root list
    if (min_node->right == min_node) {
        heap->min = NULL;
    } else {
        min_node->right->left = min_node->left;
        min_node->left->right = min_node->right;
        heap->min = min_node->right;
    }
    
    // Merge the children of min_node with the root list
    if (child != NULL) {
        temp = child;
        do {
            temp->parent = NULL;
            temp = temp->right;
        } while (temp != child);
        
        min_node->left->right = child;
        child->left = min_node->left;
        min_node->right = child;
        child->left = min_node;
    }
    
    // Consolidate the root list
    // (This step is not implemented here)
    
    // Update the minimum pointer
    if (heap->min == min_node) {
        heap->min = min_node->right;
    }
    
    // Free the memory allocated for the minimum node
    free(min_node);
}

// Function to print the keys of the elements in a Fibonacci Heap in order
void printHeap(FibonacciHeap *heap) {
    if (heap == NULL || heap->min == NULL) {
        printf("Heap is empty!\n");
        return;
    }

    printf("Keys of elements in the Fibonacci Heap: ");
    
    FibonacciNode *current = heap->min;
    do {
        printf("%d ", current->data.key);
        FibonacciNode *child = current->child;
        if (child != NULL) {
            FibonacciNode *temp = child;
            do {
                printf("%d ", temp->data.key);
                temp = temp->right;
            } while (temp != child);
        }
        current = current->right;
    } while (current != heap->min);
    
    printf("\n");
}

void decreaseKey(FibonacciHeap *a, FibonacciNode *b, int c) {
    if (a == NULL || b == NULL) {
        printf("Invalid heap or node!\n");
        return;
    }
    
    // Decrease the key in node 'b' by the constant 'c'
    b->data.key -= c;

    // Check if the decreased key violates the heap property
    if (b->parent != NULL && b->data.key < b->parent->data.key) {
        // Perform cascading cuts
        FibonacciNode *parent = b->parent;
        cut(a, b, parent);
        cascadingCut(a, parent);
    }

    // Update the min pointer if necessary
    if (b->data.key < a->min->data.key) {
        a->min = b;
    }
}

// Function to cut a node from its parent
void cut(FibonacciHeap *heap, FibonacciNode *node, FibonacciNode *parent) {
    // Remove node from its parent's child list
    if (parent->child == node) {
        if (node->right == node) {
            parent->child = NULL;
        } else {
            parent->child = node->right;
        }
    }
    node->left->right = node->right;
    node->right->left = node->left;
    parent->degree--;

    // Add the cut node to the root list
    node->left = heap->min;
    node->right = heap->min->right;
    heap->min->right->left = node;
    heap->min->right = node;

    // Mark the node as unmarked
    node->marked = 0;
}

// Function to perform cascading cuts
void cascadingCut(FibonacciHeap *heap, FibonacciNode *node) {
    FibonacciNode *parent = node->parent;

    if (parent != NULL) {
        // If the parent is unmarked, mark it
        if (!parent->marked) {
            parent->marked = 1;
        } else {
            // If the parent is already marked, cut it from its parent
            cut(heap, parent, parent->parent);
            // Recursively perform cascading cuts on the parent
            cascadingCut(heap, parent);
        }
    }
}

// Function to delete the element in node 'b' of the Fibonacci heap 'a' and return the deleted element
element deleteElement(FibonacciHeap *a, FibonacciNode *b) {
    element deleted_element;

    // If either the heap or the node is NULL, return a sentinel value indicating failure
    if (a == NULL || b == NULL) {
        deleted_element.key = INT_MIN; // Return a sentinel value indicating failure
        return deleted_element;
    }

    // Find the node 'b' in the Fibonacci heap 'a'
    FibonacciNode *current = a->min;
    FibonacciNode *prev = NULL;
    while (current != NULL && current != b) {
        prev = current;
        current = current->right;
    }

    // If the node 'b' is not found in the Fibonacci heap 'a', return a sentinel value indicating failure
    if (current == NULL) {
        deleted_element.key = INT_MIN; // Return a sentinel value indicating failure
        return deleted_element;
    }

    // Remove the node 'b' from the Fibonacci heap 'a'
    if (prev != NULL) {
        prev->right = current->right;
        current->right->left = prev;
        if (current == a->min) {
            a->min = current->right;
        }
    }

    // Perform cascading cut to maintain the heap property
    cascadingCut(a, current);

    // Return the key of the deleted node 'b'
    deleted_element = current->data;

    // Free the memory allocated for the deleted node 'b'
    free(current);

    // Decrease the number of nodes in the Fibonacci heap 'a'
    a->num_nodes--;

    return deleted_element;
}

