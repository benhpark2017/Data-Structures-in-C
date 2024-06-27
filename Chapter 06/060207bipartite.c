/**Solutions to Chapter 6, Section 2, Exercise 7 of Horowitz's Data
 * Structures in C.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 8

typedef struct node *node_pointer;
struct node {
    int vertex;
    node_pointer link;
};

node_pointer graph[MAX_VERTICES];
int matrix[][MAX_VERTICES] = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0},
};

int partition[MAX_VERTICES];
int first;

void make_lists(node_pointer *headnode);
void bipartite(int next, int prev);

int main() {
    int i;
    make_lists(graph);
    memset(&partition, 0, sizeof(partition));
    first = 0;
    bipartite(first, -1);

    printf("Set A[] = {");
    for (i = 0; i < MAX_VERTICES; i++) {
        if (partition[i] == 1)
            printf("%2d", i);
    }
    printf(" }\n");

    printf("Set B[] = {");
    for (i = 0; i < MAX_VERTICES; i++) {
        if (partition[i] == 2)
            printf("%2d", i);
    }
    printf(" }\n");

    return 0;
}

void bipartite(int u, int prev) {
    node_pointer ptr;
    int w;

    for (ptr = graph[u]; ptr; ptr = ptr->link) {
        if (prev == -1)
            partition[u] = 1;
        w = ptr->vertex;
        if (w == prev)
            continue;
        if (partition[w]) {
            if (partition[u] == partition[w]) {
                fprintf(stderr, "--> This graph isn't a bipartite graph!\n");
                exit(1);
            }
        } else {
            partition[w] = partition[u] > 1 ? 1 : 2;
            bipartite(w, u);
        }
    }

    if (u == first) {
        for (w = 0; w < MAX_VERTICES; w++) {
            if (!partition[w])
                bipartite(w, -1);
        }
    }
}

void make_lists(node_pointer *headnode) {
    node_pointer element, temp;
    node_pointer *ptr;
    int i, j;

    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            if (matrix[i][j]) {
                element = (node_pointer)malloc(sizeof(struct node));
                element->vertex = j;
                element->link = NULL;
                ptr = &headnode[i];

                if (!(*ptr))
                    *ptr = element;
                else {
                    for (temp = *ptr; temp->link; temp = temp->link);
                    temp->link = element;
                }
            }
        }
    }
}
