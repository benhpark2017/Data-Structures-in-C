/*Solution to Horowitz's Data Structures, Chapter 7, Section 3, Exercise 1*/

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int key;
    // add other fields as needed
} element;

bool ascending(int x, int y) {
    return x < y;
}

bool descending(int x, int y) {
    return x > y;
}

void insertion_sort(element list[], int n, bool (*compare)(int, int)) {
    int i, j;
    element next;
    for (i = 1; i < n; i++) {
        next = list[i];
        for (j = i - 1; j >= 0 && compare(next.key, list[j].key); j--)
            list[j + 1] = list[j];
        list[j + 1] = next;
    }
}

int main() {
    // Example usage
    element list[] = {{5}, {3}, {8}, {1}, {4}, {9}, {2}, {6}, {7}, {10}};
    int n = sizeof(list) / sizeof(list[0]);

    insertion_sort(list, n, ascending);

    // Printing sorted list
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i].key);
    }
    printf("\n");
    
    insertion_sort(list, n, descending);
    
    // Printing sorted list
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i].key);
    }
    printf("\n");    

    return 0;
}
