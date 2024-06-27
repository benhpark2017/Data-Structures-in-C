/**Solution to Horowitz's Data Structures Chapter 7 Section 3 Exercise 4.
 * This is a dynamic linked list implementation of the insert sort function.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list_node *listPtr;

typedef struct list_node {
    int listValue;
    listPtr link;
} node;

listPtr head = NULL; // Pointer to the first record of the linked list

void activeInsertionSort(); // Insertion sort

int main() {
    listPtr freeLink;

    activeInsertionSort(); // Perform insertion sort to create the dynamic linked list

    // Display the values of the allocated list and free memory
    while (head != NULL) {
        freeLink = head;
        printf("--> %d ", head->listValue);
        head = head->link;
        free(freeLink);
    }
    printf("\n");

    return 0;
}

void activeInsertionSort() {
    int inputValue;
    listPtr record, tempPtr, preTempPtr;

    do {
        printf("Enter a number to perform sorting. (Enter a negative number to end input): ");
        scanf("%d", &inputValue);

        if (inputValue < 0) // If the input is negative, exit the loop to end input
            break;

        // Allocate memory for the record
        record = (listPtr)malloc(sizeof(node));
        record->listValue = inputValue; // Assign the input value to the record
        record->link = NULL; // Assign NULL to the record's link

        if (head == NULL) // If there is no link to head's value
            head = record;
        else if (head->listValue > record->listValue) // If there's only one linked value
        {
            record->link = head;
            head = record;
        } else {
            tempPtr = head;

            while (tempPtr->listValue < record->listValue) {
                preTempPtr = tempPtr;
                tempPtr = tempPtr->link;

                if (tempPtr == NULL)
                    break;
            }

            record->link = preTempPtr->link;
            preTempPtr->link = record;
        }
    } while (1);
}



