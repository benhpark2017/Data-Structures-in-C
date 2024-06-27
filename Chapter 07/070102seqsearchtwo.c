/**Solution to Horowitz Chapter 7, Section 1, Exercise 2 on p.324.
 * 
 */
#include <stdio.h>

int rightShiftRecord(int list[], int searchnum, int n);

int main() {
    int searchnum, print_counter = 0;
    int list[] = {3, 6, 9, 4, 2, 7, 5};
    
    printf("Please enter to search for a number: ");
    scanf("%d", &searchnum);
    
    rightShiftRecord(list, searchnum, sizeof(list)/sizeof(int));
    
    while (print_counter < sizeof(list)/sizeof(int)) {
        printf("list[%d] = %d\n", print_counter, list[print_counter]);
        ++print_counter;
    }
    
    return 0;
}

int rightShiftRecord(int list[], int searchnum, int n) {
    int counter, rightShift;
    
    for (counter = 0; list[counter] != searchnum; counter++)
        ; //for loop for sequential search
    
    if (counter < n) {
        for (rightShift = counter - 1; counter; counter--, rightShift--)
            list[counter] = list[rightShift]; // move entry by one space to the right
        
        list[counter] = searchnum;
        return 0;
    }
    else // if searchnum is not in the list array
        return -1;
}

