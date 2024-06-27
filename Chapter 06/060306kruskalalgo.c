/**Solutions to Chapter 6, Section 3, Exercise 6 of Horowitz's Data Structures
 * in C.
 */

#include <stdio.h>
#include <string.h> /* for memset(), memcpy() */

#define VERTICES 6 /* maximum size of vertex */
#define NUMEDGE 9 /* maximum size of edge */

/* Struct prototype */
typedef struct {
    int from;
    int to;
    int cost;
} edge_weight;

/* Heap sort array */
edge_weight edgelist[NUMEDGE + 1];

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
/* Heap sort functions */
void heapsort_MinHeap(edge_weight list[], int n);
void adjust_MinHeap(edge_weight list[], int root, int n);
edge_weight delete_MinHeap(edge_weight *heap, int *n);
/* Kruskal function */
void kruskal(edge_weight E[]);
void union2(int *parent, int i, int j);
int find(int *parent, int i);
/* Minimum cost spanning tree */
edge_weight minspantree[VERTICES - 1];

int main() {
    int i, j, k = 1;
    int totalcost = 0;

    /* Add existing edges to the list */
    for (i = 0; i < VERTICES - 1; i++) {
        for (j = i + 1; j < VERTICES; j++) {
            if (cost[i][j] != 9999) {
                edgelist[k].cost = cost[i][j];
                edgelist[k].from = i;
                edgelist[k].to = j;
                k++;
            }
        }
    }

    /* Heap sorting */
    heapsort_MinHeap(edgelist, NUMEDGE - 1);

    /* Call Kruskal's algorithm */
    kruskal(edgelist);

    printf("Vertex 1\tVertex 2\tCost\n");
    for (i = 0; i < VERTICES - 1; i++) {
        totalcost += minspantree[i].cost;
        printf("%5d\t\t%5d\t\t%3d\n", minspantree[i].from, minspantree[i].to, minspantree[i].cost);
    }
    printf("\nMinimum cost using Kruskal's algorithm: %d\n", totalcost);

    return 0;
}

/* Kruskal's algorithm implementation */
void kruskal(edge_weight Edgelist[]) {
    int fromroot, toroot; /* Root of each vertex */
    int e = NUMEDGE; /* Number of edges */
    int v = 0; /* Number of vertices */
    int T[VERTICES];
    int l = 0;
    edge_weight select;
    
    memset(T, -1, sizeof(T));

    /* T has n-1 edges and E is not empty */
    while (e > 0 && v < VERTICES - 1) {
        /* Select and delete the edge with the lowest cost from E */
        select = delete_MinHeap(Edgelist, &e);
        
        /* If roots of the vertices are different, union them */
        if ((fromroot = find(T, select.from)) != (toroot = find(T, select.to))) {
            union2(T, fromroot, toroot); /* Pass the root values of each element */
            memcpy(&minspantree[l++], &select, sizeof(edge_weight));
            ++v;
        }
    }

    if (v < VERTICES - 1)
        printf("No spanning tree exists\n");
}

/* Union operation for sets */
void union2(int *parent, int i, int j) {
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}

/* Find operation for sets */
int find(int *parent, int i) {
    int root, trail, lead;
    for (root = i; parent[root] >= 0; root = parent[root]);
    for (trail = i; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
}

/* Heap sorting */
void heapsort_MinHeap(edge_weight list[], int n) {
    int i;
    edge_weight temp;

    /* Adjust the heap */
    for (i = n / 2; i > 0; i--)
        adjust_MinHeap(list, i, n);

    /* Extract elements from the heap */
    for (i = n - 1; i > 0; i--) {
        temp = list[1];
        list[1] = list[i + 1];
        list[i + 1] = temp;
        adjust_MinHeap(list, 1, i);
    }
}

/* Adjust the heap */
void adjust_MinHeap(edge_weight list[], int root, int n) {
    int rootkey, child;
    edge_weight temp;
    
    temp = list[root];
    rootkey = list[root].cost;
    child = 2 * root;

    while (child <= n) {
        if ((child < n) && (list[child].cost < list[child + 1].cost))
            child++;
        if (rootkey > list[child].cost)
            break;
        else {
            list[child / 2] = list[child];
            child *= 2;
        }
    }
    list[child / 2] = temp;
}

/* Delete an element from the heap */
edge_weight delete_MinHeap(edge_weight *heap, int *n) {
    int parent, child;
    edge_weight item, temp;
    
    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;

    while (child <= *n) {
        if ((child < *n) && (heap[child].cost > heap[child + 1].cost))
            child++;
        if (temp.cost <= heap[child].cost)
            break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;

    return item;
}

