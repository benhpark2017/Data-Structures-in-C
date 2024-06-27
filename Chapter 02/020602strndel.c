/**Solutions to Chapter 2, Section 6, Exercise 2 of Horowitz's Fundamentals of Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strndel(const char* str, int start, int length) {
    // Check if start is valid
    if (start < 0 || start >= strlen(str)) {
        fprintf(stderr, "Invalid start index\n");
        return NULL;
    }

    // Check if length is valid
    if (length < 0) {
        fprintf(stderr, "Invalid length\n");
        return NULL;
    }

    // Calculate the length of the new string after deletion
    size_t originalLength = strlen(str);
    size_t newLength = originalLength - length;

    // Allocate memory for the new string
    char* result = (char*)malloc((newLength + 1) * sizeof(char));
    if (result == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Copy characters before the start index
    strncpy(result, str, start);
    result[start] = '\0'; // Null-terminate the partial string

    // Concatenate characters after the deleted portion
    strcat(result, str + start + length);

    return result;
}

int main() {
    const char* inputString = "Hello, World!";
    int start = 7;
    int length = 5;

    char* result = strndel(inputString, start, length);

    if (result != NULL) {
        printf("Original String: %s\n", inputString);
        printf("Modified String: %s\n", result);

        // Remember to free the allocated memory
        free(result);
    }

    return 0;
}
