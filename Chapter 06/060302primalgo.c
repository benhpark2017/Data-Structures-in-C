/**Solutions to Chapter 6, Section 3, Exercise 2 of Fundamentals of Horowitz's
 * Data Structures in C.
 */

#include <stdio.h>
#include <string.h> /* for memcpy() */

#define TRUE 1
#define FALSE 0
#define VERTICES 6 /* maximum size of vertex */

/* Structure to represent edge weight */
typedef struct {
    int from; /* vertex 1 */
    int to; /* vertex 2 */
    int cost; /* cost of edge */
} edge_weight;

/* Adjacency matrix for cost */
int cost[VERTICES][VERTICES] = {
    {9999, 5, 4, 9999, 9999, 9999},
    {5, 9999, 2, 7, 9999, 9999},
    {4, 2, 9999, 6, 11, 9999},
    {9999, 7, 6, 9999, 3, 8},
    {9999, 9999, 11, 3, 9999, 8},
    {9999, 9999, 9999, 8, 8, 9999}
};

/* Minimum cost spanning tree */
edge_weight minspantree[VERTICES - 1];

/* Prim's algorithm function prototype */
void prim(int alledge[][VERTICES], int start);

int main() {
    int i, totalcost = 0;

    /* Start with vertex 0 and no edges */
    prim(cost, 0);

    printf("Vertex 1\tVertex 2\tCost\n");
    for (i = 0; i < VERTICES - 1; i++) {
        totalcost += minspantree[i].cost;
        printf("%5d\t\t%5d\t\t%3d\n", minspantree[i].from, minspantree[i].to, minspantree[i].cost);
    }
    printf("\nMinimum cost using Prim's algorithm = %d\n", totalcost);

    return 0;
}

/* Prim's algorithm implementation */
void prim(int alledge[][VERTICES], int start) {
    int i;
    int count = 0; /* Count of edges in the tree */
    edge_weight mincost;
    int nearest[VERTICES]; /* Set of nearest vertices for each vertex */
    int distance[VERTICES]; /* Minimum cost between vertices */

    /* Initialize arrays */
    for (i = 0; i < VERTICES; i++) {
        nearest[i] = start;
        distance[i] = alledge[i][0];
    }
    distance[start] = FALSE;

    while (count < VERTICES - 1) {
        mincost.cost = 9999; /* Set to a large value initially */
        for (i = 0; i < VERTICES; i++) {
            /* Find the nearest neighbor with minimum cost */
            if (distance[i] && mincost.cost > distance[i]) {
                mincost.cost = distance[i];
                mincost.from = i;
                mincost.to = nearest[i];
            }
        }
        distance[mincost.from] = FALSE; /* Mark the selected vertex as visited */
        for (i = 0; i < VERTICES; i++) {
            /* Update distances to other vertices if a cheaper path is found */
            if (distance[i] > alledge[i][mincost.from]) {
                distance[i] = alledge[i][mincost.from];
                nearest[i] = mincost.from;
            }
        }
        if (mincost.cost == 9999)
            break; /* No spanning tree found */
        memcpy(&minspantree[count++], &mincost, sizeof(edge_weight));
    }
    if (count < VERTICES - 1)
        printf("No spanning tree exists\n");
}

