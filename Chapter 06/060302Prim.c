/**Solutions to Chapter 6, Section 3, Exercise 2 of Horowitz's Data
 * Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 8 // Adjusted to include vertices from 1 to 7
#define INT_MAX 1000

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

// Structure to represent an edge in the MST
typedef struct MSTEdge {
    int src, dest, weight;
} MSTEdge;

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
    for (int i = 1; i <= V; ++i)
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

// Function to find the vertex with the minimum key value,
// from the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Function to print MST edges and their weights
void printMSTEdges(MSTEdge mst[], int V) {
    int totalWeight = 0;
    printf("Edges added to MST:\n");
    for (int i = 1; i < V - 1; i++) {
        printf("Edge %d-%d added to MST (Weight: %d)\n", mst[i].src, mst[i].dest, mst[i].weight);
        totalWeight += mst[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

// Function to construct MST using Prim's algorithm and return the total weight
int primMST(Graph* graph, MSTEdge mst[]) {
    int V = graph->V;
    int parent[V+1]; // Array to store constructed MST
    int key[V+1];    // Key values used to pick minimum weight edge in cut
    bool mstSet[V+1]; // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 1; i <= V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex
    key[1] = 0;
    parent[1] = -1; // First node is always root of MST

    int totalWeight = 0;

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);

        // Add the picked vertex to the MST set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        ListNode* crawl = graph->array[u].head;
        while (crawl != NULL) {
            int v = crawl->dest;

            // Update the key only if weight of edge u-v is smaller than the current key of v
            if (mstSet[v] == false && crawl->weight < key[v]) {
                parent[v] = u;
                key[v] = crawl->weight;
            }

            crawl = crawl->next;
        }
    }

    // Construct MST edges
    for (int i = 2; i <= V; i++) {
        mst[i-1].src = parent[i];
        mst[i-1].dest = i;
        mst[i-1].weight = key[i];
        totalWeight += key[i];
    }

    return totalWeight;
}

int main(void) {
    Graph* graph = createGraph(MAX_NODES);
    MSTEdge mst[MAX_NODES];

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

    // Perform Prim's algorithm to find MST
    int totalWeight = primMST(graph, mst);

    // Print MST edges and their weights
    printMSTEdges(mst, graph->V);

    return 0;
}
