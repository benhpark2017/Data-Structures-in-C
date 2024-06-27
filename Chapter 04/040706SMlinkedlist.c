/**Solutions to Chapter 4, Section 7, Exercise 6 of Horowitz's
 * Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define IS_FULL(temp) (!(temp))
#define COMPARE(a,b) ( ((a) < (b)) ? -1 : ((a) == (b)) ? 0 : 1)

typedef enum {head, entry} tagfield;

typedef struct {
    int row;
    int col;
    int value;
} entry_node;

typedef struct matrix_node {
    struct matrix_node *down;
    struct matrix_node *right;
    tagfield tag;
    union {
        struct matrix_node *next;
        entry_node entry;
    } u;
} matrix_node;

typedef struct matrix_node *matrix_pointer;

static matrix_pointer hdnode1[MAX_SIZE];
static matrix_pointer hdnode2[3][MAX_SIZE];

matrix_pointer new_node(void);
void mwrite(matrix_pointer node);
matrix_pointer mread(int num_rows, int num_cols, int num_terms);
matrix_pointer mplus(matrix_pointer pt1, matrix_pointer pt2);
matrix_pointer mmulti(matrix_pointer pt1, matrix_pointer pt2);
void new_entry(int i, int j, int val, matrix_pointer pt, int seq);
matrix_pointer make_matrix(int row, int col, int seq);
matrix_pointer mtranspose(matrix_pointer pt);
void merase(matrix_pointer *node);


void main() {
    int num_rows1, num_rows2, num_cols1, num_cols2, num_terms1, num_terms2;
    matrix_pointer a, b, c, d, e;
    printf("Enter the number of rows, columns and number of nonzero terms: ");
    scanf("%d %d %d", &num_rows1, &num_cols1, &num_terms1);
    
    a = new_node();
    a = mread(num_rows1, num_cols1, num_terms1);
    printf("Enter the number of rows, columns and number of nonzero terms: ");
    scanf("%d %d %d", &num_rows2, &num_cols2, &num_terms2);
    
    b = new_node();
    b = mread(num_rows2, num_cols2, num_terms2);
    mwrite(a);
    mwrite(b);
    
    c = new_node();
    c = mplus(a, b);
    mwrite(c);
    
    d = new_node();
    d = mmulti(a, b);
    mwrite(d);
    
    e = new_node();
    e = mtranspose(a);
    printf("Transposed matrix is: \n");
    mwrite(e);

    merase(&a);
    merase(&b);
    merase(&c);
    merase(&d);
    merase(&e);
}

matrix_pointer new_node(void){
    matrix_pointer temp;
    temp = (matrix_pointer)malloc(sizeof(matrix_node));
    if (IS_FULL(temp)) {
        fprintf(stderr, "The memory is full.\n");
        exit(1);
    }
    return temp;
}

void mwrite(matrix_pointer node) {
    int i, j, num, note;
    matrix_pointer temp, head = node->right;
    int my_row = node->u.entry.row;

    for (i = 0; i < my_row ; i++) {
        note = 0;
        if((head->right) == head)
            for(j=0; j<node->u.entry.col; j++)
        printf("0  ");

        for (temp = head->right; temp != head; temp = temp->right) {
            num = temp->u.entry.col;
	    if (!note)
                for (j = 0; j < num; j++)
                    printf("0  ");
            printf("%d  ", temp->u.entry.value);
            if ((temp->u.entry.col != node->u.entry.col - 1) && temp->right == head)
                for(j=temp->u.entry.col; j<node->u.entry.col-1; j++)
                    printf("0  ");
                if ((temp->right != head))
                    for(j=temp->u.entry.col; j<temp->right->u.entry.col-1; j++)
                        printf("0  ");
                    note = 1;
        }//end second nested for loop

        printf("\n");
        head = head->u.next;
    }//end outermost for loop
    printf("\n\n");
}

matrix_pointer mread(int num_rows,int num_cols,int num_terms){
    int num_heads, i;
    int row, col, value, current_row;
    matrix_pointer temp, last, node;
    if (num_cols > num_rows) num_heads =  num_cols;
    else num_heads = num_rows;

    node = new_node();
    node -> tag = entry;
    node -> u.entry.row = num_rows;
    node -> u.entry.col = num_cols;

    if (!num_heads) node -> right = node;
    else {
        for (i = 0; i < num_heads; i++) {
            temp = new_node();
            hdnode1[i] = temp;
            hdnode1[i]->tag = head;
            hdnode1[i]->right = temp;
            hdnode1[i]->u.next = temp;
        }
        current_row = 0;
        last = hdnode1[0];
        for (i = 0; i < num_terms; i++) {
            printf("Enter row, column amd value: ");
            scanf("%d %d %d", &row, &col, &value);
            if (row > current_row) {
                last -> right = hdnode1[current_row];
                current_row = row;
                last = hdnode1[row];
            }//end if
            temp = new_node();
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;
            last->right = temp;
            last = temp;

            hdnode1[col]->u.next ->down = temp;
            hdnode1[col]->u.next = temp;
        }//end for
        last -> right = hdnode1[current_row];

        for (i=0; i<num_cols; i++) 
            hdnode1[i]->u.next -> down = hdnode1[i];
        for (i=0; i<num_heads-1; i++)
            hdnode1[i]->u.next = hdnode1[i+1];
        hdnode1[num_heads-1] -> u.next = node;
        node -> right = hdnode1[0];
    }//end else
    return node;
}

matrix_pointer mplus(matrix_pointer pt1, matrix_pointer pt2) {
    if (pt1->u.entry.col != pt2->u.entry.col || pt1->u.entry.row != pt2->u.entry.row)
        return NULL;

    matrix_pointer pt3;
    matrix_pointer head1 = pt1->right, head2 = pt2->right, temp1, temp2;

    int my_row = pt1->u.entry.row;
    int my_col = pt1->u.entry.col;

    pt3 = make_matrix(my_row, my_col, 2);

    for (int i = 0; i < my_row ; i++) {
        temp1 = head1->right;
        temp2 = head2->right;

        while ((temp1 != head1) && (temp2!=head2)) {
            switch(COMPARE(temp1->u.entry.col, temp2->u.entry.col)){
                case -1: new_entry(temp1->u.entry.row,
                                   temp1->u.entry.col,
                                   temp1->u.entry.value, pt3, 2);
                         temp1 = temp1->right;
                         break;
                case 0 : new_entry(temp1->u.entry.row,
                                   temp1->u.entry.col,
                                   temp1->u.entry.value + temp2->u.entry.value, pt3, 2);
                         temp1 = temp1->right;
                         temp2 = temp2->right;
                         break;
                case 1 : new_entry(temp2->u.entry.row, temp2->u.entry.col, temp2->u.entry.value, pt3, 2);
                         temp2 = temp2->right;
                         break;
           }//end switch
        }//end while

        while ((temp1!=head1) && (temp2 == head2)) {
            new_entry(temp1->u.entry.row, temp1->u.entry.col, temp1->u.entry.value, pt3, 2);
            temp1 = temp1->right;
        }

        while ((temp1 == head1) && (temp2 != head2)) {
            new_entry(temp2->u.entry.row, temp2->u.entry.col, temp2->u.entry.value, pt3, 2);
            temp2 = temp2->right;
        }
        head1 = head1->u.next;
        head2 = head2->u.next;
    }
    return pt3;
}

matrix_pointer mmulti(matrix_pointer pt1, matrix_pointer pt2){
    if (pt1->u.entry.col != pt2->u.entry.row)
        return NULL;
    int temp;
    matrix_pointer pt3;
    matrix_pointer head1 = pt1->right, head2 = pt2->right;
    matrix_pointer temp1, temp2;
    int my_row = pt1->u.entry.row;
    int my_col = pt2->u.entry.col;

    pt3 = make_matrix(my_row, my_col, 2);
    temp1 = head1->right;
    temp2 = head2->down;


    for (int i = 0; i < pt1->u.entry.row ; i++) {
        head2 = pt2->right;

        for(int j=0; j< pt2->u.entry.col; j++) {
            temp = 0;
            temp1 = head1->right;
            temp2 = head2->down;

            while((temp1 != head1) && (temp2 != head2)) {
                switch(COMPARE(temp1->u.entry.col, temp2->u.entry.row)) {
                    case -1:  temp1 = temp1->right;
                              break;
                    case 0 :  temp += temp1->u.entry.value * temp2->u.entry.value;
                              temp1 = temp1->right;
                              temp2 = temp2->down;
                              break;
                    case 1 :  temp2 = temp2->down;
                              break;
                }//end switch
            } //end while

	    if (temp) new_entry(i, j, temp, pt3, 2);
	    head2 = head2->u.next;
        }//end inner for
        head1 = head1->u.next;
    }//end outer for
    return pt3;
}

void new_entry(int i, int j, int val, matrix_pointer pt, int seq){
    matrix_pointer temp, p;
    temp = new_node();
    temp->tag = entry;
    temp->u.entry.row = i;
    temp->u.entry.col = j;
    temp->u.entry.value = val;

    for (p = hdnode2[seq][i]->right; p->right != hdnode2[seq][i]; p = p->right);
    temp->right = p->right;
    p->right = temp;

    for (p = hdnode2[seq][j]->down; p->down != hdnode2[seq][j]; p = p->down);
    temp->down = p->down;
    p->down = temp;
    pt->u.entry.value += 1;
}

matrix_pointer make_matrix(int row, int col, int seq) {
    int num_heads;
    matrix_pointer pt, temp;
    pt = new_node();
    pt->tag = entry;
    pt->u.entry.row = row;
    pt->u.entry.col = col;
    pt->u.entry.value = 0;

    if (col > row) num_heads = col;
    else num_heads = row;

    for (int i = 0; i < num_heads; i++) {
        temp = new_node();
        hdnode2[seq][i] = temp;
        hdnode2[seq][i]->tag = head;
        hdnode2[seq][i]->right = temp;
        hdnode2[seq][i]->down = temp;
    }

    for (int i = 0; i < num_heads-1; i++)
        hdnode2[seq][i]->u.next = hdnode2[seq][i+1];

    hdnode2[seq][num_heads-1]->u.next = pt;
    pt->right = hdnode2[seq][0];
    pt->down = hdnode2[seq][0];
    return pt;
}

matrix_pointer mtranspose(matrix_pointer pt) {
    int num_rows = pt->u.entry.row;
    int num_cols = pt->u.entry.col;
    matrix_pointer transposed_matrix = make_matrix(num_cols, num_rows, 3);
    
    matrix_pointer head = pt->right;
    
    for (int i = 0; i < num_rows; i++) {
        matrix_pointer temp = head->right;
        while (temp != head) {
            new_entry(temp->u.entry.col, temp->u.entry.row, temp->u.entry.value, transposed_matrix, 3);
            temp = temp->right;
        }
        head = head->u.next;
    }

    return transposed_matrix;
}


void merase(matrix_pointer *node) {
    matrix_pointer x, y, head = (*node)->right;
    int i, num_heads;
    for (i = 0; i < (*node)->u.entry.row; i++){
        y = head->right;
        while (y != head){
            x = y; y = y->right;
            free(x);
        }
        x = head;
        head = head->u.next;
        free(x);
    }
    y = head;
    while (y != *node){
        x = y;
        y = y->u.next;
        free(x);
    }
    free(*node);
    *node = NULL;  // Set the matrix pointer to NULL after deletion
    printf("Memory successfully freed.\n");
}
