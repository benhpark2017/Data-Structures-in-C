/**Solutions to Chapter 4, Section 4, Exercise 7 of Fundamentals
 * of Data Structures in C by Horowitz, Sahni and Anderson-Freed.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Polynomial *polyPtr;
struct Polynomial{
    int coef;
    int expon;
    polyPtr link;
};

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

polyPtr makePolyNode(int coef, int expon){
    polyPtr P = malloc(sizeof(struct Polynomial));
    P->coef = coef;
    P->expon = expon;
    P->link = NULL;
    return P;
}

void polyRead(polyPtr *P) {
    int numberofTerms, tempExpon;
    int tempCoef;
    polyPtr lastNode = NULL;
    printf("Please enter the number of terms: ");
    scanf("%d", &numberofTerms);
    for (int i = 0; i < numberofTerms; i++){
        printf("Enter coefficient followed by exponent:\n");
        scanf("%d %d", &tempCoef, &tempExpon);
        polyPtr newNode = makePolyNode(tempCoef, tempExpon);
        if (*P == NULL) {
            *P = newNode;
        } else {
            lastNode->link = newNode;
        }
        lastNode = newNode;
    }
}

polyPtr polyAdd(polyPtr a, polyPtr b){
    polyPtr c = NULL, lastNode = NULL;
    while (a != NULL && b != NULL) {
        polyPtr newNode = NULL;
        if (a->expon > b->expon) {
            newNode = makePolyNode(a->coef, a->expon);
            a = a->link;
        } else if (a->expon < b->expon) {
            newNode = makePolyNode(b->coef, b->expon);
            b = b->link;
        } else {
            newNode = makePolyNode(a->coef + b->coef, a->expon);
            a = a->link;
            b = b->link;
        }
        if (c == NULL) {
            c = newNode;
        } else {
            lastNode->link = newNode;
        }
        lastNode = newNode;
    }
    while (a != NULL) {
        polyPtr newNode = makePolyNode(a->coef, a->expon);
        if (c == NULL) {
            c = newNode;
        } else {
            lastNode->link = newNode;
        }
        lastNode = newNode;
        a = a->link;
    }
    while (b != NULL) {
        polyPtr newNode = makePolyNode(b->coef, b->expon);
        if (c == NULL) {
            c = newNode;
        } else {
            lastNode->link = newNode;
        }
        lastNode = newNode;
        b = b->link;
    }
    return c;
}

polyPtr polyMultiply(polyPtr a, polyPtr b){
    polyPtr c = NULL;
    for (polyPtr aNode = a; aNode != NULL; aNode = aNode->link) {
        polyPtr temp = NULL, lastNode = NULL;
        for (polyPtr bNode = b; bNode != NULL; bNode = bNode->link) {
            polyPtr newNode = makePolyNode(aNode->coef * bNode->coef, aNode->expon + bNode->expon);
            if (temp == NULL) {
                temp = newNode;
            } else {
                lastNode->link = newNode;
            }
            lastNode = newNode;
        }
        c = polyAdd(c, temp);
    }
    return c;
}

void polyPrint(polyPtr P){
    while (P != NULL) {
        if (P->expon == 0){
            printf("%+d", P->coef);
        } else {
            printf("%+dx^%d", P->coef, P->expon);
        }
        P = P->link;
    }
    printf("\n");
}

float polyEvaluate(float x, polyPtr P){
    float answer = 0;
    while (P != NULL) {
        answer += P->coef * power(x, P->expon);
        P = P->link;
    }
    return answer;
}

int main(){

    polyPtr a = NULL;
    polyRead(&a);

    polyPtr b = NULL;
    polyRead(&b);

    polyPtr c = NULL;

    printf("Polynomial a(x): ");
    polyPrint(a);

    printf("Polynomial b(x): ");
    polyPrint(b);

    c = polyAdd(a, b);
    printf("Addition result: ");
    polyPrint(c);

    c = polyMultiply(a, b);
    printf("Multiplication result: ");
    polyPrint(c);

    printf("Polynomial c(x) evaluated at x = 2.0: %f\n",
            polyEvaluate(2.0, c));

    return 0;
}
