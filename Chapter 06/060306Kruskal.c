/**Solutions to Chapter 6, Section 3, Exercise 6 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent an edge in the graph
typedef struct Edge {
    int src, dest, weight;
} Edge;

// Structure to represent a node in the adjacency list
typedef struct ListNode {
    int dest;
    int weight;
    struct ListNode* next;
} ListNode;

// Structure to represent the adjacency list
typedef struct List {
    ListNode* head;
} List;

// Structure to represent the graph
typedef struct Graph {
    int V; // Number of vertices
    List* array; // Array of adjacency lists
} Graph;

// Function to create a new adjacency list node
ListNode* newListNode(int dest, int weight) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (List*)malloc(V * sizeof(List));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    ListNode* newNode = newListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Helper function to compare two edges based on weight
int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Helper function to find the parent of a node in the union-find algorithm
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Helper function to perform union operation in the union-find algorithm
void unionParent(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Function to perform Kruskal's algorithm
void kruskalMST(Graph* graph) {
    // Allocate memory for the MST
    Edge* result = (Edge*)malloc((graph->V - 1) * sizeof(Edge));
    int* parent = (int*)malloc(graph->V * sizeof(int));

    // Sort all the edges in non-decreasing order of their weight
    int e = 0;
    for (int i = 0; i < graph->V; ++i) {
        ListNode* curr = graph->array[i].head;
        while (curr) {
            int dest = curr->dest;
            int weight = curr->weight;
            if (i < dest) {
                result[e].src = i;
                result[e].dest = dest;
                result[e].weight = weight;
                ++e;
            }
            curr = curr->next;
        }
    }

    qsort(result, e, sizeof(Edge), compare);

    // Initialize parent array
    for (int i = 0; i < graph->V; ++i)
        parent[i] = i;

    int mstWeight = 0; // Total weight of MST
    int edgeCount = 0; // Number of edges included in MST
    int i = 0;

    // Find MST using Kruskal's algorithm
    while (edgeCount < graph->V - 1 && i < e) {
        Edge nextEdge = result[i++];
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            mstWeight += nextEdge.weight;
            ++edgeCount;
            unionParent(parent, x, y);
            printf("Edge %d-%d added to MST (Weight: %d)\n", 
                   nextEdge.src, nextEdge.dest, nextEdge.weight);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
}


int main(void) {
    Graph* graph = createGraph(MAX_NODES);

    // Add edges to the graph
    addEdge(graph, 1, 7, 12);
    addEdge(graph, 1, 4, 28);
    addEdge(graph, 1, 2, 67);
    addEdge(graph, 1, 5, 17);
    addEdge(graph, 2, 4, 24);
    addEdge(graph, 2, 5, 62);
    addEdge(graph, 3, 5, 20);
    addEdge(graph, 3, 6, 37);
    addEdge(graph, 4, 7, 13);
    addEdge(graph, 5, 6, 45);
    addEdge(graph, 5, 7, 73);

    // Perform Kruskal's algorithm to find MST
    kruskalMST(graph);

    return 0;
}

