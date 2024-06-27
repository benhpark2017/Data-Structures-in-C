/**Solution to Horowitz's Data Structures, Chapter 7, Section 3, Exercise 3*/

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPtr;

typedef struct listNode {
    int listValue;
    listPtr link;
} node;

listPtr head = NULL; // Pointer to the first record of the linked list

void insertionSort(int list[], int insertValue, int lastArrayNum); // Insertion sort
int changeLinkedList(int list[], int listNumber); // Convert sorted lists to linked lists

int main() {
    int inputNumber, inputCounter, printCounter;
    listPtr freeLink;
    int *list;

    printf("Enter the number of records to be sorted: ");
    scanf("%d", &inputNumber);

    list = (int *)malloc(sizeof(int) * inputNumber);

    for (inputCounter = 0; inputCounter < inputNumber; ++inputCounter) {
        printf("Enter record %d: ", inputCounter);
        scanf("%d", list + inputCounter);
        insertionSort(list, *(list + inputCounter), inputCounter);
    }

    for (printCounter = 0; printCounter < inputNumber; ++printCounter)
        printf("list[%d] = %d \n", printCounter, list[printCounter]);
    printf("\n");

    changeLinkedList(list, inputNumber);

    while (head != NULL) {
        freeLink = head;
        printf("--> %d ", head->listValue);
        head = head->link;
        free(freeLink);
    }
    printf("\n");

    free(list);

    return 0;
}

void insertionSort(int list[], int insertValue, int lastArrayNum) {
    int insertPosition, shiftArrayNum;

    for (insertPosition = 0; (insertPosition < lastArrayNum) && (list[insertPosition] < insertValue); ++insertPosition);

    for (shiftArrayNum = lastArrayNum; shiftArrayNum > insertPosition ; --shiftArrayNum)
        list[shiftArrayNum] = list[shiftArrayNum - 1];

    list[insertPosition] = insertValue;
}

int changeLinkedList(int list[], int listNumber) {
    int linkCounter;
    listPtr linkedList;

    linkedList = (listPtr)malloc(sizeof(node));
    linkedList->listValue = list[listNumber - 1];
    linkedList->link = NULL;

    if (listNumber < 2) {
        head = linkedList;
        return 0;
    }

    for (linkCounter = listNumber - 2; linkCounter >= 0; --linkCounter) {
        head = linkedList;
        linkedList = (listPtr)malloc(sizeof(node));
        linkedList->listValue = list[linkCounter];
        linkedList->link = head;
    }

    head = linkedList;

    return 0;
}
