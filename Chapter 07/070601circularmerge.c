/**Solution to Horowitz's Data Structure Chapter 7 Section 6 Exercise 1.
 * This program shifts the records x_0, x_1, x_2, ... x_(n-1) circularly
 * right by p positions, where p is an integer between 0 and n, the
 * number of records. 
 */

#include <stdio.h>
#define MAX_SIZE 20

void swap(int *one, int *the_other);
void reverse(int list[], int start, int end);
void p_shift(int list[], int shift_pos);

int main() {
    int shift_position, counter;
    int list[MAX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    
    printf("Enter the number of positions to shift: ");
    scanf("%d", &shift_position);
    
    p_shift(list, shift_position);

    printf("Shifted array:\n");
    for (counter = 0; counter < MAX_SIZE; counter++)
        printf(" %d", list[counter]);
    printf("\n");
    
    return 0;
}

void p_shift(int list[], int shift_pos) {
    int n = MAX_SIZE;
    shift_pos %= n; // Ensure shift_pos is within array bounds

    if (shift_pos == 0)
        return; // No shift needed
    
    reverse(list, 0, n - shift_pos - 1);
    reverse(list, n - shift_pos, n - 1);
    reverse(list, 0, n - 1);
}

void reverse(int list[], int start, int end) {
    while (start < end) {
        swap(&list[start], &list[end]);
        start++;
        end--;
    }
}

void swap(int *one, int *the_other) {
    int temp;
    temp = *one;
    *one = *the_other;
    *the_other = temp;
}

