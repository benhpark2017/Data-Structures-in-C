/**Solutions to Chapter 1, Section 2, Exercise 3 of Horowitz's 
 * Fundamentals of Data Structures in C.
 */

#include <stdio.h>

// Function to print truth values for n variables
void prepareTruthValues(char values[], int n, int index) {
    if (index == n) {
        // Print the current permutation of truth values
        for (int i = 0; i < n; i++) {
            printf("%c ", values[i]);
        }
        printf("\n");
        return;
    }

    // Set the current variable to 'T' and use recursion
    values[index] = 'T';
    prepareTruthValues(values, n, index + 1);

    // Set the current variable to 'F' and use recursion
    values[index] = 'F';
    prepareTruthValues(values, n, index + 1);
}

// Function to initialize and call the recursive helper function
void printTruthValues(int n) {
    char values[n];
    prepareTruthValues(values, n, 0);
}

int main() {
    int n;

    // Get the number of variables from the user
    printf("Enter the number of variables (n): ");
    scanf("%d", &n);

    // Validate input
    if (n <= 0) {
        printf("Number of variables should be greater than 0.\n");
        return 1;
    }

    // Call the function to print truth values
    printTruthValues(n);

    return 0;
}
