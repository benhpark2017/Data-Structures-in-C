/**Solutions to Chapter 5, Section 13, Exercise 3 of Horowitz's Data
 * Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50

// Node structure for storing information about each word
typedef struct Node {
    char word[MAX_WORD_LENGTH];
    int occurrences;
    int *lines;
    struct Node *next;
} Node;

// Function to compare nodes for sorting alphabetically
int compareNodes(const void *a, const void *b) {
    return strcmp(((Node *)a)->word, ((Node *)b)->word);
}

// Function to add a word to the cross-reference list
void addWord(Node **head, char *word, int lineNumber) {
    // Convert the word to lowercase and ignore punctuations, hyphens, and quotes
    char cleanWord[MAX_WORD_LENGTH];
    int cleanIndex = 0;
    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            cleanWord[cleanIndex++] = tolower(word[i]);
        }
    }
    cleanWord[cleanIndex] = '\0';

    // Check if the cleaned word is not empty
    if (cleanIndex > 0) {
        // Check if the word already exists in the list
        Node *current = *head;
        while (current != NULL) {
            if (strcmp(current->word, cleanWord) == 0) {
                // Word found, update occurrences and add the line number
                current->occurrences++;
                current->lines = realloc(current->lines, current->occurrences * sizeof(int));
                current->lines[current->occurrences - 1] = lineNumber;
                return;
            }
            current = current->next;
        }

        // If the word is not in the list, add it
        Node *newNode = (Node *)malloc(sizeof(Node));
        strncpy(newNode->word, cleanWord, MAX_WORD_LENGTH - 1);
        newNode->word[MAX_WORD_LENGTH - 1] = '\0';
        newNode->occurrences = 1;
        newNode->lines = (int *)malloc(sizeof(int));
        newNode->lines[0] = lineNumber;
        newNode->next = *head;
        *head = newNode;
    }
}

void bubbleSort(Node *arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j]->word, arr[j + 1]->word) > 0) {
                // If arr[j] comes after arr[j+1] alphabetically, swap them
                Node *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printCrossReference(Node *head) {
    // Count the number of nodes
    int nodeCount = 0;
    Node *current = head;
    while (current != NULL) {
        nodeCount++;
        current = current->next;
    }

    // Create an array of nodes for sorting
    Node **nodeArray = (Node **)malloc(nodeCount * sizeof(Node *));
    current = head;
    for (int i = 0; i < nodeCount; i++) {
        nodeArray[i] = current;
        current = current->next;
    }

    // Sort the array of nodes alphabetically (any other sorting algorithm is fine)
    bubbleSort(nodeArray, nodeCount);

    // Print the sorted cross-reference list
    for (int i = 0; i < nodeCount; i++) {
        printf("%s: %d occurrences (lines: ", nodeArray[i]->word, nodeArray[i]->occurrences);
        for (int j = 0; j < nodeArray[i]->occurrences; j++) {
            printf("%d", nodeArray[i]->lines[j]);
            if (j < nodeArray[i]->occurrences - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    // Free the array of nodes
    free(nodeArray);
}

// Function to free memory allocated for the cross-reference list
void freeCrossReference(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->lines);
        free(temp);
    }
}

// Function to count unique words in the input file
int uniqueWordCount(Node *head) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->occurrences == 1) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main() {
    FILE *file;
    char input[1000];
    Node *crossReference = NULL;
    int lineNumber = 1;

    // Open the file for reading
    if ((file = fopen("gettysburg.txt", "r")) == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read input line by line
    while (fgets(input, sizeof(input), file) != NULL) {
        // Tokenize the line into words
        char *token = strtok(input, " \t\n");
        while (token != NULL) {
            // Add each word to the cross-reference list
            addWord(&crossReference, token, lineNumber);
            token = strtok(NULL, " \t\n");
        }

        lineNumber++;
    }

    // Close the file
    fclose(file);

    // Print the cross-reference list in alphabetical order
    printCrossReference(crossReference);

    // Count the number of unique words and kinds of unique words
    int totalUniqueWords = uniqueWordCount(crossReference);

    printf("\nTotal kinds of unique words: %d\n", totalUniqueWords);

    // Free memory allocated for the cross-reference list
    freeCrossReference(crossReference);

    return 0;
}

