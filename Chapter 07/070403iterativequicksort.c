/**Solutions to Chapter 7, Section 4, Exercise 3 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 1000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int median(int arr[], int left, int right) {
    int center = (left + right) / 2;

    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    if (arr[left] > arr[right])
        swap(&arr[left], &arr[right]);
    if (arr[center] > arr[right])
        swap(&arr[center], &arr[right]);

    return center;
}


void iterative_quicksort(int *list, int left, int right) {
    int beg[MAX_LEVELS], end[MAX_LEVELS], L, R;
    int i = 0;

    beg[0] = left;
    end[0] = right;
    while (i >= 0) {
        L = beg[i];
        R = end[i];
        if (L + 1 < R--) {
            int piv = list[L];
            while (L < R) {
                while (list[R] >= piv && L < R)
                    R--;
                if (L < R)
                    list[L++] = list[R];
                while (list[L] <= piv && L < R)
                    L++;
                if (L < R)
                    list[R--] = list[L];
            }
            list[L] = piv;
            if (L - beg[i] > end[i] - R) { 
                beg[i + 1] = L + 1;
                end[i + 1] = end[i];
                end[i++] = L;
            } else {
                beg[i + 1] = beg[i];
                end[i + 1] = L;
                beg[i++] = L + 1;
            }
        } else {
            i--;
        }
    }
}

int main() {
    int arr[] = {6, 4, 14, 5, 12, 7, 13, 8, 2, 3, 11, 9, 1, 10, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    iterative_quicksort(arr, 0, n - 1);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

