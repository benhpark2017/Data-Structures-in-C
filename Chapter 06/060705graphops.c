/**Solutions to Chapter 6, Section 7, Exercise 5 of Horowitz's Data
 * Structures in C.*/

#include <stdio.h>
#include <stdlib.h> /* for exit(), malloc(), free() */
#include <string.h> /* for memset() */

#define TRUE 1
#define MAX_VERTICES 50 /* maximum size of vertex */
#define IS_FULL(ptr) (!(ptr)) /* stack full */
#define IS_EMPTY(ptr) (!(ptr)) /* stack empty */
#define CLEAR(arr) memset(&arr, 0, sizeof(arr)) /* initialize array */

/* for adjacency lists */
typedef struct node *node_pointer;
typedef struct node {
    int vertex;
    node_pointer link;
} node;

/* for breadth-first search, queue definition */
typedef struct queue *queue_pointer;
typedef struct queue {
    int vertex;
    queue_pointer link;
} queue;

/* for biconnected, stack definition */
typedef struct stack *stack_pointer;
typedef struct stack {
    int vertex1;
    int vertex2;
    stack_pointer link;
} stack;
stack_pointer top;

/* display menu */
void prompt();
/* depth-first search (DFS) */
void dfs(int v);
/* breadth-first search (BFS) */
void bfs(int v);
void addq(queue_pointer *, queue_pointer *, int);
int deleteq(queue_pointer *);
/* connected component */
void connected(int n);

/* determine dfn & low */
void dfnlow(int u, int v);
/* insert graph and make adjacency lists */
void read_graph(node_pointer *headnode);
int insert_graph(node_pointer *headnode, int vertex1, int vertex2);
void print_graph(node_pointer *graph);
/* biconnected graph */
void biconnected(int u, int v);
void deletes(stack_pointer *top, int *v1, int *v2);
void adds(stack_pointer *top, int v1, int v2);
/* bridge */
void bridge(int u, int v);

/* function array declaration */
node_pointer graph[MAX_VERTICES]; /* adjacency list array */
short int visited[MAX_VERTICES]; /* visited vertex check array */
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
short int articulation_point[MAX_VERTICES]; /* articulation points array */

/* global variables declaration */
int child, root; /* articulation point check of the root */
int vertices; /* number of total vertices */
int num; /* global variable to increase dfn and low */

int main() {
    char menu;
    int i;

    /* user input selection */
    while (1) {
        CLEAR(visited);
        prompt();
        printf("input menu: ");
        /* receive menu from the user */
        menu = getchar();
        printf("%c\n", menu);
        switch (menu) {
            case 'i': case 'I':
                read_graph(graph);
                break;
            case 'p': case 'P':
                print_graph(graph);
                break;
            case 'd': case 'D':
                printf("\n=== Depth first search (DFS) ===\n\n");
                dfs(0);
                printf("\n");
                break;
            case 'r': case 'R':
                printf("\n=== Breadth first search (BFS) ===\n\n");
                bfs(0);
                printf("\n");
                break;
            case 'c': case 'C':
                printf("\n ===== Connected component =====\n\n");
                connected(vertices);
                break;
            case 'a': case 'A':
                /* initialization */
                child = num = 0;
                memset(&dfn, -1, sizeof(dfn));
                memset(&low, -1, sizeof(low));
                CLEAR(articulation_point);
                printf("Enter the root: ");
                scanf("%d", &root);
                dfnlow(root, -1);
                printf("\n ===== Articulation Point =====\n");
                for (i = 0; i < vertices; i++)
                    if (articulation_point[i])
                        printf("%2d", i);
                printf("\n");
                break;
            case 'b': case 'B':
                num = 0;
                memset(&dfn, -1, sizeof(dfn));
                memset(&low, -1, sizeof(low));
                bridge(3, -1);
                break;
            case 't': case 'T':
                num = 0;
                top = NULL;
                memset(&dfn, -1, sizeof(dfn));
                memset(&low, -1, sizeof(low));
                biconnected(3, -1);
                break;
            case 'x': case 'X':
                printf("End of program.\n");
                exit(1);
        }
    }
}

/* display menu */
void prompt() {
    printf("\n============Menu============\n");
    printf("= Insert Graph : i\n");
    printf("= Print Graph : p\n");
    printf("= Depth first search (DFS) : d\n");
    printf("= Breadth first search (BFS) : r\n");
    printf("= Connected Component : c\n");
    printf("= Articulation point : a\n");
    printf("= Bridge : b\n");
    printf("= Biconnected component : t\n");
    printf("= Exit : x\n");
    printf("===============================\n");
}

/* receive vertices and edges from the user to create a graph */
void read_graph(node_pointer *headnode) {
    int i;
    int repetition; /* check for duplicate edges */
    int vertex, vertex1, vertex2; /* variables to read edges */
    int maxedge; /* maximum number of edges that can be read */
    int count = 0;
    printf("Input the number of vertices (less than 50): ");
    scanf("%d", &vertices);
    maxedge = vertices * (vertices - 1) / 2;
    printf("Input end => -1, Vertex start = 0\n");
    while (count++ < maxedge) {
        printf("Insert edge (vertex1 vertex2): ");
        scanf("%d", &vertex1);
        if (vertex1 == -1)
            break;
        scanf("%d", &vertex2);
        vertex = vertex1;
        i = 0;
        repetition = 0;
        /* since it's an undirected graph, add to both sides */
        /* if using a directed graph, remove the while loop */
        while ((i++ < 2) && !repetition) {
            if ((repetition = insert_graph(&graph[vertex], vertex, vertex2))) {
                count -= 1;
            }
            vertex = vertex2;
            vertex2 = vertex1;
        }
    }
}

/* insert a vertex with an edge into the list */
int insert_graph(node_pointer *headnode, int vertex1, int vertex2) {
    int repetition = 0;
    node_pointer element, trail, lists;
    if (!(*headnode)) {
        /* if the node is null */
        lists = (node_pointer)malloc(sizeof(node));
        lists->vertex = vertex2;
        lists->link = NULL;
        *headnode = lists;
    } else {
        for (trail = *headnode; trail; trail = trail->link) {
            /* check if the edge exists */
            element = trail;
            if (trail->vertex == vertex2) {
                printf("The edge already exists!\n");
                repetition = 1;
                break;
            }
        }
        if (!repetition) {
            /* if there is no duplicate edge, add */
            lists = (node_pointer) malloc (sizeof(node));
            if (IS_FULL(lists)) {
                fprintf(stderr, "The memory is full\n");
                exit(1);
            }
            lists->vertex = vertex2;
            lists->link = NULL;
            element->link = lists;
        } else {
            return repetition;
        }
    }
    return repetition;
}

/* determine biconnected component */
void biconnected(int u, int v) {
    /* calculate dfn and low, print edges for biconnected components of G */
    /* v is the parent of u in the result spanning tree */
    /* initialize dfn[]=-1, num=0, stack is empty */
    node_pointer ptr;
    int w, x, y;
    dfn[u] = low[u] = num++;
    for (ptr = graph[u]; ptr; ptr = ptr->link) {
        w = ptr->vertex;
        if (v != w && dfn[w] < dfn[u])
            adds(&top, u, w); /* add edge to stack */
        if (dfn[w] < 0) { /* w has not been visited */
            biconnected(w, u);
            low[u] = low[u] < low[w] ? low[u] : low[w];
            if (low[w] >= dfn[u]) {
                printf("New biconnected component: ");
                do { /* delete edge from stack */
                    deletes(&top, &x, &y);
                    printf("<%d, %d> ", x, y);
                } while (!((x == u) && (y == w)));
                printf("\n");
            }
        } else if (w != v) {
            low[u] = low[u] < low[w] ? low[u] : low[w];
        }
    }
}

/* stack operation for bicon method */
void adds(stack_pointer *top, int v1, int v2) {
    stack_pointer temp = (stack_pointer)malloc(sizeof(stack));
    if (IS_FULL(temp)) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->vertex1 = v1;
    temp->vertex2 = v2;
    temp->link = *top;
    *top = temp; /* new node is the top */
}

void deletes(stack_pointer *top, int *v1, int *v2) {
    stack_pointer temp = *top;
    if (IS_EMPTY(temp)) {
        fprintf(stderr, "The memory is empty\n");
        exit(1);
    }
    *v1 = temp->vertex1;
    *v2 = temp->vertex2;
    *top = temp->link; /* remove top node and set new top */
    free(temp);
}

/* determine bridge */
void bridge(int u, int v) {
    node_pointer ptr;
    int w;
    dfn[u] = low[u] = num++;
    for (ptr = graph[u]; ptr; ptr = ptr->link) {
        w = ptr->vertex;
        if (dfn[w] < 0) {
            bridge(w, u);
            low[u] = low[u] < low[w] ? low[u] : low[w];
            if (low[w] > dfn[u])
                printf("<%d, %d> ", u, w);
        } else if (w != v) {
            low[u] = low[u] < dfn[w] ? low[u] : dfn[w];
        }
    }
}

/* divide the edges of a connected graph into biconnected components */
void dfnlow(int u, int v) {
    node_pointer ptr;
    int w;
    dfn[u] = low[u] = num++;
    for (ptr = graph[u]; ptr; ptr = ptr->link) {
        w = ptr->vertex;
        if (dfn[w] < 0) { /* w is an unvisited vertex */
            if (v == -1) /* check if the root has more than one child */
                child++;
            dfnlow(w, u);
            /* minimum value among the low of children */
            low[u] = low[u] < low[w] ? low[u] : low[w];
            /* if it's a root and has more than one child or not a root and low(w) >= dfn(u),
               it's an articulation point */
            if (((u == root) && (child > 1)) || ((u != root) && (dfn[u] <= low[w])))
                articulation_point[u] = TRUE;
        } else if (w != v) {
            low[u] = low[u] < dfn[w] ? low[u] : dfn[w];
        }
    }
}

void connected(int n) {
    /* determine the connected components of the graph */
    int i;
    for (i = 0; i < n; i++)
        if (!visited[i]) {
            dfs(i);
            printf("\n");
        }
}

/* depth-first search */
void dfs(int v) {
    node_pointer w;
    visited[v] = TRUE;
    printf("%3d", v);
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex);
}

/* breadth-first search */
void bfs(int v) {
    node_pointer w;
    queue_pointer front, rear;
    front = rear = NULL; /* initialize queue */
    printf("%3d", v);
    visited[v] = TRUE;
    addq(&front, &rear, v);
    while (front) {
        v = deleteq(&front);
        for (w = graph[v]; w; w = w->link)
            if (!visited[w->vertex]) {
                printf("%3d", w->vertex);
                addq(&front, &rear, w->vertex);
                visited[w->vertex] = TRUE;
            }
    }
}

void addq(queue_pointer *front, queue_pointer *rear, int item) {
    /* insert an element at the rear of the queue */
    queue_pointer temp = (queue_pointer) malloc(sizeof(queue));
    if (IS_FULL(temp)) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->vertex = item;
    temp->link = NULL;
    if (*front)
        (*rear)->link = temp;
    else
        *front = temp;
    *rear = temp;
}

int deleteq(queue_pointer *front) {
    queue_pointer temp = *front;
    int item;
    if (IS_EMPTY(*front)) {
        fprintf(stderr, "The queue is empty\n");
        exit(1);
    }
    item = temp->vertex;
    *front = temp->link;
    free(temp);
    return item;
}

/* function to print the graph */
void print_graph(node_pointer *graph) {
    int i;
    node_pointer ptr;
    for (i = 0; i < vertices; i++) {
        ptr = graph[i];
        printf("Head[%d] : ", i);
        for (; ptr; ptr = ptr->link) {
            if (!(ptr->vertex == -1)) {
                printf("%4d", ptr->vertex);
            }
        }
        printf("\n");
    }
}

