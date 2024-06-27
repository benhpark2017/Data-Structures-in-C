/**Solutions to Chapter 3, Section 2, Exercise 1 of Horowitz's
 * Data Structures in C.*/

#define MAX_QUEUE_SIZE 100

typedef struct{
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int isEmptyQueue(){
    return (rear == front);
}

int isFullQueue(){
    return (rear == MAX_QUEUE_SIZE);
}
void addQueue(int *rear, element item){
    if (*rear == MAX_QUEUE_SIZE - 1){
        queueFull();
        return;
    } else
    queue(++*rear) = item;
}

element deleteQueue(int *front, int rear){
    if (*front == rear) queueEmpty();
    else return queue(++*front);
}

void queueEmpty(){
    fprintf(stderr, "The queue is empty.\n");
}

void queueFull(){
    fprintf(stderr, "The queue is full.\n");
}
