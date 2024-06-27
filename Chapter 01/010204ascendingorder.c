/**Solution to Chapter 1, Section 2, Exercise 4 of Horowitz's Data Structures
 * in C. */

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);
void printArray(int arr[], int size);

int main() {
    // Example usage
    int numberOfIntegers;

    // Get input from the user
    printf("Enter the number of integers: ");
    scanf("%d", &numberOfIntegers);

    int *arr = (int*)malloc(numberOfIntegers*sizeof(int));

    // Check if memory allocation is successful
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;  // Exit with an error code
    }

    // Get integers from the user
    printf("Enter %d integers:\n", numberOfIntegers);
    for (int i = 0; i < numberOfIntegers; i++) {
        scanf("%d", &arr[i]);
    }

    // Call the recursive quicksort function
    quicksort(arr, 0, numberOfIntegers - 1);

    // Display the sorted array
    printf("Integers in ascending order: ");
    printArray(arr, numberOfIntegers);

    free(arr);
    return 0;
}

// Function to perform a recursive quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the index of the pivot
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the subarrays on either side of the pivot
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Function to partition the array and return the index of the pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i+1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
