/** Solution to Horowitz's Data Structures Chapter 7, Section 4, Exercise 4.
 *  For each record finding its appropriate place we can partition the file into
 *  the following portions to obtain an inequality below:
 *  T(n) <= cn + 2T(n/2), for some constant c.
 *       <= cn + 2(cn/2 + 2T(n/4))
 *       <= 2cn + 4T(n/4)
 * .
 * .
 *       <= cn log n + nT(1) = O(n log n) 이다 (여기서 log는 로그2 를 뜻함.)
 *
 * For an already sorted list of entries, quicksort, an algorithm which uses the
 * medium of threes are split into almost identically large portions, so the above
 * inequality holds.
 * Therefore, the quicksort that uses median of threes has a time complexity of
 * O(n log2 n).
 */
/** Solution to Horowitz's Data Structures Chapter 7, Section 4, Exercise 3.
 *  For each record finding its appropriate place we can partition the file into
 *  the following portions to obtain an inequality below:
 *  T(n) <= cn + 2T(n/2), for some constant c.
 *       <= cn + 2(cn/2 + 2T(n/4))
 *       <= 2cn + 4T(n/4)
 *       <= cn log n + nT(1) = O(n log2 n). 
 *
 * For an already sorted list of entries, quicksort, an algorithm which uses the
 * medium of threes are split into almost identically large portions, so the above
 * inequality holds.
 * Therefore, the quicksort that uses median of threes has a time complexity of
 * O(n log2 n).
 */

#include <stdio.h>

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

void iterativeQuickSort(int arr[], int left, int right) {
    int stack[right - left + 1]; // Stack for storing subarray boundaries
    int top = -1;

    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        if (left < right) {
            int pivotIndex = median(arr, left, right);
            int pivot = arr[pivotIndex];
            int i = left;
            int j = right;

            while (i <= j) {
                while (arr[i] < pivot)
                    i++;
                while (arr[j] > pivot)
                    j--;

                if (i <= j) {
                    swap(&arr[i], &arr[j]);
                    i++;
                    j--;
                }
            }

            if (left < j) {
                stack[++top] = left;
                stack[++top] = j;
            }

            if (i < right) {
                stack[++top] = i;
                stack[++top] = right;
            }
        }
    }
}

/** If you want to type in your own array, use the commented code:
int main() {
    int *list, input_num, counter;
    printf("Enter the number of elements to be sorted: ");
    scanf("%d", &input_num);
    list = (int *)malloc(sizeof(list) * input_num);
    for (counter = 0; counter < input_num; ++counter) {
        printf("Please input entry number %d: ", counter + 1);
        scanf("%d", list + counter);
    }
    quicksort(list, 0, input_num - 1);
    for (counter = 0; counter < input_num; ++counter)
        printf("The %dth number is %d.\n", counter + 1, *(list + counter));
    return 0;
}
*/

int main() {
    int arr[] = {6, 4, 5, 7, 8, 2, 3, 9, 1, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    iterativeQuickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
