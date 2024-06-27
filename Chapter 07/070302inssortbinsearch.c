/**Solutions to Chapter 7, Section 3, Exercise 2 of Horowitz's Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h> // For malloc(), free()

int binsearch(int list[], int searchnum, int n);
void insertion_sort(int list[], int start_pos, int end_pos);

int main() {
    int print_counter, input_num, input_counter, insert_pos;
    int *list;

    printf("Enter the number of elements to input: ");
    scanf("%d", &input_num);

    if (input_num < 0) {
        printf("Number of elements to input is invalid. \n");
        return -1;
    }

    // Allocate memory for the array based on the input number
    list = (int*)malloc(sizeof(int) * input_num);

    for (input_counter = 0; input_counter < input_num; ++input_counter) {
        printf("Enter the %dth number: ", input_counter);
        scanf("%d", list + input_counter);
        
        // Find insertion position using binary search
        insert_pos = binsearch(list, *(list + input_counter), input_counter);
        
        // Perform insertion sort
        insertion_sort(list, insert_pos, input_counter);
    }

    // Print the values in the list
    for (print_counter = 0; print_counter < input_num; ++print_counter)
        printf("The value of list[%d] is %d \n", print_counter, *(list + print_counter));

    // Free the allocated memory
    free(list);

    return 0;
}

// Binary search function
int binsearch(int list[], int searchnum, int n) {
    int left = 0, right = n, middle;

    while (left <= right) {
        middle = (left + right) / 2;
        
        if (list[middle] < searchnum)
            left = middle + 1;
        else if (list[middle] > searchnum)
            right = middle - 1;
        else
            return middle;
    }

    return left;
}

// Insertion sort function
void insertion_sort(int list[], int start_pos, int end_pos) {
    int insert_value, shifted_array_num;

    insert_value = list[end_pos];

    for (shifted_array_num = end_pos; shifted_array_num > start_pos ; --shifted_array_num)
        list[shifted_array_num] = list[shifted_array_num - 1];

    list[start_pos] = insert_value;
}
