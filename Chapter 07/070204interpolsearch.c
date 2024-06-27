/**Solutions to Chapter 7, Section 2, Exercise 4 of Horowitz's Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_SIZE 20

typedef struct {
    int key;
    // add other fields as needed
} element;

element list[MAX_SIZE];
element exponList[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
                       2048, 4096, 8192, 16384, 32768, 65536, 
                       131072, 262144, 524288, 1048576};

void shuffle(element arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        element temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void bubbleSort(element list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].key > list[j + 1].key) {
                element temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

int binarySearch(element list[], int searchnum, int n) {
    int left = 0;
    int right = n - 1;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;
        printf("Debug: left = %d, right = %d, middle = %d\n", left, right, middle);
        switch (COMPARE(list[middle].key, searchnum)) {
            case -1: left = middle + 1; break;
            case 0: return middle;
            case 1: right = middle - 1; break;
        }
    }

    return -1;
}

int interpolationSearch(element list[], int searchnum, int n) {
    int low = 0;
    int high = n - 1;
    int mid;

    while ( (list[low].key != list[high].key) 
             && (searchnum >= list[low].key) 
             && (searchnum <= list[high].key) ) {
        mid = low + ((searchnum - list[low].key) * (high - low))
                    / (list[high].key - list[low].key);

        if (list[mid].key < searchnum)
            low = mid + 1;
        else if (list[mid].key > searchnum)
            high = mid - 1;
        else
            return mid;
    }

    if (searchnum == list[low].key)
        return low;
    else
        return -1; // Not found
}


int main() {
    srand(time(0));

    // Initialize the array with unique numbers
    for (int i = 0; i < MAX_SIZE; i++) {
        list[i].key = i; // Initialize each element's key field with a unique number
    }

    // Shuffle the array
    shuffle(list, sizeof(list) / sizeof(int));
    
    int result_binary;
    int result_interpol;
    int result_Expon;
    int searchnum;
    int searchnumExpon;
    
    // Print the shuffled array
    for (int i = 0; i < sizeof(list) / sizeof(int); i++)
        printf("list[%d].key is %d\n", i, list[i].key);
    
    bubbleSort(list, sizeof(list) / sizeof(int));
    // Print the sorted array
    for (int i = 0; i < MAX_SIZE; i++)
        printf("list[%d].key is %d\n", i, list[i].key);
    
    printf("Please enter a number to search: \n");
    scanf("%d", &searchnum);
    result_binary = binarySearch(list, searchnum, MAX_SIZE);
    result_interpol = interpolationSearch(list, searchnum, MAX_SIZE);

    if (result_binary >= 0) 
        printf("By binary search, list[%d].key has been found in %d\n",
                result_binary, list[result_binary].key);
    else printf("The desired number does not exist in the list[] array.\n");
    
    if (result_interpol >= 0) 
        printf("By interpolation, list[%d].key has been found in %d\n",
                result_interpol, list[result_interpol].key);
    else printf("The desired number does not exist in the list[] array.\n");
    
    //shuffle(exponList, sizeof(exponList) / sizeof(int) );
    
    printf("Please enter a number to search: \n");
    scanf("%d", &searchnumExpon);
    result_Expon = interpolationSearch(exponList, searchnumExpon, 
                                          sizeof(exponList) / sizeof(int));
    
    for (int i = 0; i < sizeof(exponList) / sizeof(int); i++)
        printf("Exponential list exponList[%d].key is %d\n", i, exponList[i].key);
    
    if (result_Expon >= 0) 
        printf("By interpolation, The exponential list exponlist[%d].key "
               "has been found in %d\n",
                result_Expon, list[result_Expon].key);
    else printf("The desired number does not exist in the list[] array.\n");
    return 0;
}
