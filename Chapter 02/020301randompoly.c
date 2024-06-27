/**Solutions to Chapter 2, Section 3, Exercise 1 of Horowitz's Fundamentals of Data
 * Structures in C.
 */

#include <stdio.h>
#include <stdlib.h> // for srand(), rand()
#include <time.h>   // for time()
#include <string.h> // for memset()

#define MAX_TERMS 100 // Size of the array

typedef struct {
    int coef;   // Coefficient
    int expon;  // Exponent
} Polynomial;    // Structure to store exponent and coefficient

Polynomial terms[MAX_TERMS];

void readpoly();
void printpoly();

int main() {
    readpoly();
    printpoly();
    return 0;
}

void readpoly() {
    int input, temp;
    int counter;
    
    memset(terms, -1, sizeof(Polynomial) * MAX_TERMS); // Initialize to -1 to represent the term of degree 0
    printf("Enter the degree of the polynomial. (Please enter 100 or less): "); // To stabilize due to the array size being 100...
    scanf("%d", &input);
    
    srand(time(NULL)); // Initialize rand() with time function
    
    terms[0].expon = input;
    terms[0].coef = rand() % 100 + 1; // +1 to avoid coefficient being 0
    temp = input;
    
    for (counter = 1; temp > 0; ++counter) { // Loop until the exponent is 0 or negative
        terms[counter].expon = rand() % temp;
        terms[counter].coef = rand() % 100 + 1;
        temp = terms[counter].expon;
    }
}

void printpoly() {
    int counter;
    
    for (counter = 0; terms[counter].expon >= 0; ++counter) // Print the generated polynomial
        printf("%dx^%d ", terms[counter].coef, terms[counter].expon);
    puts(""); // Move to the next line
}

