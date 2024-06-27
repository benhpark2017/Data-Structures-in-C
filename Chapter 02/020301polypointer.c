/**Solutions to Chapter 2, Section 3, Exercises 1 through 3 and 5 of Fundamentals
 * of Data Structures in C by Horowitz, Sahni, and Anderson-Freed.
 */

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#define MAX_DEGREE 101

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

void polyRead(polyPtr P) {
    int numberofTerms, tempExpon;
    float tempCoef;
    printf("Please enter the number of terms followed by the highest exponent");
    scanf("%d %d", &P->expon, &numberofTerms);
    for (int i = 0; i < numberofTerms; i++){
        printf("Enter coefficient followed by exponent:\n");
        scanf("%f %d", &tempCoef, &tempExpon);
        P->coef[tempExpon] = tempCoef;
    }
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
                printf("%+.1d", P->coef[i]);
            } else {
                printf("%+.1dx^%d", P->coef[i], i);
            }
        }
    }
    printf("\n");
}

float polyEvaluate(float x, polyPtr P){
    float answer = 0;
    for (int i = 0; i <= P->expon; i++)
        answer += P->coef[i] * power(x, i);
    return answer;
}

int main(){

    polyPtr a = makePolyPtr();
    polyRead(a);

    polyPtr b = makePolyPtr();
    polyRead(b);

    polyPtr c = makePolyPtr();

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
