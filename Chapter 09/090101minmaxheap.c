/**Solutions to Chapter 9, Section 1, numbered exercises 1 through 5 of Horowitz's
 * Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX_SIZE 101
#define FALSE 0
#define TRUE 1
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
    /*other fields*/
} element;
element heap[MAX_SIZE];

int level(int x);
int min_child_grandchild(int i, int *n);
int max_child_grandchild(int i, int *n);
void min_max_insert(element heap[], int *n, element item);
void verify_max(element heap[], int i, element item);
void verify_min(element heap[], int i, element item);
element delete_max(element heap[], int *n);
element delete_min(element heap[], int *n);

int main(){
    int n = 0;
    element ht[] = {7, 2, 30, 9, 100, 40, 15};
    
    for (int i = 0; i < 7 ; ++i){
        min_max_insert(heap, &n, ht[i]);
    }
    
    printf("Before deletion of nodes: ");
    for (int i = 1; i < 8 ; ++i){
        printf("%d ", heap[i].key);
    }
    printf("\n");
    
    delete_max(heap, &n);
    printf("After deletion of maximum node: ");
    for (int i = 1; i < 7 ; ++i){
        printf("%d ", heap[i].key);
    }
    printf("\n");
    
    delete_min(heap, &n);
    printf("After deletion of minimum node: ");
    for (int i = 1; i < 6 ; ++i){
        printf("%d ", heap[i].key);
    }
    printf("\n");
    
}

int level(int x) {
    int t = ((int)(log((double)x) / log(2.0))) % 2;
    if (t == 0) return 0;
    else return 1;
}

int min_child_grandchild(int i, int *n) {
    int min = i + 1;
    for (int j = i + 2; j <= *n; ++j)
        if (heap[min].key > heap[i].key) min = i;
    return min;
}

int max_child_grandchild(int i, int *n) {
    int max = i + 1;
    for (int j = i + 2; j <= *n; ++j)
        if (heap[max].key < heap[i].key) max = i;
    return max;
}

void min_max_insert(element heap[], int *n, element item) {
    /*insert item into the minimum-maximum heap*/
    /**Algorithm:
     * 1) Insert the required node to a given min-max heap
     * 2) Compare the node with its parent
     * 3) Check nodes at min and max levels.
     */
    int parent;
    (*n)++;
    if ( *n == MAX_SIZE ){
        printf("The heap is full.\n");
        return;
    }
    parent = (*n) / 2;
    if (!parent) heap[1] = item; // heap is empty, insert item into first position
    else switch ( level(parent) ) {
            case FALSE : //in case of min level
                if ( item.key < heap[parent].key ) {
                    heap[*n] = heap[parent];
                    verify_min(heap, parent, item); 
                }
                else
                    verify_max(heap, *n, item);
                break;
            case TRUE :                            // max level 일때,
                if (item.key > heap[parent].key ) {
                    heap[*n] = heap[parent];
                    verify_max(heap, parent, item); 
                }
                else
                    verify_min(heap, *n, item );
    }
}

void verify_max(element heap[], int i, element item) {
    /** Follows the nodes from the max node i to the root
     *  and inserts item into its proper place*/
    int grandparent = i / 4;                                             
    while (grandparent) {
        if (item.key > heap[grandparent].key) {
            heap[i] = heap[grandparent];                             
            i  = grandparent;
            grandparent /= 4;
        } else break;
    }
    heap[i] = item;
}

void verify_min(element heap[], int i, element item) {
    int grandparent = i / 4;
    while (grandparent) {
        if ( item.key < heap[grandparent].key) {
            heap[i] = heap[grandparent];
            i  = grandparent;
            grandparent /= 4;
        } else break;
    }
    heap[i] = item;
}

element delete_max(element heap[], int *n) {
    /**Deletes the maximum element from the min-max heap.*/
    int i, last, k, parent;
    element temp, x;

    if (!(*n)) {
        fprintf(stderr, "The heap is empty.\n");
        heap[0].key = INT_MAX; // Assuming INT_MIN is defined in limits.h
        return heap[0];
    }

    // Find the maximum element in the heap
    int max_index = 1;
    for (i = 2; i <= *n; i++) {
        if (heap[i].key > heap[max_index].key) {
            max_index = i;
        }
    }

    heap[0] = heap[max_index]; // Save the maximum element
    x = heap[(*n)--]; // Remove the last element and decrement heap size

    // Find place to insert x
    for (i = max_index; last = (*n) / 2; i = k) {
        k = max_child_grandchild(i, n);
        if (x.key >= heap[k].key) {
            break;
        }
        heap[i] = heap[k];
        if (k <= 2 * i + 1) {
            i = k;
            break;
        }
        parent = k / 2;
        if (x.key < heap[parent].key) {
            SWAP(heap[parent], x, temp);
        }
        i = k;
    }
    heap[i] = x;
    return heap[0];
}


element delete_min(element heap[], int *n) {
    /**Deletes the minimum element from the min-max heap.*/
    int i, last, k, parent;
    element temp, x;
    
    if (!(*n)) {
        fprintf(stderr, "The heap is empty.\n");
        heap[0].key = INT_MAX;
        return heap[0];
    }
    heap[0] = heap[1]; //save the element
    x = heap[(*n)--];
    /*Find place to insert x*/
    for (i = 1; last = (*n)/2; i <= last) {
        k = min_child_grandchild(i, n);
        if (x.key <= heap[k].key) break;
        
        //case 2(b)
        heap[i] = heap[k];
        if (k <= 2 * i + 1) {
            i = k;
            break;
        }
        //case 2(c), where k is the grandchild of i
        parent = k / 2;
        if (x.key > heap[parent].key) SWAP(heap[parent], x, temp);
        i = k;
    } //end of for loop
    heap[i] = x;
    return heap[0];
}

