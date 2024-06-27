/**Solution to Chapter 6, Section 4, Exercise 8 of Horowitz's
 * Data Structures in C textbook.
 */

#include <stdio.h>
#include <limits.h> /* for INT_MAX */
#include <stdlib.h> /* for malloc(), free() */

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 6 /* maximum size of vertex */

/* Structure for representing each vertex's shortest path */
typedef struct node *node_pointer;
struct node {
    int vertex;
    node_pointer link;
};

/* Pointer array to store paths */
node_pointer path[MAX_VERTICES][MAX_VERTICES];

/* Cost matrix */
int cost[][MAX_VERTICES] = {
    {0, 50, 10, 1000, 45, 1000},
    {1000, 0, 15, 1000, 10, 1000},
    {20, 1000, 0, 15, 1000, 1000},
    {1000, 20, 1000, 0, 35, 1000},
    {1000, 1000, 1000, 30, 0, 1000},
    {1000, 1000, 1000, 3, 1000, 0}
};

/* Function prototypes */
void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n);
void free_memory(node_pointer *ptr);

/* Distance matrix */
int distance[MAX_VERTICES][MAX_VERTICES];

/* Array to keep track of found vertices */
short int found[MAX_VERTICES];

int n = MAX_VERTICES;

void main() {
    int i, j;
    node_pointer temp;

    printf("\t++++ All costs ++++\n");
    allcosts(cost, distance, n);

    printf("\tpath\t\t\tcost\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2d->%2d : ", i, j);

            for (temp = path[i][j]; temp; temp = temp->link)
                printf("V%d ", temp->vertex);

            if (!path[i][j])
                printf("No path exists.\n");
            else
                printf("V%d\n\t\t\t\t%d\n", j, distance[i][j]);

            /* Free memory used */
            free_memory(&path[i][j]);
        }
        printf("\n\n\n");
    }
}

/* Calculate all costs */
void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n) {
    int i, j, k;
    node_pointer temp, ptr, next;

    /* Initialize distance matrix with cost matrix */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            distance[i][j] = cost[i][j];
    }

    /* Floyd-Warshall algorithm to find shortest paths */
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                /* If a cheaper path is found */
                if ((!path[i][j]) && (distance[i][j] != 1000) && (distance[i][j] != 0)) {
                    /* Add starting vertex to path */
                    temp = (node_pointer) malloc(sizeof(struct node));
                    temp->vertex = i;
                    temp->link = NULL;
                    path[i][j] = temp;
                }
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    /* Free previous path if a cheaper path is found */
                    free_memory(&path[i][j]);

                    /* Reconstruct path */
                    for (ptr = path[i][k]; ptr; ptr = ptr->link) {
                        temp = (node_pointer) malloc(sizeof(struct node));
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        if (!path[i][j])
                            path[i][j] = next = temp;
                        else {
                            next->link = temp;
                            next = next->link;
                        }
                    }
                    for (ptr = path[k][j]; ptr; ptr = ptr->link) {
                        temp = (node_pointer) malloc(sizeof(struct node));
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        next->link = temp;
                        next = next->link;
                    }
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

/* Free memory used by a linked list */
void free_memory(node_pointer *ptr) {
    node_pointer trail;
    while (*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}


