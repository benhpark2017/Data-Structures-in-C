/**Horowitz 5th Ed p.301 Chapter 6 Section 4 Exercise 2.
 * This is an improved program that builds on Dijkstra's algorithm.
 * Instead of calculating the minimum distance from just vertex
 * number zero, it calculates all possible routes from vertex
 * zero to other vertices. */

#include <stdio.h>
#include <limits.h> /* for INT_MAX */
#include <stdlib.h> /* for malloc(), free() */

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 8 /* maximum size of vertex */
#define INF 10000

/* struct prototype */
typedef struct node *node_pointer; /* struct pointer */
struct node {
    int vertex;
    node_pointer link;
} node;

/* Array of pointers to store each path */
node_pointer path[MAX_VERTICES];

/* Cost matrix */
int cost[][MAX_VERTICES] = {
    {0, INF, INF, INF, INF, INF, INF, INF},
    {300, 0, INF, INF, INF, INF, INF, INF},
    {1000, 800, 0, INF, INF, INF, INF, INF},
    {INF, INF, 1200, 0, INF, INF, INF, INF},
    {INF, INF, INF, 1500, 0, 250, INF, INF},
    {INF, INF, INF, 1000, INF, 0, 900, 1400},
    {INF, INF, INF, INF, INF, INF, 0, 1000},
    {1700, INF, INF, INF, INF, INF, INF, 0}
};

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int n = MAX_VERTICES;

int choose(int distance[], int n, short found[]);
void shortest_path(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]);
void free_memory(node_pointer *ptr);

void main() {
    int i, j;
    node_pointer temp;

    printf("++++ Shortest Path ++++\n\n");
    printf("\tpath\t\t\tcost\n");

    /* Select path and minimum cost for all vertices */
    for (i = 0; i < n; i++) {
        shortest_path(i, cost, distance, n, found);
        for (j = 0; j < n; j++) {
            printf("%2d->%2d: ", i, j);
            for (temp = path[j]; temp; temp = temp->link)
                if (path[j] && distance[j] < INF)
                    printf("V%d ", temp->vertex);
            if (!path[j] || distance[j] >= INF)
                printf("No path exists.\n");
            else
                printf("V%d \t\tcost: %6d\n", j, distance[j]);
        }
        for (j = 0; j < n; j++)
            free_memory(&path[j]);
    }
}

/* Function to free allocated memory */
void free_memory(node_pointer *ptr) {
    node_pointer trail;
    while (*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}

int choose(int distance[], int n, short found[]) {
    /* Find the vertex with the minimum distance among those not yet visited */
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void shortest_path(int v, int cost[][MAX_VERTICES], int distance[], int n, short found[]) {
    /* distance[i]: shortest path from vertex v to i, found[i] = 1 when shortest path is found */
    int i, u, w;
    node_pointer ptr, temp, next;
    
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    
    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        found[u] = TRUE;
        
        if (!path[u] && !(distance[u] == 1000)) { /* Unvisited vertex */
            temp = (node_pointer)malloc(sizeof(node));
            temp->vertex = v;
            temp->link = NULL;
            path[u] = temp;
        }
        
        for (w = 0; w < n; w++)
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                    /* When the shortest path is updated from existing shortest path */
                    if (path[w]) {
                        free_memory(&path[w]); /* Delete existing path */
                    }
                    /* Input newly found paths to the vertex */
                    for (ptr = path[u]; ptr; ptr = ptr->link) {
                        temp = (node_pointer)malloc(sizeof(node));
                        temp->vertex = ptr->vertex;
                        temp->link = NULL;
                        if (!path[w])
                            path[w] = next = temp;
                        else {
                            next->link = temp;
                            next = next->link;
                        }
                    }
                    /* Input the last vertex */
                    temp = (node_pointer)malloc(sizeof(struct node));
                    temp->vertex = u;
                    temp->link = NULL;
                    next->link = temp;
                }
            }
    }
}



