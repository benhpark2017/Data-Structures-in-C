/**Solutions to Chapter 2, Section 3, numbered exercises 1~3 of
 * Horowitz's Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#define MAX_DEGREE 101

FILE *filereadPtr;
FILE *filewritePtr;

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

typedef struct Polynomial *polyPtr;
struct Polynomial{
    int expon;
    int coef[MAX_DEGREE];
};

polyPtr makePolyPtr(){
    polyPtr P = malloc(sizeof(struct Polynomial));
    for (int i = 0; i < MAX_DEGREE; i++){
        P->coef[i] = 0;
    }
    return P;
}

polyPtr polyAdd(polyPtr a, polyPtr b){
    polyPtr c = makePolyPtr();
    c->expon = 0;
    int big, i;
    if (a->expon > b->expon){
        big = a->expon;
    } else {
        big = b->expon;
    }
    for (i = big; i >= 0; i--){
        c->coef[i] = a->coef[i] + b->coef[i];
        if (c->expon==0 && c->coef[i] != 0)
            c->expon = i;
    }
    return c;
};

polyPtr polyMultiply(polyPtr a, polyPtr b){
    polyPtr c = makePolyPtr();
    c->expon = a->expon + b->expon;
    for (int i = a->expon; i >= 0; i--)
        for (int j = b->expon; j >= 0; j--)
            c->coef[i+j] += a->coef[i] * b->coef[j];
    return c;
}

void polyPrint(polyPtr P){
    for (int i = P->expon; i >= 0; i--){
        if (P->coef[i] != 0){
            if (i == 0){
                fprintf(filewritePtr, "%+.1d", P->coef[i]);
            } else {
                fprintf(filewritePtr, "%+.1dx^%d", P->coef[i], i);
            }
        }
    }
    fprintf(filewritePtr, "\n");
}

float polyEvaluate(float x, polyPtr P){
    float answer = 0;
    for (int i = 0; i <= P->expon; i++)
        answer += P->coef[i] * power(x, i);
    return answer;
}

int main(){
    filereadPtr = fopen("input.txt", "r");
    filewritePtr = fopen("output.txt", "w");
    int numberA, numberB, tempExpon;
    float tempCoef;
 
    polyPtr a = makePolyPtr();
    fscanf(filereadPtr, "%d %d", &a->expon, &numberA);
    for (int i = 0; i < numberA; i++){
        fscanf(filereadPtr, "%f %d", &tempCoef, &tempExpon);
        a->coef[tempExpon] = tempCoef;
    }
    
    polyPtr b = makePolyPtr();
    fscanf(filereadPtr, "%d %d", &b->expon, &numberB);
    for (int i = 0; i < numberB; i++){
        fscanf(filereadPtr, "%f %d", &tempCoef, &tempExpon);
        b->coef[tempExpon] = tempCoef;
    }
    
    polyPtr c = makePolyPtr();

    fprintf(filewritePtr, "Polynomial a(x): ");
    polyPrint(a);

    fprintf(filewritePtr, "Polynomial b(x): ");
    polyPrint(b);

    c = polyAdd(a, b);
    fprintf(filewritePtr, "Addition result: ");
    polyPrint(c);
    
    c = polyMultiply(a, b);
    fprintf(filewritePtr, "Multiplication result: ");
    polyPrint(c);
    
    fprintf(filewritePtr, "Polynomial c(x) evaluated at x = 2.0: %f",
            polyEvaluate(2.0, c));
    
    return 0;
}
