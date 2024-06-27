/**Solutions to Horowitz's Fundamnetals of Data Structures, Chapter 8, Section 2, 
 * Exercises 2 and 3. 
 */

// Implementing a hash table using chaining with singly linked lists
#include <stdio.h>
#include <stdlib.h> // for memory allocation

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; // total length of buckets

// Declaration of node structure
struct node {
    int key; // key used for hash function
    int value; // data held by the key
    struct node* next; // pointer to the next node
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

    return newNode;
}

// Creating a hash function. Here, simply creating the function by taking the remainder of the key divided by the bucket size.
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
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

// Function to remove a key
void removeKey(int key){
    int hashIndex = hashFunction(key);
    int flag = 0;
    struct node* node = hashTable[hashIndex].head;
    struct node* before = NULL; // Initialize before to NULL
    while (node != NULL)
    {
        if (node->key == key){
            if (node == hashTable[hashIndex].head){
                hashTable[hashIndex].head = node->next;
            }
            else{
                before->next = node->next;
            }
            hashTable[hashIndex].count--;
            free(node);
            flag = 1;
            break; // Exit the loop after removing the key
        }
        before = node;
        node = node->next;
    }
    if (flag == 1){
        printf("\n [ %d ] was deleted. \n", key);
    }
    else{
        printf("\n [ %d ] does not exist, so deletion failed.\n", key);
    }
}

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
    if (flag == 1) printf("\n Key is [ %d ], value is [ %d ]. \n", node->key, node->value);
    else printf("\n The key does not exist.\n");
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
            printf("(key : %d, val : %d)  -> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main() {
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
