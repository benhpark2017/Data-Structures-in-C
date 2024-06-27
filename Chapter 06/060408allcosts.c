/**Solution to Horowitz Chapter 6 Section 4 Exercise 8.
 * Program that shows allowed paths and costs (distance lengths)
 * with all costs available for source and destination nodes.
 * The allcosts() function has been appropriately modified
 * to fit the requirements of the problem.*/
 
#include <stdio.h>
#include <limits.h> /*for INT_MAX*/
#include <stdlib.h> /*for malloc(), free()*/
#define FALSE 0
#define TRUE 1
#define INF 100000
#define MAX_VERTICES 8 /*maximum size of vertex*/

/*Node structure*/
/*Structure that contains shortest distance between two connected nodes*/
typedef struct node {
    int vertex;
    struct node *link;
} node;
typedef struct node *node_pointer;
/*경로를 저장하기 위한 구조체 포인터 배열*/
node_pointer path[MAX_VERTICES][MAX_VERTICES];
int cost[][MAX_VERTICES] = {{0, INF, INF, INF, INF, INF, INF, INF},
                            {300, 0, INF, INF, INF, INF, INF, INF},
                            {1000, 800, 0, INF, INF, INF, INF, INF},
                            {INF, INF, 1200, 0, INF, INF, INF, INF},
                            {INF, INF, INF, 1500, 0, 250, INF, INF},
                            {INF, INF, INF, 1000, INF, 0, 900, 1400},
                            {INF, INF, INF, INF, INF, INF, 0, 1000},
                            {1700, INF, INF, INF, INF, INF, INF, 0}};
                            
void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n);
void free_memory(node_pointer *ptr);
int distance[MAX_VERTICES][MAX_VERTICES];
short int found[MAX_VERTICES];
int n = MAX_VERTICES;

void main() {
    int i, j;
    node_pointer temp;
    printf( "\t\t   Floyd-Warshall's algorithm\n");
    printf( "\t++++ List of allowed paths showing all costs ++++\n");
    allcosts(cost, distance, n);
    
    printf("\tpath\t\t\tcost\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2d->%2d : ", i, j);
            for (temp = path[i][j]; temp; temp = temp->link)
                if (path[i][j] && distance[i][j] < INF)
                    printf("V%d ", temp->vertex);
            if (!path[i][j] || distance[i][j] >= INF)
                printf("No path exists.\n");
            else
                printf("V%d \t\tcost: %6d\n", j, distance[i][j]);
            /*free memory allocated to pointers*/
            free_memory(&path[i][j]);
        }
        printf("\n");
    }
}

void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n) {
    /* Calculate the distance from each vertex to all other vertices */
    /* cost is the adjacency matrix, distance is the matrix of distance values */
    int i, j, k;
    node_pointer temp, ptr, next;

    /* Initialize the distance matrix */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            distance[i][j] = cost[i][j];
        }
    }

    /* Floyd-Warshall algorithm to calculate shortest paths */
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                /* Add the starting vertex to the path if it's not already present and if there's a path */
                if ((!path[i][j]) && (distance[i][j] != 1000) && (distance[i][j] != 0)) {
                    temp = (node_pointer)malloc(sizeof(struct node));
                    temp->vertex = i;
                    temp->link = NULL;
                    path[i][j] = temp;
                }

                /* Update the shortest path if a shorter path via vertex k is found */
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    /* Free the memory of the existing path */
                    free_memory(&path[i][j]);

                    /* Copy the path from i to k */
                    for (ptr = path[i][k]; ptr; ptr = ptr->link) {
                        temp = (node_pointer)malloc(sizeof(struct node));
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        if (!path[i][j])
                            path[i][j] = next = temp;
                        else {
                            next->link = temp;
                            next = next->link;
                        }
                    }

                    /* Append the path from k to j */
                    for (ptr = path[k][j]; ptr; ptr = ptr->link) {
                        temp = (node_pointer)malloc(sizeof(struct node));
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        next->link = temp;
                        next = next->link;
                    }

                    /* Update the distance */
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

void free_memory(node_pointer *ptr) {
    node_pointer trail;
    while (*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}
