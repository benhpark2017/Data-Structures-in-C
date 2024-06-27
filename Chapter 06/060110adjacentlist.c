/**Solutions to Chapter 6, Section 1, numbered exercises 10 and 11
 * of Horowitz's Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define IS_FULL(ptr) (!(ptr))


typedef struct node {
    int vertex;
    struct node *link;
};
typedef struct node *nodePtr;

nodePtr graph[MAX_VERTICES];
nodePtr inverse_graph[MAX_VERTICES];
int vertices;

void read_graph(nodePtr *head_node);
int insert_edge(nodePtr *head_node, int vertex1, int vertex2);
void inverse_adjacency_lists(int vertices);
void print_graph(nodePtr *graph);
void free_memory(nodePtr *ptr);

int main() {
    int i;

    read_graph(graph);
    printf("\n\n----- Adjacency lists -----\n");
    print_graph(graph);

    inverse_adjacency_lists(vertices);
    printf("\n\n----- Inverse Adjacency lists -----\n");
    print_graph(inverse_graph);

    for(i = 0; i < vertices; i++) {
        free_memory(&graph[i]);
        free_memory(&inverse_graph[i]);
    }

    return 0;
}

// Function to read the graph from user input
void read_graph(nodePtr *head_node) {
    int i;
    int repetition;
    int vertex, vertex1, vertex2;
    int max_edge;
    int count = 0;

    printf("Input the number of vertices (less than 50): ");
    scanf("%d", &vertices);
    max_edge = vertices * (vertices - 1) / 2;
    printf("Input ends with -1, Vertex start = 0\n");

    while(count++ < max_edge) {
        printf("Insert edge (vertex1 vertex2): ");
        scanf("%d", &vertex1);

        if(vertex1 == -1)
            break;

        scanf("%d", &vertex2);
        vertex = vertex1;
        i = 0;
        repetition = 0;

        while((i++ < 2) && !repetition) {
            if((repetition = insert_edge(&graph[vertex], vertex, vertex2))) {
                count -= 1;
            }
            vertex = vertex2;
            vertex2 = vertex1;
        }
    }
}

// Function to insert an edge into the graph
int insert_edge(nodePtr *head_node, int vertex1, int vertex2) {
    int repetition = 0;
    nodePtr element, trail, lists;

    if(!(*head_node)) {
        lists = (nodePtr)malloc(sizeof(struct node));
        lists->vertex = vertex2;
        lists->link = NULL;
        *head_node = lists;
    } else {
        for(trail = *head_node; trail; trail = trail->link) {
            element = trail;
            if(trail->vertex == vertex2) {
                printf("The edge already exists!\n");
                repetition = 1;
                break;
            }
        }
        if(!repetition) {
            lists = (nodePtr) malloc (sizeof(struct node));
            if(IS_FULL(lists)) {
                fprintf(stderr, "Memory is full.\n");
                exit(1);
            }
            lists->vertex = vertex2;
            lists->link = NULL;
            element->link = lists;
        }
    }
    return repetition;
}

// Function to create the inverse adjacency lists
void inverse_adjacency_lists(int vertices) {
    int i;
    nodePtr element;

    for (i = 0; i < vertices; i++) {
        for(element = graph[i]; element; element = element->link) {
            insert_edge(&inverse_graph[element->vertex], element->vertex, i);
        }
    }
}

// Function to print the graph
void print_graph(nodePtr *graph) {
    int i;
    nodePtr ptr;

    for(i = 0; i < vertices; i++) {
        ptr = graph[i];
        printf("Head[%d]: ", i);
        for(; ptr; ptr = ptr->link) {
            if(!(ptr->vertex == -1)) {
                printf("%4d", ptr->vertex);
            }
        }
        printf("\n");
    }
}

// Function to free memory allocated for the graph
void free_memory(nodePtr *ptr) {
    nodePtr trail;
    while(*ptr) {
        trail = *ptr;
        *ptr = (*ptr)->link;
        free(trail);
    }
}

