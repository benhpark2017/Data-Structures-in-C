/**Solution to Chapter 8, Section 2, Exercise 13 of Horowitz's Data Structures in C
 * Create a menu-driven, user-friendly program that manages the supply list of
 * Widgets, Inc. Widgets, Inc. keeps the following information on their supplies:
 * 5-digit part number (the key), 10-character description of the parts, re-order
 * level, and the size of the current inventory. One must maintain the supply list
 * using a chained hash table. In addition, the users of the program must be able
 * to perform the following operations.
 * a) add a new part to the inventory
 * b) delete a part form the inventory
 * c) search for a part
 * d) change the key field of a part
 * e) change any of the remaining fields.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for string operations

#define BUCKET_SIZE 10
#define DESCRIPTION_LENGTH 11 // 10 characters + null terminator

// Structure for a part in the inventory
struct part {
    int partNumber; // 5-digit part number
    char description[DESCRIPTION_LENGTH]; // 10-character description
    int depthLevel; // depth level in the bucket of hash table
    int inventorySize; // size of the current inventory
    struct part* next; // pointer to the next part
};

// Structure for a node in the linked list
struct node {
    struct part* data; // data held by the node
    struct node* next; // pointer to the next node
};

// Structure for a bucket in the hash table
struct bucket {
    struct node* head; // pointer to the first node of the bucket
    int count; // number of nodes in the bucket
};

// Global hash table declaration
struct bucket* hashTable = NULL;

// Function to create a new part
struct part* createPart(int partNumber, const char* description, int depthLevel, int inventorySize) {
    struct part* newPart = (struct part*)malloc(sizeof(struct part));
    if (newPart != NULL) {
        newPart->partNumber = partNumber;
        strncpy(newPart->description, description, DESCRIPTION_LENGTH - 1);
        newPart->description[DESCRIPTION_LENGTH - 1] = '\0'; // Ensure null-termination
        newPart->depthLevel = depthLevel;
        newPart->inventorySize = inventorySize;
        newPart->next = NULL;
    }
    return newPart;
}

// Function to create a new node
struct node* createNode(struct part* data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to calculate hash index
int hashFunction(int partNumber) {
    return partNumber % BUCKET_SIZE;
}

// Function to add a new part to the inventory
void addPart(int partNumber, const char* description, int depthLevel, int inventorySize) {
    int hashIndex = hashFunction(partNumber);
    struct part* newPart = createPart(partNumber, description, depthLevel, inventorySize);
    struct node* newNode = createNode(newPart);

    if (hashTable[hashIndex].head == NULL) {
        hashTable[hashIndex].head = newNode;
    } else {
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
    }
    hashTable[hashIndex].count++;
}

// Function to remove a part from the inventory
void removePart(int partNumber) {
    int hashIndex = hashFunction(partNumber);
    struct node* current = hashTable[hashIndex].head;
    struct node* previous = NULL;
    
    while (current != NULL) {
        if (current->data->partNumber == partNumber) {
            if (previous == NULL) {
                hashTable[hashIndex].head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->data);
            free(current);
            hashTable[hashIndex].count--;
            printf("Part with part number %d removed.\n", partNumber);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Part with part number %d not found.\n", partNumber);
}

// Function to search for a part in the inventory
void searchPart(int partNumber) {
    int hashIndex = hashFunction(partNumber);
    struct node* current = hashTable[hashIndex].head;

    while (current != NULL) {
        if (current->data->partNumber == partNumber) {
            printf("Part found - Part Number: %d, Description: %s, Depth Level: %d, Inventory Size: %d\n",
                   current->data->partNumber, current->data->description, current->data->depthLevel, current->data->inventorySize);
            return;
        }
        current = current->next;
    }
    printf("Part with part number %d not found.\n", partNumber);
}

//Function to change the part number of a part
void changePartNumber(int old_partNumber, int new_partNumber) {
    
    // Search for the part with the old part number, 
    // clone it with the new part number, and add it back to the inventory
    // (This step assumes that you want to change the part number and keep other fields the same)
    int hashIndex = hashFunction(old_partNumber);
    struct node* current = hashTable[hashIndex].head;

    while (current != NULL) {
        if (current->data->partNumber == old_partNumber) {
            addPart(new_partNumber, current->data->description, current->data->depthLevel, current->data->inventorySize);
            return;
        }
        current = current->next;
    }
    printf("Part with part number %d not found.\n", old_partNumber);
}

// Function to change any of the remaining fields of a part
void changePartFields(int partNumber, const char* new_description, int new_depthLevel, int new_inventorySize) {
    int hashIndex = hashFunction(partNumber);
    struct node* current = hashTable[hashIndex].head;

    while (current != NULL) {
        if (current->data->partNumber == partNumber) {
            strncpy(current->data->description, new_description, DESCRIPTION_LENGTH - 1);
            current->data->description[DESCRIPTION_LENGTH - 1] = '\0'; // Ensure null-termination
            current->data->depthLevel = new_depthLevel;
            current->data->inventorySize = new_inventorySize;
            printf("Fields of part with part number %d updated.\n", partNumber);
            return;
        }
        current = current->next;
    }
    printf("Part with part number %d not found.\n", partNumber);
}

// Function to display the entire hash table
void displayInventory() {
    printf("Inventory:\n");
    for (int i = 0; i < BUCKET_SIZE; i++) {
        struct node* current = hashTable[i].head;
        printf("Bucket %d:\n", i);
        while (current != NULL) {
            printf("Part Number: %d, Description: %s,"
                   " Depth Level: %d, Inventory Size: %d\n",
                   current->data->partNumber,
                   current->data->description,
                   current->data->depthLevel,
                   current->data->inventorySize
            );
            current = current->next;
        }
    }
}

int main() {
    // Allocate memory for the hash table
    hashTable = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));
    if (hashTable == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Exit with error
    }

    // Initialize the hash table
    for (int i = 0; i < BUCKET_SIZE; i++) {
        hashTable[i].head = NULL;
        hashTable[i].count = 0;
    }

    int choice;
    int partNumber;
    char description[DESCRIPTION_LENGTH];
    int depthLevel;
    int inventorySize;
    int old_partNumber;
    int new_partNumber;
    char new_description[DESCRIPTION_LENGTH];
    int new_depthLevel;
    int new_inventorySize;

    // Main loop to continuously ask the user for actions
    while (1) {
        printf("Please select an option:\n");
        printf("1. Add a new part to the inventory\n");
        printf("2. Delete a part from the inventory\n");
        printf("3. Search for a part\n");
        printf("4. Change the key field of a part\n");
        printf("5. Change any of the remaining fields\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter part number: ");
                scanf("%d", &partNumber);
                printf("Enter description (up to 10 characters): ");
                scanf("%s", description);
                printf("Enter depth level: ");
                scanf("%d", &depthLevel);
                printf("Enter inventory size: ");
                scanf("%d", &inventorySize);
                addPart(partNumber, description, depthLevel, inventorySize);
                break;
            case 2:
                printf("Enter part number to delete: ");
                scanf("%d", &partNumber);
                removePart(partNumber);
                break;
            case 3:
                printf("Enter part number to search: ");
                scanf("%d", &partNumber);
                searchPart(partNumber);
                break;
            case 4:
                printf("Enter old part number: ");
                scanf("%d", &old_partNumber);
                printf("Enter new part number: ");
                scanf("%d", &new_partNumber);
                changePartNumber(old_partNumber, new_partNumber);
                break;
            case 5:
                printf("Enter part number: ");
                scanf("%d", &partNumber);
                printf("Enter new description (up to 10 characters): ");
                scanf("%s", new_description);
                printf("Enter new depth level: ");
                scanf("%d", &new_depthLevel);
                printf("Enter new inventory size: ");
                scanf("%d", &new_inventorySize);
                changePartFields(partNumber, new_description, new_depthLevel, new_inventorySize);
                break;
            case 6:
                printf("Exiting program...\n");
                // Free allocated memory
                for (int i = 0; i < BUCKET_SIZE; i++) {
                    struct node* current = hashTable[i].head;
                    while (current != NULL) {
                        struct node* temp = current;
                        current = current->next;
                        free(temp->data);
                        free(temp);
                    }
                }
                free(hashTable);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

