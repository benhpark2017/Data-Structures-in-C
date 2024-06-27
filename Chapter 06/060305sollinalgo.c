/**Solutions to Chapter 6, Section 3, Exercise 5 of Horowitz's Data Structures
 * in C.
 */

#include <stdio.h>
#include <string.h> /* for memcpy(), memset() */

#define TRUE 1
#define FALSE 0
#define VERTICES 6 /* maximum size of vertex */

/* Structure to represent edge weight */
typedef struct {
    int from;
    int to;
    int cost;
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

/* Function prototypes */
void sollin(int edges[][VERTICES], int n);
void union2(int *parent, int i, int j);
int find(int *parent, int i);

/* Minimum spanning tree */
edge_weight Minspantree[VERTICES - 1];

int main() {
    int i, totalcost = 0; /* Spanning tree's cost */

    sollin(cost, VERTICES);

    printf("Vertex 1\tVertex 2\tCost\n");
    for (i = 0; i < VERTICES - 1; i++) {
        totalcost += Minspantree[i].cost;
        printf("%5d\t\t%5d\t\t%3d\n", Minspantree[i].from, Minspantree[i].to, Minspantree[i].cost);
    }
    printf("\nMinimum cost using Sollin's algorithm = %d\n", totalcost);

    return 0;
}

/* Sollin's algorithm implementation */
void sollin(int edges[][VERTICES], int n) {
    edge_weight edgelist[VERTICES]; /* Set of selected edges */
    edge_weight mincost, select; /* Minimum cost and selected struct */
    int edgecount = 0; /* Number of selected edges */
    int i, j, k, l = 0;
    int root, fromroot, toroot; /* Root of each forest */
    int group[VERTICES]; /* Group of each node */
    int parent[VERTICES]; /* Parent nodes */

    /* Initialize arrays */
    memset(group, -1, sizeof(group));
    memset(parent, -1, sizeof(parent));

    while (edgecount < n - 1) {
        /* Select minimum cost for each group */
        for (i = 0; i < VERTICES; i++) {
            if (group[i] < 0) {
                root = i; /* Find root */
                mincost.cost = 9999;

                for (j = 0; j < VERTICES; j++) {
                    /* Find minimum cost among members of the root's group */
                    if ((group[j] == root) || (j == root)) {
                        for (k = 0; k < VERTICES; k++) {
                            if ((mincost.cost > edges[j][k]) && edges[j][k]) {
                                mincost.from = j;
                                mincost.to = k;
                                mincost.cost = edges[j][k];
                            }
                        }
                    }
                }

                /* Remove duplicate edges and add to list */
                edges[mincost.from][mincost.to] = FALSE;
                if (edges[mincost.to][mincost.from]) {
                    memcpy(&edgelist[l++], &mincost, sizeof(edge_weight));
                }
            }
        }

        while (l > 0) {
            memcpy(&select, &edgelist[--l], sizeof(edge_weight));

            /* Check if roots of both vertices are different */
            if ((fromroot = find(parent, select.from)) != (toroot = find(parent, select.to))) {
                memcpy(&group, &parent, sizeof(parent));
                union2(parent, fromroot, toroot); /* Union of two sets */
                memcpy(&Minspantree[edgecount++], &select, sizeof(edge_weight));
                edges[select.to][select.from] = FALSE;
            }
        }
    }
}

/* Union operation */
void union2(int *parent, int i, int j) {
    /* Use weighting rule to merge two sets with roots i and j (i != j) */
    /* parent[i] = -count[i] and parent[j] = -count[j] */
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) {
        parent[i] = j; /* Make j the new root */
        parent[j] = temp;
    } else {
        parent[j] = i; /* Make i the new root */
        parent[i] = temp;
    }
}

/* Find operation */
int find(int *parent, int i) {
    /* Find the root containing element i */
    /* Use collapsing rule to collapse all nodes from i to the root */
    int root, trail, lead;
    for (root = i; parent[root] >= 0; root = parent[root]);
    for (trail = i; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
}

