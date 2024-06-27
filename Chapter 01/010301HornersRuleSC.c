/**Solutions to Chapter 1, Section 3, Exercise 1 of Horowitz's Data Structures
 * in C. */

#include <stdio.h>
#include <stdlib.h>

//For this recursive implementation of Horner's rule, the total step count is 2n + 2.
int stepCount = 0;

// Function to evaluate a polynomial using Horner's Rule
double evaluatePolynomial(int degree, double coefficients[], double x) {
    stepCount++;
    // Base case: if the degree is 0, return the constant term
    if (degree == 0) {
        stepCount++;
        return coefficients[0];
    } else {
        stepCount++;
        // Recursive case: evaluate the polynomial with reduced degree
        return evaluatePolynomial(degree - 1, coefficients, x) * x + coefficients[degree];
    }
}

int main(){

    int degree;

    // Get the degree of the polynomial from the user
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);

    // Ensure the degree is non-negative
    if (degree < 0) {
        printf("Invalid degree. Please enter a non-negative integer.\n");
        return 1;  // Exit with an error code
    }

    // Dynamically allocate an array to store coefficients
    double *coefficients = malloc((degree + 1) * sizeof(double));

    // Get coefficients from the user
    for (int i = degree; i >= 0; i--) {
        printf("Enter the coefficient for x^%d: ", i);
        scanf("%lf", &coefficients[i]);
    }

    double x;  // Value of x for evaluation

    // Get the value of x from the user
    printf("Enter the value of x for evaluation: ");
    scanf("%lf", &x);

    // Evaluate the polynomial using Horner's Rule
    double result = evaluatePolynomial(degree, coefficients, x);

    // Display number of step counts
    printf("Number of steps taken: %d\n", stepCount);

    // Display the result
    printf("Result of the polynomial evaluation at x = %.2f is: %.2f\n", x, result);

    // Free dynamically allocated memory
    free(coefficients);

    return 0;
}
