/**Solutions to Chapter 1, Section 2, Exercise 10 of Horowitz's Data
 * Structures in C.*/

#include <stdio.h>
#include <stdlib.h>

unsigned long recursiveAckermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return recursiveAckermann(m - 1, 1);
    } else {
        return recursiveAckermann(m - 1, recursiveAckermann(m, n - 1));
    }
}


unsigned long iterativeAckermann(int m, int n) {
    // Allocate an array to simulate the "right" list
    int* right = (int*)malloc((m + 1) * sizeof(int));
    int result = n;
    int i = 0;

    right[0] = m;

    while (1) {
        if (right[i] > 0 && result > 0) {
            right = (int*)realloc(right, (m + i + 2) * sizeof(int));
            right[i + 1] = right[i];
            right[i] -= 1;
            result -= 1;
            i += 1;
        } else if (right[i] > 0 && result == 0) {
            right[i] -= 1;
            result = 1;
        } else if (right[i] == 0) {
            result += 1;
            i -= 1;
        }

        if (i < 0) {
            break;
        }
    }

    free(right); // Free the allocated memory
    return result;
}


int main() {
    int m, n;

    printf("Please specify the integer m of A(m, n).\n");
    scanf("%d", &m);

    printf("Please specify the integer n of A(m, n).\n");
    scanf("%d", &n);

    printf("Recursive: A(%d, %d) = %ld\n", m, n, recursiveAckermann(m, n));
    printf("Iterative: A(%d, %d) = %ld\n", m, n, iterativeAckermann(m, n));

    return 0;
}

