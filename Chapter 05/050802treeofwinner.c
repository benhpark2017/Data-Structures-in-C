/**Solutions to Chapter 5, Section 8, Exercises 2 and 4.
 * Selection Trees: This program constructs a tree of winners for records
 * with eight keys. The smaller key wins the battle between two numbers.
 */

#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 100
#define MAX_BUFFER 8

int TEMP[MAX_BUFFER][MAX_BUFFER];
int stack[MAX_BUFFER];
int run = 0;
int count = 0;

typedef struct runNode* RUN_NODE;
typedef struct runNode {
    int key;
} runNode;

typedef struct selectNode* SELECT_NODE;
typedef struct selectNode {
    int key;
    short run_number;
    short index;
} selectNode;

void winnerTree(runNode **RUN, int nRUN);
void open();
void print(int n);
void iterinorder();
void Restructuring(runNode **RUN, int nRUN);

SELECT_NODE selectTree;

int main() {
    open();
    runNode **RUN; 
    RUN = (runNode**)malloc(sizeof(runNode*) * MAX_BUFFER);
    for (int i = 0; i < MAX_BUFFER; i++)
        RUN[i] = (runNode*)malloc(sizeof(runNode*) * MAX_BUFFER);

    for (int i = 0; i < run; i++)
        for (int j = 0; j < count; j++)
            RUN[i][j].key = TEMP[i][j];

    winnerTree(RUN, count);
    printf("Level order : ");
    print(run);
    printf("\nIn order  :    ");
    iterinorder();
    printf("\n");

    Restructuring(RUN, count);
    printf("Level order : ");
    print(run);
    printf("\nIn order  :    ");
    iterinorder();
    printf("\n");

    free(RUN); 
    return 0;
}

void open() {
    FILE *fp = fopen("winnertree.txt", "r");
    fscanf(fp, "%d", &run);
    int i = 0, j = 0;
    int item;
    while (fscanf(fp, "%d", &item) != EOF) {
        TEMP[i][j] = item;
        j++;
        if (item == -1) {
            i++;
            if (count < j) count = j;
            j = 0;
        }
    }
}

void winnerTree(runNode **RUN, int nRun) {
    int i, j;
    int compare;
    selectTree = (SELECT_NODE)malloc(sizeof(selectNode)*run * 2);

    for (i = 0; i < run; i++) {
        selectTree[i + run].index = 0;
        selectTree[i + run].run_number = i;
        selectTree[i + run].key = RUN[i][selectTree[i + run].index].key;
    }

    i = run;
    compare = run / 2;

    while (i > 1) {
        for (j = 0; j < compare; j++) {
            selectTree[i / 2] = ((selectTree[i].key < selectTree[i + 1].key) ? selectTree[i] : selectTree[i + 1]);
            i += 2;
        }
        i = compare;
        compare /= 2;
    }

    printf("Winner  :     %3d \n", selectTree[1].key);
}

void iterinorder() {
    int i = 1;
    int top = -1;
    while (1) {
        while (run * 2 > i) {
            top++;
            stack[top] = i;
            i = i * 2;
        }
        if (top == -1)
            return;
        i = stack[top];
        top--;
        printf("%3d ", selectTree[i].key);
        i = i * 2 + 1;
    }
}

void print(int n) {
    int i;
    for (i = 1; i < n * 2; i++)
        printf("%3d ", selectTree[i].key);
}

void Restructuring(runNode **RUN, int nRun) {
    int i, j;
    int compare;
    SELECT_NODE winner;

    i = run;
    compare = run / 2;
    winner = selectTree + 1;

    if (winner->index < run - 1) {
        selectTree[run + winner->run_number].key = RUN[winner->run_number][(winner->index) + 1].key;
        ++(selectTree[run + winner->run_number].index);
    } else {
        selectTree[run + winner->run_number].key = INT_MAX;
        --nRun;
    }

    while (i > 1) {
        for (j = 0; j < compare; j++) {
            selectTree[i / 2] = ((selectTree[i].key < selectTree[i + 1].key) ? selectTree[i] : selectTree[i + 1]);
            i += 2;
        }
        i = compare;
        compare /= 2;
    }

    printf("Winner  :     %3d \n", selectTree[1].key);
}


