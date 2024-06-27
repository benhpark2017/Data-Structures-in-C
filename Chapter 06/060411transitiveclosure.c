/**Solutions to Horowitz p.303, Chapter 6 Section 4, Exercises 11 and 12.
 * The program computes the reflexive transitive and transitive closures 
 * of an undirected graph with n vertices in O(n^2) time. The program
 * begins with the adjacency matrix of the graph and obtaining its
 * connected components.
 */

#include <stdio.h>

#define MAX_VERTICES 8 // maximum size of vertex

// Figure 6.5 Graph
int adj_matrix[][MAX_VERTICES] = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0}
};

short int visited[MAX_VERTICES]; // array to check visited vertices
int transitive[MAX_VERTICES][MAX_VERTICES];

// initialize function
void init();
// connected component
void dfs(int v, int c);
void connected(void);
void re_trans_closure();
void trans_closure();

int n = MAX_VERTICES;

void main() {
    int i, j;
    init();
    trans_closure();
    printf("== Transitive closure ==\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            printf("%3d", transitive[i][j]);
        printf("\n");
    }
    init();
    re_trans_closure();
    printf("\n\n== Reflexive Transitive closure ==\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            printf("%3d", transitive[i][j]);
        printf("\n");
    }
}

// If there is a path from i to j with length > 0, then A+[i][j]=1
void trans_closure() {
    int i, j;
    connected();
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            // Same connected components have paths between each other, excluding self-loop
            if((visited[j] == visited[i]) && (i != j))
                transitive[i][j] = 1;
        }
    }
}

// If there is a path from i to j with length >= 0, then A*[i][j]=1
void re_trans_closure() {
    int i, j;
    connected();
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            // Same connected components have paths between each other
            if(visited[j] == visited[i])
                transitive[i][j] = 1;
        }
    }
}

void dfs(int v, int c) {
    int i;
    // Same connected components create the same set through c
    visited[v] = c;
    for(i = 0; i < MAX_VERTICES; i++) {
        if(!visited[i] && adj_matrix[v][i])
            dfs(i, c);
    }
}

void connected(void) {
    // Determine connected components of the graph
    int i;
    int connect = 1; // Variable to distinguish connected components
    for (i = 0; i < n; i++)
        if(!visited[i]) {
            dfs(i, connect);
            connect++; // Distinguish different connected components
        }
}

void init() {
    int i, j;
    // Initialization
    for(i = 0; i < n; i++) {
        visited[i] = 0;
        for(j = 0; j < n; j++)
            transitive[i][j] = 0;
    }
}

