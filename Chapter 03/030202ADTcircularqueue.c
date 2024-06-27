/**Solutions to Chapter 3, Section 2, Exercise 2 of Horowitz's
 * Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void queueFull(int *rear) {
    fprintf(stderr, "The queue is full.\n");
    *rear = (*rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void queueEmpty() {
    fprintf(stderr, "The queue is empty.\n");
}

// Adds an item to the queue
void addCircularQueue(element item) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        queueFull(&rear);
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

// Removes an item from the queue and puts the front element in the item
element deleteCircularQueue() {
    element item;
    if (front == rear) {
        queueEmpty();
        return item; // Return a default item in case of an error
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    item = queue[front];
    return item;
}

int main() {
    // Example usage
    element item1 = {1};
    element item2 = {2};

    addCircularQueue(item1);
    addCircularQueue(item2);

    element removedItem = deleteCircularQueue();
    printf("Removed item: %d\n", removedItem.key);

    return 0;
}

