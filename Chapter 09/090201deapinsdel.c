/**This code contains answers to Chapter 9, Section 2, Exercises 1-3
 * of Horowitz's Data Structures, p.445.
 */

/**This is a program that depends on the <math.h> preprocessor. To run
 * this program, write gcc deapinsdel.c -o deap -lm followed by ./deap.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_SIZE 100
#define FALSE 0
#define TRUE 1

typedef struct {
    int key;
    /*Other fields*/
} element;

//element deap[MAX_SIZE];

void deap_insert(element deap[], int *n, element x);
int max_heap(int x);
int max_partner(int x);
int min_partner(int x);
void min_insert(element deap[], int index, element x);
void max_insert(element deap[], int index, element x);
void elementSwap(element *px, element *py);
element deap_delete_min(element deap[], int *n);
element deap_delete_max(element deap[], int *n);

int main() {
    int n = 1;
    element deap[MAX_SIZE];

    element keys[12] = {5, 45, 10, 8, 25, 40, 15, 19, 9, 30, 20, 4};

    for (int i = 0; i < 12; i++){
        deap_insert(deap, &n, keys[i]);
    }
    
    printf("Before deleting keys: \n");
    for (int i = 2; i < 14; i++) {
        printf("%d ", deap[i].key);
    }
    printf("\n");
    
    element min_value = deap_delete_min(deap, &n);
    element max_value = deap_delete_max(deap, &n);
    
    printf("The minimum value is %d\n", min_value.key);
    printf("The maximum value is %d\n", max_value.key);
    
    printf("\nAfter deleting keys: \n");
    for (int i = 2; i < 12; i++) {
        printf("%d ", deap[i].key);
    }
    printf("\n");

    return 0;
}

void deap_insert(element deap[], int *n, element x) {
    int i;
    (*n)++;
    if (MAX_SIZE == *n) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }

    if (*n == 2) {
        deap[2] = x;
    } else
        switch (max_heap(*n)) {
            case 0:
                i = max_partner(*n);
                if (x.key > deap[i].key) {
                    deap[*n] = deap[i];
                    max_insert(deap, i, x);
                } else {
                    min_insert(deap, *n, x);
                }
                break;
            case 1:
                i = min_partner(*n);
                if (x.key < deap[i].key) {
                    deap[*n] = deap[i];
                    min_insert(deap, i, x);
                } else {
                    max_insert(deap, *n, x);
                }
        }
}

//verified.
int max_heap(int n) {
    int exp = (int)(log(n) / log(2));
    if ((pow(2.0, exp) <= n) && (n < pow(2.0, exp) + pow(2.0, exp - 1))) {
        return 0;
    }

    return 1;
}

//verified.
int max_partner(int n) {
    return (int)((n + pow(2.0, (int)(log(n) / log(2)) - 1)) / 2);
}

//verified.
int min_partner(int n) {
    return n - (int)(pow(2.0, (int)(log(n) / log(2)) - 1));
}

void min_insert(element deap[], int index, element x) {
    int parent = index / 2;
    deap[index] = x;
    if (parent == 1) {
        deap[index] = x;
    } else {
        while (parent > 1) {
            if (deap[index].key < deap[parent].key) {
                elementSwap(&deap[index], &deap[parent]);
            }
            index /= 2;
            parent = index / 2;
        }
    }
}

void max_insert(element deap[], int index, element x) {
    int parent = index / 2;
    deap[index] = x;
    if (parent == 1) {
        deap[index] = x;
    } else {
        while (parent > 1) {
            if (deap[index].key > deap[parent].key) {
                elementSwap(&deap[index], &deap[parent]);
            }
            index /= 2;
            parent = index / 2;
        }
    }
}

void elementSwap(element *px, element *py) {
    element temp = *px;
    *px = *py;
    *py = temp;
}

element deap_delete_min(element deap[], int *n) {
    element temp;
    int i, j, k;
    if (*n < 2) {
        fprintf(stderr, "The deap is empty.\n");
        deap[0].key = INT_MAX;
        return deap[0];
    }
    deap[0] = deap[2];
    temp = deap[*n++];
    for (i = 2; i * 2 <= *n; deap[i] = deap[j], i = j) {
        j = i * 2;
        if (j + 1 <= *n) {
            if (deap[j].key > deap[j + 1].key)
                j++;
        }
    }
    deap[i] = temp;
    k = max_partner(i);

    while (k <= *n) {
        if (deap[i].key > deap[k].key)
            deap[i] = deap[k];
        max_insert(deap, k, temp);
        break;
    }
    k *= 2;
    if (k + 1 <= *n) {
        if (deap[k].key > deap[k + 1].key) {
            k += 1;
        }
    }
    (*n)--;
    return deap[0];
}

element deap_delete_max(element deap[], int *len) {
    element temp;
    int i, j, k;
    if (*len < 3) {
        fprintf(stderr, "The deap is empty.\n");
        deap[0].key = INT_MAX;
        return deap[0];
    }
    // Save the maximum value
    element max_value = deap[3];
    // Swap the last element with the maximum value
    deap[3] = deap[*len];
    // Adjust the length
    (*len)--;
    // Start from the root
    i = 3;
    while (i * 2 <= *len) {
        // Find the child with the maximum key
        j = i * 2;
        if (j + 1 <= *len && deap[j + 1].key > deap[j].key) {
            j++;
        }
        // Compare with the parent
        if (deap[j].key > deap[i / 2].key) {
            // Swap if child key is greater than parent key
            elementSwap(&deap[i], &deap[j]);
        } else {
            break; // Max-heap property satisfied
        }
        // Move to the child
        i = j;
    }
    return max_value;
}


