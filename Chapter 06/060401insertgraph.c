/**Solutions to Chapter 6, Section 4, Exercise 1 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>
#include <stdlib.h> /*for malloc(), free()*/

#define FALSE 0
#define TRUE 1

int input_cost(void);

/* Two-dimensional array pointer */
int **cost;

int main(void) {
    int i, j, n;
    int *distance; /* Pointer to distance[] */
    short int *found; /* Pointer to found[] */

    printf("************* Insert the graph *************\n");
    n = input_cost(); /* Number of vertices in the input graph */

    /* Dynamically allocate array based on user input for vertices */
    distance = (int*)malloc(sizeof(int) * n);
    found = (short int *)malloc(sizeof(short int) * n);

    printf("\n+++ Adjacency Matrix +++\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%7d", cost[i][j]);
        printf("\n");
    }

    /* Free memory allocated for columns */
    for (i = 0; i < n; i++)
        free(cost[i]);
    
    /* Free memory allocated for rows */
    free(cost);
    free(distance);
    free(found);

    return 0;
}

/* Function to input number of vertices and edges from the user */
int input_cost(void) {
    int vertices, vertex1, vertex2, weight;
    int i, j, count = 0; /* count: to check if array size is exceeded */

    printf("Input the number of Vertices: ");
    scanf("%d", &vertices);

    /* Dynamically allocate memory for the rows of cost adjacency matrix */
    cost = (int**)malloc(sizeof(int*) * vertices);

    /* Dynamically allocate memory for the columns of cost adjacency matrix */
    for (i = 0; i < vertices; i++)
        cost[i] = (int*)malloc(sizeof(int) * vertices);

    /* Initialize cost[][] */
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            cost[i][j] = -1;

    printf("Input the weight for each vertex (exit = -1): Usage(vertex1, vertex2, cost)\n");

    /* Input edges until a negative integer is encountered */
    while (count < (vertices * vertices)) {
        printf("%d: ", count++);
        scanf("%d", &vertex1);
        if (vertex1 == -1)
            break;
        scanf("%d%d", &vertex2, &weight);
        cost[vertex1][vertex2] = weight;
    }

    /* Initialize the values of non-existent edges */
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++) {
            if (cost[i][j] == -1) {
                if (i == j)
                    cost[i][j] = 0;
                else
                    cost[i][j] = 1000;
            }
        }

    return vertices;
}

