/**Solutions to Chapter 1, Section 5, Exercise 5 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>

int recursiveSeqSearch(int list[], int searchnum, int n, int i) {
    if (i >= n) {
        // Base case: element not found
        return -1;
    }

    if (list[i] == searchnum) {
        // Base case: element found
        return i;
    }

    // Recursive case: continue searching in the rest of the array
    return recursiveSeqSearch(list, searchnum, n, i + 1);
}

int iterativeSeqSearch(int list[], int searchnum, int n){
    int i = 0;
    list[n] = searchnum;
    while (list[i] != searchnum) i++;
    if (i < n) return i;
    else return -1;
}

int main() {
    // Example usage:
    int list[] = {1, 2, 3, 4, 5};
    int searchnum = 3;
    int n = sizeof(list) / sizeof(list[0]);

    int recursiveResult = recursiveSeqSearch(list, searchnum, n, 0);
    int iterativeResult = iterativeSeqSearch(list, searchnum, n);

    if (recursiveResult != -1) {
        printf("Element found at index: %d\n", recursiveResult);
    } else {
        printf("Element not found in the array.\n");
    }

    if (iterativeResult != -1) {
        printf("Element found at index: %d\n", iterativeResult);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}

