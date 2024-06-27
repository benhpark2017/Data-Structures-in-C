/**Solution to Chapter 7, Section 1, Exercise 1 in Horowitz p.324.*/

#include <stdio.h>

#define MAX_SIZE 1000

typedef struct {
    int key;
    //add other fields as needed
} element;

element list[MAX_SIZE];

int strainSeqSearch(int list[], int searchnum, int n);
int seqSearch(int list[], int searchnum, int n);
void swap(int *initial_value, int *search_value);

int main() {
    int searchnum, return_result, return_value, start = 0;
    int list[] = {3, 6, 9, 4, 2, 7, 5};

    printf("Please enter the number that needs to be found: ");
    scanf("%d", &searchnum);

    return_result = seqSearch(list, searchnum, sizeof(list) / sizeof(int));
    if (return_result > 0)
        printf("The position of desired number in seqSearch is list[%d].\n", return_result);
    else
        printf("The desired number is not found in seqSearch.\n");

    while (start < sizeof(list) / sizeof(int)) {
        printf("list[%d] = %d \n", start, list[start]);
        start++;
    }

    return_value = strainSeqSearch(list, searchnum, sizeof(list) / sizeof(int));
    if (return_value > 0)
        printf("The position of desired number in strainSeqSearch is list[%d].\n", return_value);
    else
        printf("The desired number is not found in strainSeqSearch.\n");

    start = 0; // Reset start for printing the list again

    while (start < sizeof(list) / sizeof(int)) {
        printf("list[%d] = %d \n", start, list[start]);
        start++;
    }

    return 0;
}

void swap(int *initial_value, int *search_value) {
    int temp;
    temp = *initial_value;
    *initial_value = *search_value;
    *search_value = temp;
}

// A function that searches list of n entries. If list[i] equals searchnum,
// the function exchanges i and list[0] and returns i.
// If searchnum is not in the list, the function returns -1.
int strainSeqSearch(int list[], int searchnum, int n) {
    int i;
    for (i = 0; list[i] != searchnum; i++);
    if (i < n) {
        swap(list, list + i);
        return i;
    } else return -1;
}

int seqSearch(int list[], int searchnum, int n) {
    int i;
    list[n] = searchnum;
    for (i = 0; list[i] != searchnum; i++);
    if (i < n) return i; 
    else return -1;
}


