/**Horowitz p.302 Solution in Chapter 6 Section 4 to Exercise number 5.
 * The program is a rewritten version of shortest_path() function
 * that follows the Dijkstra algorithm. The program is a linked
 * list implementation that prints X for forbidden paths.*/

#include <stdio.h>
#include <limits.h> /* for INT_MAX */
#include <stdlib.h> /* for malloc(), free() */

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 8 /* maximum size of vertex */
#define INF 1000000

/* Structure for a node */
typedef struct node *nodePtr; /* struct pointer */
struct node {
    int vertex;
    int cost;
    nodePtr link;
};

nodePtr graph[MAX_VERTICES]; /* struct array */

/* Structure for checking whether shortest path is found */
typedef struct found *foundPtr;
struct found {
    int vertex;
    foundPtr link;
};

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
foundPtr ptrFound = NULL; /* pointer to struct for vertices not yet explored */
int n = MAX_VERTICES;

void make_lists(nodePtr *head_node);
int choose(int distance[], int n, foundPtr *ptrFound);
void shortest_path(int v, nodePtr *head_node, int distance[], int n, foundPtr *ptrFound);
void free_memory(nodePtr *ptr);

void main() {
    int i, j;
    make_lists(graph);
    for (i = 0; i < n; i++) {
        shortest_path(i, graph, distance, n, &ptrFound);
        for (j = 0; j < n; j++)
            if (distance[j] >= INF) printf("         X");
            else printf("%10d", distance[j]);
        printf("\n");
    }
}

void make_lists(nodePtr *head_node) {
    nodePtr element, temp;
    nodePtr *ptr; /* head node */
    int i, j;
    
    /* Convert adjacency matrix to linked lists */
    for (i = 0; i < MAX_VERTICES; i++)
        for (j = 0; j < MAX_VERTICES; j++) {
            element = (nodePtr)malloc(sizeof(struct node));
            element->vertex = j;
            element->cost = cost[i][j];
            element->link = NULL;
            ptr = &head_node[i];
            /* If head node is null, add to head node */
            if (!(*ptr))
                *ptr = element;
            /* Otherwise, find the last node and add to list */
            else {
                for (temp = *ptr; temp->link; temp = temp->link);
                temp->link = element;
            }
        }
}

/* Function to free allocated memory */
void free_memory(nodePtr *ptr) {
    nodePtr trail;
    while (*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}

int choose(int distance[], int n, foundPtr *ptrFound) {
    int i, min, minpos, exist;
    foundPtr ptr;
    min = INT_MAX;
    minpos = -1;
    exist = FALSE;
    for (i = 0; i < n; i++) {
        /* Traverse the list to choose the minimum cost */
        for (ptr = *ptrFound; ptr; ptr = ptr->link) {
            if (distance[ptr->vertex] < min) {
                min = distance[ptr->vertex];
                minpos = ptr->vertex;
            }
        }
    }
    return minpos;
}

void shortest_path(int v, nodePtr *head_node, int distance[], int n, foundPtr *ptrFound) {
    int i, u, w;
    nodePtr ptr;
    foundPtr lead, trail;

    /* Store all vertices except v in ptrFound list */
    for (i = 0; i < n; i++) {
        if (i == v)
            continue;
        lead = (foundPtr)malloc(sizeof(struct found));
        lead->vertex = i;
        lead->link = NULL;
        /* If ptrFound list is empty, make this vertex the head */
        if (!(*ptrFound))
            *ptrFound = trail = lead;
        /* Otherwise, add it to the end */
        else {
            trail->link = lead;
            trail = lead;
        }
    }

    /* Store costs of vertices in the list to the distance array */
    for (ptr = head_node[v], i = 0; ptr; ptr = ptr->link, i++)
        distance[i] = ptr->cost;
    distance[v] = 0;

    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, ptrFound);
        /* T = V(G) - S */
        /* If the found vertex is the head, change the head and delete it */
        if ((*ptrFound)->vertex == u) {
            lead = *ptrFound;
            *ptrFound = lead->link;
            free(lead);
        }
        /* If it's not the head, traverse the found list and delete the selected vertex */
        else {
            for (trail = *ptrFound; trail; trail = trail->link) {
                if (trail->vertex == u) {
                    lead->link = trail->link;
                    free(trail);
                    break;
                }
                lead = trail;
            }
        }
        /* Choose the vertex with minimum cost among vertices not yet traversed */
        for (lead = *ptrFound; lead; lead = lead->link) {
            w = lead->vertex;
            for (ptr = head_node[u]; ptr; ptr = ptr->link)
                if (ptr->vertex == w)
                    break;
            if (distance[u] + ptr->cost < distance[w])
                distance[w] = distance[u] + ptr->cost;
        }
    }
    free(*ptrFound);
    *ptrFound = NULL;
}
