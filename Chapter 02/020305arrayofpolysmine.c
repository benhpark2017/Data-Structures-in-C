/**Solutions to Chapter 2, Section 3, Exercise 5 of Horowitz's
 * Fundamentals of Data Structures in C.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101 /*Maximum number of terms*/
#define MAX_POLYS 15  /*Maximum number of polynomials*/

typedef struct{
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_POLYS][MAX_TERMS]; //two-dimensional array for polynomial
int avail = 0; // index that keeps track of where to attach a polynomial term

int compareNumbers(int a, int b) {
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}

double power(double a, double b){
    double result = 1.0;
    // For positive powers
    if (b >= 0){
        for (int i = 0; i < b; i++)
            result *= a;
    // For negative powers
    } else {
        for (int i = 0; i > b; i--)
            result /= a;
    }
    return result;
}

double polyEvaluate(float x, polynomial terms[][MAX_TERMS], int nes[], int polyIndex){
    double answer = 0;
    for (int i = 0; i < nes[polyIndex]; i++){
        answer += terms[polyIndex][i].coef * power(x, terms[polyIndex][i].expon);
    }
    return answer;
}


void attach(float coefficient, int exponent, int polyIndex){
//polyIndex tags a polynomial with a unique number.
    if (avail >= MAX_TERMS){
        fprintf(stderr, "There are too many terms in the polynomial.\n");
        exit(1);
    }
    terms[polyIndex][avail].coef = coefficient;
    terms[polyIndex][avail].expon = exponent;
    avail++; //move one entry forward in the terms array
}

void polyMultiply(int polyIndexA, int polyIndexB, int nes[], int *startC, int *finishC) {
    int i, j, k;
    *startC = avail;

    for (i = 0; i < nes[polyIndexA]; i++) {
        for (j = 0; j < nes[polyIndexB]; j++) {
            float coefProduct = terms[polyIndexA][i].coef * terms[polyIndexB][j].coef;
            int exponSum = terms[polyIndexA][i].expon + terms[polyIndexB][j].expon;

            // Find if a term with the same exponent already exists in the result
            int found = 0;
            for (k = *startC; k < avail; k++) {
                if (terms[polyIndexA][k].expon == exponSum) {
                    terms[polyIndexA][k].coef += coefProduct;
                    found = 1;
                    break;
                }
            }

            // If not found, attach a new term
            if (!found) {
                attach(coefProduct, exponSum, polyIndexA);
            }
        }
    }
    *finishC = avail - 1;
}



//Don't touch
void polyAdd(int polyIndexA, int polyIndexB, int nes[], int *startC, int *finishC){
    float coefficient;
    int startA = 0;
    int startB = 0;

    //*startC = avail;
    *startC = 0;

    while (startA < nes[polyIndexA] && startB < nes[polyIndexB]) {
        switch (compareNumbers(terms[polyIndexA][startA].expon, terms[polyIndexB][startB].expon)) {
            case -1:
                attach(terms[polyIndexB][startB].coef, terms[polyIndexB][startB].expon, polyIndexA);
                startB++;
                break;
            case 0:
                coefficient = terms[polyIndexA][startA].coef + terms[polyIndexB][startB].coef;
                if (coefficient != 0.0) attach(coefficient, terms[polyIndexA][startA].expon, polyIndexA);
                startA++;
                startB++;
                break;
            case 1:
                attach(terms[polyIndexA][startA].coef, terms[polyIndexA][startA].expon, polyIndexA);
                startA++;
                break;
        } // end switch-case
    } // end while

    while (startA < nes[polyIndexA]){
        attach(terms[polyIndexA][startA].coef, terms[polyIndexA][startA].expon, polyIndexA);
        startA++;
    }

    while (startB < nes[polyIndexB]){
        attach(terms[polyIndexB][startB].coef, terms[polyIndexB][startB].expon, polyIndexA);
        startB++;
    }

    *finishC = avail - 1;
}

//Don't touch
void readPoly(polynomial terms[][MAX_TERMS], int nes[], int *total){
    //nterms is the number of terms in one polynomial that must not exceed 101,
    //which is the maximum number of terms in the array terms.

    //nes[] is an array such that nes[i] holds the number of terms in
    //one polynomial, terms[i].

    int i, expon, nterms;
    float coef;
    printf("Enter the number of terms in your polynomial: ");
    scanf("%d", &nterms);
    while (nterms >= MAX_TERMS){
        printf("There are too many terms in the polynomial.\n");
        printf("Number of terms: ");
        scanf("%d", &nterms);
    }

    for (i = 0; i < nterms; i++){
        printf("Please enter the coefficient: ");
        scanf("%f", &coef);
        printf("Please enter the exponent: ");
        scanf("%d", &expon);
        terms[*total][i].coef = coef;
        terms[*total][i].expon = expon;
    }
    nes[*total] = nterms;
    (*total)++;
}

//Don't touch
void printPoly(polynomial terms[], int n){
    int i;
    for (i = 0; i < n - 1; i++)
        printf("%5.2fx^%d +", terms[i].coef, terms[i].expon);
    printf("%5.2fx^%d", terms[n - 1].coef, terms[n - 1].expon);
}

//Driver code
int main(){
    int total = 0;
    int nes[MAX_POLYS];
    int option;

    do {
        printf("\nChoose an option:\n");
        printf("1. Read Polynomial\n");
        printf("2. Print Polynomial\n");
        printf("3. Evaluate Polynomial\n");
        printf("4. Add two polynomials\n");
	printf("5. Multiply two polynomials\n");
        printf("0. Exit\n");
        printf("Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (total < MAX_POLYS) {
                    readPoly(terms, nes, &total);
                    printf("Polynomial read successfully.\n");
                } else {
                    printf("Cannot add more polynomials. Maximum limit reached.\n");
                }
                break;

            case 2:
                printf("Enter the polynomial index to print: ");
                int index;
                scanf("%d", &index);
                if (index >= 0 && index < total) {
                    printf("Polynomial %d: ", index);
                    printPoly(terms[index], nes[index]);
                    printf("\n");
                } else {
                    printf("Invalid polynomial index.\n");
                }
                break;

            case 3:
                //Specify polynomial index, polyIndex
                int polyIndex;
                printf("Enter the index of the polynomial to evaluate: ");
                scanf("%d", &polyIndex);
                //Read x value
                float x;
                printf("Enter the value of x: ");
                scanf("%f", &x);

                // Evaluate and print the result
                double result = polyEvaluate(x, terms, nes, polyIndex);
                printf("Result of polynomial number %d at x=%.2f is %.2f\n",
                        polyIndex, x, result);
                break;

            case 4:
                //Specify the numbers of two tagged polynomials
                if (total >= 2) {
                    int i, startC, finishC, polyIndexA, polyIndexB;
                    printf("Enter the indices of the polynomials to add (A and B):\n");
                    printf("Enter the indices separated by a space: ");
                    scanf("%d %d", &polyIndexA, &polyIndexB);
                    polyAdd(polyIndexA, polyIndexB, nes, &startC, &finishC);

                    // Print the result
                    printf("Result of polynomial addition:\n");

                    for (i = startC; i < finishC; i++)
                        printf("%5.2fx^%d +", terms[polyIndexA][i].coef, terms[polyIndexA][i].expon);
                    printf("%5.2fx^%d", terms[polyIndexA][i].coef, terms[polyIndexA][i].expon);

                } else {
                    printf("Insufficient number of polynomials to perform addition.\n");
                }
                break;

            case 5:
                //Specify the numbers of two tagged polynomials
                if (total >= 2) {
                    int i, startC, finishC, polyIndexA, polyIndexB;
                    printf("Enter the indices of the polynomials to multiply (A and B):\n");
                    printf("Enter the indices separated by a space: ");
                    scanf("%d %d", &polyIndexA, &polyIndexB);
                    polyMultiply(polyIndexA, polyIndexB, nes, &startC, &finishC);

                    // Print the result
                    printf("Result of polynomial multiplication:\n");

                    for (i = startC; i < finishC; i++)
                        printf("%5.2fx^%d +", terms[polyIndexA][i].coef, terms[polyIndexA][i].expon);
                    printf("%5.2fx^%d", terms[polyIndexA][i].coef, terms[polyIndexA][i].expon);

                } else {
                    printf("Insufficient number of polynomials to perform addition.\n");
                }
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 0);
    return 0;
}
