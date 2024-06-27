/**Solution to Horowitz's Data Structure, Chapter 9, Section 4, Exercise 2.
 * Let x be an unsorted array of n elements. The function 
 * 'search(x, n, i, y)' searches x for y by examining x[i], x[i+1],
 * x[i+2], ... in that order, for the least j such that x[j] = y.
 * If no such j is found, j is set to n+1. On termination, the 'search'
 * function sets i to j. Assuming that the time it takes to examine a 
 * single element of x is O(1), write the 'search' function in C and a
 * driver code that tests the 'search' function.
 */

#include <stdio.h>

void search(int x[], int n, int* i, int y) {
    for (*i = 0; *i < n; (*i)++) {
        if (x[*i] == y) {
            return;
        }
    }
    *i = n + 1;
}

int main() {
    int x[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(x) / sizeof(x[0]);
    int i, y;

    y = 11;
    search(x, n, &i, y);
    if (i != n + 1) {
        printf("Element %d found at index %d\n", y, i);
    } else {
        printf("Element %d not found\n", y);
    }

    y = 20;
    search(x, n, &i, y);
    if (i != n + 1) {
        printf("Element %d found at index %d\n", y, i);
    } else {
        printf("Element %d not found\n", y);
    }

    return 0;
}
