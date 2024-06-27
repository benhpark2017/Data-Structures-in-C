/**Solutions to Chapter 6, Section 4, Exercise 5 of Horowitz's Data
 * Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
#define MAX_VERTICES 8
#define FALSE 0
#define TRUE 1
#define INF 1000000

int cost[][MAX_VERTICES] = {
    {0, INF, INF, INF, INF, INF, INF, INF},
    {300, 0, INF, INF, INF, INF, INF, INF},
    {1000, 800, 0, INF, INF, INF, INF, INF},
    {INF, INF, 1200, 0, INF, INF, INF, INF},
    {INF, INF, INF, 1500, 0, 250, INF, INF},
    {INF, INF, INF, 1000, INF, 0, 900, 1400},
    {INF, INF, INF, INF, INF, INF,  0, 1000},
    {1700, INF, INF, INF, INF, INF, INF, 0}
};

/*node 구조체*/
typedef struct node {
    int vertex; 
    int cost; 
    struct node* link; 
};
typedef struct node *node_pointer; /*struct pointer*/
node_pointer graph[MAX_VERTICES];/*struct array*/

/*최단 경로 발견 여부 확인을 위한 구조체*/
typedef struct found {
    int vertex; 
    struct found *link; 
}; 
typedef struct found *found_pointer;


int distance[MAX_VERTICES]; found_pointer p_fnd = NULL; /*조사되지 않은 정점을 가지는 구조체 포인터*/

int n = MAX_VERTICES;
void make_lists(node_pointer *headnode);
int choose(int distance[], int n, found_pointer *p_fnd); 
void shortestpath(int v, node_pointer *head_node, int distance[], int n, found_pointer *p_fnd);
void free_memory(node_pointer *ptr);

void main() { 
    int i, j; 
    make_lists(graph); 
    for (i = 0; i<n; i++) { 
        shortestpath(i, graph, distance, n, &p_fnd); 
        for (j = 0; j < n; j++) printf("%10d", distance[j]); 
        printf("\n");
    } 
}

void make_lists(node_pointer *headnode) {
    node_pointer element, temp; node_pointer *ptr; /*head node*/
    int i, j; 
    /*adjacency matirx를 list로 변환*/ 
    for (i = 0; i < MAX_VERTICES; i++)
        for (j = 0; j<MAX_VERTICES; j++) {
            element = (node_pointer)malloc(sizeof(struct node)); 
            element->vertex = j;
            element->cost = cost[i][j];
            element->link = NULL;
            ptr = &headnode[i]; /*head node가 null이면 head node에 추가*/
            if(!(*ptr)) *ptr = element; /*아니면 마지막 node를 찾아 list추가*/
            else {
                for (temp = *ptr; temp->link; temp = temp->link); 
                temp->link = element; 
            } 
        } 
}

/*memory 해제 함수*/ 
void free_memory(node_pointer *ptr){
    node_pointer trail;
    while(*ptr) { 
        trail = *ptr; *ptr = (*ptr)->link; free(trail); 
    } 
}

int choose(int distance[], int n, found_pointer *p_fnd) {
    int i, min, minpos, exist;
    found_pointer ptr;
    min = INT_MAX;
    minpos = -1;
    exist = FALSE;
    
    for (i = 0; i < n; i++) { /*리스트를 따라가면서 최소비용 선택*/
        for (ptr = *p_fnd; ptr; ptr = ptr->link) {
            if (distance[ptr->vertex] < min) {
                min = distance[ptr->vertex];
                minpos = ptr->vertex; 
            }
        } 
    } 
    return minpos; 
}

void shortestpath(int v, node_pointer *head_node, int distance[], int n, found_pointer *p_fnd) {
    int i, u, w;
    node_pointer ptr;
    found_pointer lead, trail; /*p_fnd리스트에 v를 제외한 모든 정점 저장*/
    
    // Populate the found list with all vertices except v
    for (i = 0; i < n; i++) {
        if (i == v) continue;
        lead = (found_pointer)malloc(sizeof(struct found));
        lead->vertex = i;
        lead->link = NULL; /* head node가 null이면 head node */
        if (!(*p_fnd))
            *p_fnd = trail = lead; /* 아니면 trail다음에 추가 */
        else {
            trail->link = lead;
            trail = lead;
        }
    }

    /* 리스트 정점의 cost를 distance배열에 넣음 */
    for (ptr = head_node[v], i = 0; ptr; ptr = ptr->link, i++)
        distance[i] = ptr->cost;

    distance[v] = 0;

    for (i = 0; i < n - 2; i++) {
        // Choose the vertex with the minimum distance not yet processed
        u = choose(distance, n, p_fnd); /* T = V(G) - S */
        
        // If the found vertex is the head, change head and remove it
        if ((*p_fnd)->vertex == u) {
            lead = *p_fnd;
            *p_fnd = lead->link;
            free(lead);
        }
        // If it's not the head, find and remove it from the found vertices
        else {
            for (trail = *p_fnd; trail; trail = trail->link) {
                if (trail->vertex == u) {
                    lead->link = trail->link;
                    free(trail);
                    break;
                }
                lead = trail;
            }
        }
        
        // Choose the vertex with minimum cost among unprocessed vertices
        // and update its distance if necessary
        for (lead = *p_fnd; lead; lead = lead->link) {
            w = lead->vertex;
            // Search for w among the adjacent vertices of u
            for (ptr = head_node[u]; ptr; ptr = ptr->link)
                if (ptr->vertex == w)
                    break;
            
            // Update distance[w] if the new path through u is shorter
            if (distance[u] + ptr->cost < distance[w])
                distance[w] = distance[u] + ptr->cost;
        }
    }

    // Free memory and reset found list
    free(*p_fnd);
    *p_fnd = NULL;
}
