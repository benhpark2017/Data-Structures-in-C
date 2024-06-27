/**A program that prints the graph based on the adjacency list
 * using depth-first search and breadth-first search algorithms.
 * This code is the solution to Chapter 6, Section 2, Exercises
 * 1 and 2 of Horowitz's Data Structure text on p.282. 
 */

#include <stdio.h>
#include <string.h> /* for memset() */
#include <stdlib.h> /* for exit() */

#define TRUE 1
#define MAX_VERTICES 8 /* maximum size of vertex */

int adj_matrix[][MAX_VERTICES] = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 1, 1, 0}
};

/* queue array */
int queue[MAX_VERTICES];

/* global queue variables, initialize queue */
int front = -1;
int rear = -1;

/* arrays to track visited vertices */
short int dfs_visited[MAX_VERTICES];
short int bfs_visited[MAX_VERTICES];

/* function prototypes */
void dfs(int v);
void bfs(int v);
void addq(int *rear, int vertex);
int deleteq(int *front, int rear);

int main() {
    /* initialize arrays with zeros */
    memset(&dfs_visited, 0, sizeof(dfs_visited));
    memset(&bfs_visited, 0, sizeof(bfs_visited));

    printf("---------- Depth First Search (DFS) Algorithm ----------\n");
    dfs(0);

    printf("\n\n---------- Breadth First Search (BFS) Algorithm ----------\n");
    bfs(0);

    printf("\n\n");

    return 0;
}

/* Depth First Search (DFS) */
void dfs(int v) {
    /* Recursive DFS starting from vertex v */
    int i;
    dfs_visited[v] = TRUE;
    printf("%5d", v);
    for (i = 0; i < MAX_VERTICES; i++) {
        /* If vertex i is not visited and there is an edge from v to i */
        if (!dfs_visited[i] && adj_matrix[v][i])
            dfs(i);
    }
}

/* Breadth First Search (BFS) */
void bfs(int v) {
    /* BFS starting from vertex v */
    int i;
    printf("%5d", v);
    bfs_visited[v] = TRUE;
    addq(&rear, v);
    while (1) {
        /* Remove vertex from queue */
        v = deleteq(&front, rear);
        for (i = 0; i < MAX_VERTICES; i++) {
            /* If vertex i is not visited and there is an edge from v to i */
            if (!bfs_visited[i] && adj_matrix[v][i]) {
                printf("%5d", i);
                addq(&rear, i);
                bfs_visited[i] = TRUE;
            }
        }
        /* If queue is empty, terminate */
        if (front == rear)
            break;
    }
}

/* Add element to the queue */
void addq(int *rear, int vertex) {
    if (*rear == MAX_VERTICES - 1) {
        fprintf(stderr, "Queue is full\n");
        exit(1);
    }
    queue[++*rear] = vertex;
}

/* Delete element from the queue */
int deleteq(int *front, int rear) {
    if (*front == rear) {
        fprintf(stderr, "Queue is empty");
        exit(1);
    }
    return queue[++*front];
}

