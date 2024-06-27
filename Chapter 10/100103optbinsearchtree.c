/**Solutions to Chapter 10, Section 1, Exercise 3 of Horowitz's Data Structures.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define MAX_SIZE 200 //max number of ids plus 1
#define MAX_CHAR  30 //max characters / id

// set of identifiers
char words[MAX_SIZE][MAX_CHAR];
int q[MAX_SIZE];
int p[MAX_SIZE];
int cost[MAX_SIZE][MAX_SIZE];
int root[MAX_SIZE][MAX_SIZE];
int weight[MAX_SIZE][MAX_SIZE];
int n; // number of identifiers

// Define your binary tree structure
typedef struct TreeNode {
    char *word;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void obst(int p[], int q[], 
          int cost[][MAX_SIZE], int root[][MAX_SIZE],
          int weight[][MAX_SIZE], int n);

int knuth_min(int cost[][MAX_SIZE], int root[][MAX_SIZE], int i, int j);

void printInorder(TreeNode *root);

TreeNode* constructBST(int i, int j);

//driver code
int main() {
    srand(time(NULL)); // Seed for random number generation
    n = 12; // Number of identifiers (change as needed)

    // Example initialization of words array
    for (int i = 0; i < n; ++i) {
        sprintf(words[i], "Word%d", i); // Words are "Word0", "Word1", ...
    }

    // Example initialization of q array (frequency of searches)
    for (int i = 0; i < n; ++i) {
        q[i] = rand() % 100 + 1; // Random frequency between 1 and 100
    }

    // Example initialization of p array (frequency of unsuccessful searches)
    for (int i = 0; i < n + 1; ++i) {
        p[i] = rand() % 100 + 1; // Random frequency between 1 and 100
    }

    // Calculate cost and root matrices
    obst(p, q, cost, root, weight, n);

    // Construct binary search tree
    TreeNode* root_node = constructBST(0, n - 1);

    // Print inorder traversal of the constructed tree
    printf("In-order traversal of constructed BST: \n");
    printInorder(root_node);
    printf("\n");
    
    return 0;
}

//Correct!!
TreeNode* constructBST(int i, int j) {
    if (i == j) { // Base case: only one element to construct
        // Allocate memory for the current node
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->word = words[i];
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (i > j) // Base case: no elements to construct
        return NULL;

    int root_index = root[i][j]; // Root index in the words array

    // Allocate memory for the current node
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->word = words[root_index];
    node->left = constructBST(i, root_index - 1); // Construct left subtree
    node->right = constructBST(root_index + 1, j); // Construct right subtree

    return node;
}

// Function to print the inorder traversal of the tree (for demonstration)
void printInorder(TreeNode* root) {
    if (root) {
        printInorder(root->left);
        printf("%s ", root->word);
        printInorder(root->right);
    }
}

void obst(int p[], int q[], 
          int cost[][MAX_SIZE], int root[][MAX_SIZE],
          int weight[][MAX_SIZE], int n) {
    int i, j, k, m, min, minpos;
    for (i = 0; i < n; i++) {
        weight[i][i] = q[i];
        root[i][i] = 0;
        cost[i][i] = 0;
        cost[i][i + 1] = weight[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        root[i][i + 1] = i + 1;
    }
    weight[n][n] = q[n];
    root[n][n] = 0;
    cost[n][n] = 0;
    for (m = 2; m <= n; m++)
        for (i = 0; i < n - m; i++) {
            j = i + m;
            weight[i][j] = weight[i][j - 1] + p[j] + q[j];
            k = knuth_min(cost, root, i, j);
            cost[i][j] = weight[i][j] + cost[i][k - 1] + cost[k][j];
            root[i][j] = k;
        }
}

int knuth_min(int cost[][MAX_SIZE], int root[][MAX_SIZE], int i, int j) {
    int k;
    int min_cost = INT_MAX; // Initialize with maximum possible value
    int min_k;

    for (k = root[i][j - 1]; k <= root[i + 1][j]; k++) {
        int current_cost = cost[i][k - 1] + cost[k][j];
        if (current_cost < min_cost) {
            min_cost = current_cost;
            min_k = k;
        }
    }
    return min_k;
}

