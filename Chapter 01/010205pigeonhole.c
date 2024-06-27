/**Solutions to Chapter 1, Section 2, Exercise 5 of Horowitz's
 * Fundamentals of Data Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to find all instances of a and b such that f(a) = f(b)
void findCollisions(int* input, int n) {
    // Create a dictionary to store indices for each output value
    bool* seen = (bool*)calloc(n, sizeof(bool));
    for (int i = 0; i < n; i++)
        seen[i] = false;

    // Iterate through the input array
    for (int i = 0; i < n; i++) {
        int value = input[i];

        // Check if the value has been seen before
        if (seen[value]) {
            // Print all encountered indices including current one
            for (int j = 0; j < i; j++){
                if (input[j] == value)
                    printf("Value %d occurs at indices %d and %d\n", value, j, i);
            } //end inner for
        } else seen[value] = true;
    }//end outer for

    // Free the dynamically allocated memory
    free(seen);
}

int main() {
    // Example usage
    int n;

    // Get input size from the user
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    // Allocate memory for the input array
    int* input = (int*)malloc(n * sizeof(int));

    // Get input values from the user
    printf("Enter the elements of the array, starting from f(0): \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }

    // Call the function to find all instances of a and b
    findCollisions(input, n);

    // Free the dynamically allocated memory
    free(input);

    return 0;
}
