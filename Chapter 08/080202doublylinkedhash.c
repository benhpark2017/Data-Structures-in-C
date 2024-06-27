/**Solutions to Chapter 8, Section 2, Exercises 2 and 3 of Horowitz's
 * Data Structures in C.*/
// Implementing a hash table using chaining with doubly linked lists
#include <stdio.h>
#include <stdlib.h> // for memory allocation

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; // total length of buckets

// Declaration of node structure
struct node {
    int key; // key used for hash function
    int value; // data held by the key
    struct node* next; // pointer to the next node
    struct node* previous; // pointer to the previous node
};
// Declaration of bucket structure
struct bucket{
    struct node* head; // pointer to the first node of the bucket
    int count; // number of nodes in the bucket
};
// Function to create a new node when inserting into the hash table (initialization)
struct node* createNode(int key, int value){
    struct node* newNode;
    // memory allocation
    newNode = (struct node *)malloc(sizeof(struct node));
    // assigning the values provided by the user
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL; // initialize next to NULL during creation
    newNode->previous = NULL; // initialize previous to NULL during creation

    return newNode;
}
/**Creating a hash function. Here, we are simply creating the function by taking the
 * remainder of the key divided by the bucket size.*/
int hashFunction(int key){
    return key % BUCKET_SIZE;
}
// Function to add a new key
void add(int key, int value){
    // calculate the index where to add
    int hashIndex = hashFunction(key);
    // create a new node
    struct node* newNode = createNode(key, value);
    // if there are no nodes in the calculated index of the bucket
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; // replace head
    }
    // if there are other nodes in the bucket, shift them one by one and set myself as the head (actually just change the pointers)
    else{
        hashTable[hashIndex].head->previous = newNode; // add
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}
// Function to remove a key
void removeKey(int key){
    int hashIndex = hashFunction(key);
    // flag to check if the deletion is successful
    int flag = 0;
    // iterator to find the key
    struct node* node;
    // struct node* before; // not needed!
    // start from the head of the bucket
    node = hashTable[hashIndex].head;
    // traverse the bucket to find the key
    while (node != NULL) // until NULL is reached
    {
        if (node->key == key){
            // updating pointers - if the node is 1. head or 2. not head
            if (node == hashTable[hashIndex].head){
                node->next->previous = NULL; // add, now the next becomes the head so there's no previous
                hashTable[hashIndex].head = node->next; // the next node becomes the head
            }
            else{
                node->previous->next = node->next; // the previous node's next becomes my next node
                node->next->previous = node->previous; // my next node's previous becomes my previous node
            }
            // perform remaining operations
            hashTable[hashIndex].count--;
            free(node);
            flag = 1;
        }
        node = node->next;
    }
    // print differently based on the value of flag
    if (flag == 1){ // if deletion is successful
        printf("\n [ %d ] was deleted. \n", key);
    }
    else{ // if the key doesn't exist and deletion failed
        printf("\n [ %d ] does not exist, so deletion failed.\n", key);
    }
}
// Function to find the value when given a key
void linearSearch(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;
    int flag = 0;
    while (node != NULL)
    {
        if (node->key == key){
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 1){ // if the key is found
        printf("\n Key is [ %d ], value is [ %d ]. \n", node->key, node->value);
    }
    else{
        printf("\n The key does not exist.\n");
    }
}
// Function to display the entire hash table
void display(){
    // iterator declaration
    struct node* iterator;
    printf("\n========= display start ========= \n");
    for (int i = 0; i < BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key : %d, val : %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    // allocate memory for the hash table
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    
    // add values up to 15
    for (int i = 0; i < 16; i++){
        add(i, 10 * i);
    }
    // add a few more
    add(21, 210);
    add(31, 310);
    add(41, 410);

    display();

    removeKey(31);
    removeKey(11);
    removeKey(51);

    display();

    linearSearch(11);
    linearSearch(1);
}
