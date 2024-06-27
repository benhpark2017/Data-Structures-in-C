/**Solutions to Chapter 6, Section 4, Exercise 2 of Horowitz's Data
 * Structures in C.
 *
 * The specification asks for a rewritten shortestpath() function
 * so that it generates the paths as well as the distances for
 * each of the shortest paths.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 8
#define FALSE 0
#define TRUE 1
#define INF 1000000

/* Node structure */
struct node {
    int vertex;
    struct node *link;
};
typedef struct node *node_pointer; /* Node pointer */

/* Array to store paths */
node_pointer path[MAX_VERTICES] = {NULL}; // Initialize path array with NULL pointers

/* Cost matrix as shown in Figure 6.30 of the Horowitz textbook*/
int cost[MAX_VERTICES][MAX_VERTICES] = {
    {0, INF, INF, INF, INF, INF, INF, INF},
    {300, 0, INF, INF, INF, INF, INF, INF},
    {1000, 800, 0, INF, INF, INF, INF, INF},
    {INF, INF, 1200, 0, INF, INF, INF, INF},
    {INF, INF, INF, 1500, 0, 250, INF, INF},
    {INF, INF, INF, 1000, INF, 0, 900, 1400},
    {INF, INF, INF, INF, INF, INF, 0, 1000},
    {1700, INF, INF, INF, INF, INF, INF, 0}
};

// Global variables
int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int n = MAX_VERTICES;

// Function prototypes
int choose(int distance[], int n, short found[]);
void shortestpath(int v, int cost[][MAX_VERTICES], int distance[], 
                  int n, short int found[]);
void free_memory(node_pointer *ptr);

int main() {
    int i, j;
    node_pointer temp;
    printf("++++ Shortest Path ++++\n\n");
    printf("\tpath\t\t\tcost\n");
    /* Loop through all vertices to find paths and minimum costs */
    for (i = 0; i < n; i++) {
        shortestpath(i, cost, distance, n, found);
        for (j = 0; j < n; j++) {
            printf("%2d->%2d : ", i, j);
            if (path[j] && distance[j] < 1000000) { // Check if a path exists
                temp = path[j];
                while (temp) {
                    printf("V%d ", temp->vertex);
                    temp = temp->link;
                }
                printf("V%d\t\t\t%d\n", j, distance[j]);
            } else {
                printf("No path exists.\n");
            }
            free_memory(&path[j]); // Free memory associated with this vertex
        }
    }
    return 0;
}

/* Free memory function */
void free_memory(node_pointer *ptr){
    node_pointer trail;
    while (*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}

/* Function to choose the next vertex with the minimum distance */
int choose(int distance[], int n, short int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

/* Function to find shortest paths from vertex v */
void shortestpath(int v, int cost[][MAX_VERTICES], int distance[],
                  int n, short int found[]) {
    int i, u, w;
    node_pointer ptr, temp, next;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0; i < n - 1; i++) {
        u = choose(distance, n, found);
        found[u] = TRUE;
        if (!path[u] && !(distance[u] == 1000)) {
            temp = (node_pointer)malloc(sizeof(struct node)); // Corrected allocation
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            temp->vertex = v;
            temp->link = NULL;
            path[u] = temp;
        }
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                    free_memory(&path[w]); // Free memory associated with this vertex
                    if (path[w]) path[w] = NULL; // Reset the path pointer
                    for (ptr = path[u]; ptr; ptr = ptr->link) {
                        temp = (node_pointer)malloc(sizeof(struct node)); // Corrected allocation
                        if (temp == NULL) {
                            printf("Memory allocation failed.\n");
                            exit(EXIT_FAILURE);
                        }
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        if (!path[w]) path[w] = next = temp;
                        else {
                            next->link = temp;
                            next = next->link;
                        }
                    }
                    temp = (node_pointer)malloc(sizeof(struct node)); // Corrected allocation
                    if (temp == NULL) {
                        printf("Memory allocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                    temp->vertex = u;
                    temp->link = NULL;
                    next->link = temp;
                }
            }
        }
    }
}
