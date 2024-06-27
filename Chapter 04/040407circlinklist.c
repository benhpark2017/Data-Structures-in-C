/**Solutions to Chapter 4, Section 4, Exercise 7 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define IS_FULL(ptr) (!(ptr))
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1))

typedef struct polyNode {
    int coef;
    int expon;
    struct polyNode *link;
    struct polyNode *downlink;
} polyNode;

typedef struct polyNode *polyPtr;

polyPtr avail = NULL;

int compare(int x, int y);
void polyRead(polyPtr P); //works well
void polyPrint(polyPtr P); //works well
polyPtr polyAdd(polyPtr a, polyPtr b);
polyPtr polySubtract(polyPtr a, polyPtr b);
polyPtr polyMultiply(polyPtr a, polyPtr b);
double polyEvaluate(float x, polyPtr P);
void attach(float coefficient, int exponent, polyPtr *ptr);
void attachDown(polyPtr *ptr);
polyPtr getNode(void);
void polyErase(polyPtr *ptr);

int main(){
    
    polyPtr a, b, c;
    a = getNode();
    b = getNode();
    c = getNode();
    
    polyRead(a);
    polyRead(b);
    polyPrint(a);
    polyPrint(b);

    printf("Add two polynomials a(x) and b(x): ");
    c = polyAdd(a, b);
    polyPrint(c);
    polyErase(&c); //free(c);
    
    printf("Subtract polynomial b(x) from a(x): ");
    c = polySubtract(a, b);
    polyPrint(c);
    polyErase(&c); //free(c);
    
    printf("Multiply polynomials a(x) and b(x): ");
    c = polyMultiply(a, b);
    polyPrint(c);
    printf("Polynomial c(x) evaluated at 2.0 is %lf", polyEvaluate(2.0, c));
    polyErase(&c); //free(c);
}

double power(double base, int exponent) {
    double result = 1.0;
    if (exponent < 0) {
        base = 1 / base;
        exponent = -exponent;
    }
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}

int compare(int x, int y) {
    int result;
    if (x > y) result = 1;
    if (x == y) result = 0;
    if (x < y) result = -1;
    return result;
}

void polyRead(polyPtr P) {
    int numberofTerms, tempExpon;
    float tempCoef;
    polyPtr current = P;  // Start with the head of the linked list

    printf("Enter highest exponent and number of terms: ");
    scanf("%d %d", &current->expon, &numberofTerms);

    for (int i = 0; i < numberofTerms; i++) {
        printf("Enter coefficient followed by exponent: \n");
        scanf("%f %d", &tempCoef, &tempExpon);

        // Allocate memory for the next node
        current->link = getNode();
        current = current->link;

        current->coef = tempCoef;
        current->expon = tempExpon;
    }

    // Terminate the linked list
    current->link = P;
}

void polyPrint(polyPtr P){
    int a = 0;
    polyPtr temp;
    temp = getNode();
    temp = P->link;

    while (temp->link != P){
        if ((temp->coef == 0) && !(P->link==temp)){
            a = -1 * (temp->coef);
            printf("%dx", a);
        } else {
            printf("%dx", temp->coef);
        }
        printf("%d ", temp->expon);
        if (temp->link->coef > 0){ //If the sign of the next term is positive
            printf("+"); //print the plus
        }
        temp = temp->link;
    }
    printf("%d", abs(temp->coef));
    if (temp->expon != 0) printf("x%d", temp->expon);
    printf("\n");
}

polyPtr polyAdd(polyPtr a, polyPtr b) {
    polyPtr c, startA, lastC;
    int sum;
    short int done = 0;
    startA = a;
    a = a->link;
    b = b->link;
    c = getNode();
    c->expon = -1; lastC = c;
    
    if (IS_FULL(lastC)) {
        fprintf(stderr, "The memory is full.\n");
        exit(1);
    }
    
    do {
        switch (compare(a->expon, b->expon)){
            case -1: /*a->expon < b->expon*/ 
                    {attach(b->coef, b->expon, &lastC);
                     b = b->link;
                     break;}
            case 0:  /*a->expon = b->expon*/
                    {if (startA == a) done = 1;
                     else {
                         sum = a->coef + b->coef;
                         if (sum) attach(sum, a->expon, &lastC);
                         a = a->link;
                         b = b->link;
                     }
                     break;}
            case 1:  /*a->expon > b->expon*/
                    {attach(a->coef, a->expon, &lastC);
                     a = a->link; break;
                    }
        } //end switch
    } while (!done); //end do...while
    
    lastC->link = c; 
    return c;
}

polyPtr polySubtract(polyPtr a, polyPtr b) {
    polyPtr c, startA, lastC;
    int diff;
    short int done = 0;
    startA = a;
    a = a->link;
    b = b->link;
    c = getNode();
    c->expon = -1; lastC = c;
    
    if (IS_FULL(lastC)) {
        fprintf(stderr, "The memory is full.\n");
        exit(1);
    }
    
    do {
        switch (compare(a->expon, b->expon)){
            case -1: /*a->expon < b->expon*/
                    {b->coef = -(b->coef);
                     attach(b->coef, b->expon, &lastC);
                     b->coef = -(b->coef);
                     b = b->link;}
                     break;
            case 0:  /*a->expon = b->expon*/
                    {if (startA == a) done = 1;
                     else {
                         b->coef = -(b->coef);
                         diff = a->coef + b->coef;
                         b->coef = -(b->coef);
                         if (diff) attach(diff, a->expon, &lastC);
                         a = a->link;
                         b = b->link;
                     }
                    }   
                     break;
            case 1:  /*a->expon > b->expon*/
                    {attach(a->coef, a->expon, &lastC);
                     a = a->link;}
        } //end switch
    } while (!done); //end do...while
    
    lastC->link = c;
    return c;
    
    /**For linear linked list
    for (; a; a->link) attach(a->coef, a->expon, &rear);
    for (; b; b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL;
    temp = front;
    front = front->link;
    free(temp);
    return front;
    */
}

polyPtr polyMultiply(polyPtr a, polyPtr b) {
    polyPtr result, subresult, temp_one, temp_two, frontresult, front, rear, tempfront;
    subresult = getNode();
    subresult->expon = -1;
    temp_one = a;
    
    frontresult = subresult;
    frontresult->expon = -1;
    front = frontresult;
    
    rear = frontresult;
    temp_one = temp_one->link;
    
    while (temp_one != a){
        temp_two = b;
        temp_two = temp_two->link;
        while (temp_two != b){
            attach(temp_one->coef * temp_two->coef,
                   temp_one->expon + temp_two->expon, &rear);
            temp_two = temp_two->link;       
        }
        rear->link = frontresult;
        attachDown(&frontresult);
        rear = frontresult;
        frontresult->expon = -1;
        temp_one = temp_one->link;
    }
    frontresult->downlink = NULL;
    
    front->expon = -1;
    if (front->downlink->downlink != NULL){
        result = polyAdd(front, front->downlink);
        tempfront = front->downlink->downlink;
        polyErase(&front->downlink);
        polyErase(&front);
        while (tempfront->downlink){
            front = tempfront;
            result = polyAdd(result, tempfront);
            result->downlink = NULL;
            tempfront = front->downlink;
            polyErase(&front);
        }
        return result;
    } else return front;
}

double polyEvaluate(float x, polyPtr P){
    double result = 0;
    polyPtr temp;
    temp = getNode();
    temp = P;
    temp = temp->link;
    while (temp != P) {
        result += temp->coef * power(x, temp->expon);
        temp = temp->link;
    }
    return result;
}

/*The attach function creates a new node with coef = coefficient
 *and expon = exponent, attaches it to the node pointed to by
 *ptr. The polyPtr variable ptr is updated to point to this new 
 *node.
 */
void attach(float coefficient, int exponent, polyPtr *ptr){
    polyPtr temp;
    temp = getNode();
    if (IS_FULL(temp)){
        fprintf(stderr, "The memory is full.\n");
        exit(1);
    }
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void attachDown(polyPtr *ptr){
    polyPtr temp;
    temp = getNode();
    (*ptr)->downlink = temp;
    *ptr = temp;
}

/**This function provides a node for use.*/
polyPtr getNode(){
    polyPtr node;
    if (avail){
        node = avail;
        avail = avail->link;
    } else {
        node = (polyPtr)malloc(sizeof(struct polyNode));
        if (IS_FULL(node)){
            fprintf(stderr, "The memory is full.\n");
            exit(1);
        }
    }
    return node;
}

/* erase the polynomial pointed by ptr */
void polyErase(polyPtr *ptr) {
    polyPtr temp;
    if (*ptr) {
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}
