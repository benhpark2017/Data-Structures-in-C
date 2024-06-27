/**Solutions to Chapter 2, Section 3, Exercise numbers 1, 2, 3, 5
 * of Horowitz's Data Structures.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_POLYS 15

typedef struct {
    float coef;
    int expon;
} Polynomial;

Polynomial terms[MAX_POLYS][MAX_TERMS];
Polynomial sum[MAX_TERMS];
Polynomial product[MAX_TERMS];

void readPoly();
void printPoly(Polynomial poly[]);
void addPolynomials(Polynomial one[], Polynomial theOther[]);
void multiplyPolynomials(Polynomial one[], Polynomial theOther[]);
float peval(Polynomial poly[], int input);
double pow(double base, double exponent);

int main() {
    int one, theOther;

    readPoly();
    printPoly(terms[0]);
    printPoly(terms[1]);

    printf("Enter the row numbers of the two polynomials to add: ");
    scanf("%d %d", &one, &theOther);
    addPolynomials(terms[one], terms[theOther]);
    printf("Result of addition:\n");
    printPoly(sum);
    printf("Result of addition at x = 1: %.2f\n", peval(sum, 1));

    printf("Enter the row numbers of the two polynomials to multiply: ");
    scanf("%d %d", &one, &theOther);
    multiplyPolynomials(terms[one], terms[theOther]);
    printf("Result of multiplication:\n");
    printPoly(product);
    printf("Result of multiplication at x = 1: %.2f\n", peval(product, 1));

    return 0;
}

void readPoly() {
    int polyCounter, rowCounter;
    char decision;

    for (polyCounter = 0; polyCounter < MAX_POLYS; ++polyCounter) {
        printf("Enter the coefficients and exponents for polynomial %d:\n", polyCounter);
        printf("Enter the terms in descending order of exponents.\n");

        for (rowCounter = 1; ; ++rowCounter) {
            printf("Enter term %d in the order of coefficient followed by an exponent.\n", rowCounter);
            printf("Enter a negative exponent to finish: ");
            scanf("%f %d", &(terms[polyCounter][rowCounter].coef), &(terms[polyCounter][rowCounter].expon));

            if (terms[polyCounter][rowCounter].expon < 0) // Finish input if exponent is negative
                break;

            if (rowCounter != 1 && (terms[polyCounter][rowCounter - 1].expon < terms[polyCounter][rowCounter].expon))
                --rowCounter; // Re-enter if current exponent is greater than previous one
        }

        terms[polyCounter][0].expon = rowCounter - 1;

        printf("Do you want to enter another polynomial? (y or n): ");
        scanf(" %c", &decision); // Space before %c to consume newline from previous input

        if (decision != 'Y' && decision != 'y')
            break;
    }
}

void printPoly(Polynomial poly[]) {
    int rowCounter;

    for (rowCounter = 1; poly[rowCounter].expon > 0; ++rowCounter)
        printf("%.2fx^%d ", poly[rowCounter].coef, poly[rowCounter].expon);

    printf("\n");
}

void addPolynomials(Polynomial one[], Polynomial theOther[]) {
    Polynomial *tempSumPoly;
    int startA = 1, startB = 1, sumCounter = 1;

    tempSumPoly = (Polynomial *)calloc(MAX_TERMS, sizeof(Polynomial));

    while (one[startA].expon > 0 || theOther[startB].expon > 0) {
        if (one[startA].expon > theOther[startB].expon) {
            tempSumPoly[sumCounter].expon = one[startA].expon;
            tempSumPoly[sumCounter].coef = one[startA].coef;
            ++sumCounter;
            ++startA;
        } else if (one[startA].expon < theOther[startB].expon) {
            tempSumPoly[sumCounter].expon = theOther[startB].expon;
            tempSumPoly[sumCounter].coef = theOther[startB].coef;
            ++sumCounter;
            ++startB;
        } else {
            tempSumPoly[sumCounter].coef = one[startA].coef + theOther[startB].coef;
            tempSumPoly[sumCounter].expon = theOther[startB].expon;
            ++sumCounter;
            ++startA;
            ++startB;
        }
    }

    memcpy(sum, tempSumPoly, sizeof(Polynomial) * MAX_TERMS);
    sum[0].expon = sumCounter - 1;

    free(tempSumPoly);
}

void multiplyPolynomials(Polynomial one[], Polynomial theOther[]) {
    int oneCounter, otherCounter, productCounter = 1;

    memset(product, 0, sizeof(product)); // Initialize product polynomial

    for (oneCounter = 1; one[oneCounter].expon > 0; ++oneCounter) {
        for (otherCounter = 1; theOther[otherCounter].expon > 0; ++otherCounter) {
            int expon = one[oneCounter].expon + theOther[otherCounter].expon;
            float coef = one[oneCounter].coef * theOther[otherCounter].coef;

            while (product[productCounter].expon > 0 && product[productCounter].expon > expon)
                ++productCounter;

            if (product[productCounter].expon == expon)
                product[productCounter].coef += coef;
            else {
                memmove(&product[productCounter + 1], &product[productCounter], sizeof(Polynomial) * (MAX_TERMS - productCounter));
                product[productCounter].expon = expon;
                product[productCounter].coef = coef;
            }
        }
    }
}

float peval(Polynomial poly[], int input) {
    int startCounter;
    float sum = 0.0;

    for (startCounter = 1; poly[startCounter].expon > 0; ++startCounter)
        sum += poly[startCounter].coef * pow(input, poly[startCounter].expon);

    if (poly[startCounter].expon == 0)
        sum += poly[startCounter].coef;

    return sum;
}

double pow(double base, double exponent) {
    float result = 1.0;
    int i;

    if (exponent >= 0) {
        for (i = 0; i < exponent; i++) {
            result *= base;
        }
    } else {
        for (i = 0; i < -exponent; i++) {
            result /= base;
        }
    }
    return result;
}
