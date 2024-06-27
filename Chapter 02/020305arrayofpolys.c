/**Solutions to Chapter 2, Section 3, Exercise 5 of Horowitz's
 * Data Structures in C.*/

#include <stdio.h>
#include <string.h> // for memset
//#include <math.h>   // for pow

#define MAX_SIZE 40 // Size of the array

typedef struct {
    float coef; // Coefficient of the polynomial
    int expon;  // Exponent of the polynomial
} Polynomial;

Polynomial one_poly[MAX_SIZE/2], other_poly[MAX_SIZE/2], mult[MAX_SIZE];
// Polynomial to store the multiplication of one_poly and other_poly.

void pmult();           // Function to multiply polynomials
void padd(Polynomial add_poly[]);   // Function to add two polynomials
float peval(Polynomial poly[], int input); // Function to evaluate a polynomial
double pow(double base, double exponent); //Power function


int main() {
    int one_counter = 0, other_counter = 0, counter, prinf_counter;

    // Assigning random polynomials for testing purposes.
    for (counter = 10; counter > 0; --counter) {
        if (counter > 5) {
            one_poly[one_counter].expon = counter;
            one_poly[one_counter].coef = 1.0;
            one_counter++;
            continue;
        }
        other_poly[other_counter].expon = counter;
        other_poly[other_counter].coef = 2.0;
        other_counter++;
    }

    // Initializing the space for the polynomial product.
    memset(mult, 0, sizeof(Polynomial) * MAX_SIZE);

    pmult(); // Perform polynomial multiplication.

    // Printing the stored values.
    for (prinf_counter = 0; mult[prinf_counter].expon > 0; ++prinf_counter)
        printf("%fx^%d\n", mult[prinf_counter].coef, mult[prinf_counter].expon);
    
    // Test the result of pmult at x = 1
    printf("Result of pmult at x = 1: %f\n", peval(mult, 1));

    return 0;
}

void pmult() {
    int one_counter, other_counter;
    Polynomial temp_poly[MAX_SIZE];

    for (other_counter = 0; other_poly[other_counter].expon > 0; ++other_counter) {
        for (one_counter = 0; one_poly[one_counter].expon > 0; ++one_counter) {
            // Adding the exponents and multiplying the coefficients.
            temp_poly[one_counter].expon = one_poly[one_counter].expon + other_poly[other_counter].expon;
            temp_poly[one_counter].coef = one_poly[one_counter].coef * other_poly[other_counter].coef;
        }
        padd(temp_poly); // Add the temporary polynomial to the product.
    }
}

void padd(Polynomial add_poly[]) {
    Polynomial temp_sum_poly[MAX_SIZE];
    int start_a = 0, start_b = 0, sum_counter = 0;

    while (add_poly[start_a].expon > 0) {
        if (add_poly[start_a].expon > mult[start_b].expon) {
            // Store the exponent if it's greater.
            temp_sum_poly[sum_counter].expon = add_poly[start_a].expon;
            temp_sum_poly[sum_counter].coef = add_poly[start_a].coef;
            ++sum_counter;
            ++start_a;
        } else if (add_poly[start_a].expon < mult[start_b].expon) {
            // Store the exponent if it's greater.
            temp_sum_poly[sum_counter].expon = mult[start_b].expon;
            temp_sum_poly[sum_counter].coef = mult[start_b].coef;
            ++sum_counter;
            ++start_b;
        } else {
            // Add the coefficients if the exponents are equal.
            temp_sum_poly[sum_counter].coef = add_poly[start_a].coef + mult[start_b].coef;
            temp_sum_poly[sum_counter].expon = mult[start_b].expon;
            ++sum_counter;
            ++start_a;
            ++start_b;
        }
    }

    // Assign the computed polynomial for the next calculation.
    for (sum_counter = 0; temp_sum_poly[sum_counter].expon > 0; ++sum_counter) {
        mult[sum_counter].expon = temp_sum_poly[sum_counter].expon;
        mult[sum_counter].coef = temp_sum_poly[sum_counter].coef;
    }
}

float peval(Polynomial poly[], int input) {
    int start_counter;
    float sum = 0.0;

    // Iterate through the polynomial terms
    for (start_counter = 0; poly[start_counter].expon > 0; ++start_counter) {
        // Evaluate each term and add it to the sum
        sum += poly[start_counter].coef * pow(input, poly[start_counter].expon);
    }

    // If the last term has exponent 0, add its coefficient to the sum
    if (poly[start_counter].expon == 0) {
        sum += poly[start_counter].coef;
    }

    return sum; // Return the result of polynomial evaluation
}

double pow(double base, double exponent) {
    double result = 1.0;
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

