/**Solutions to Chapter 1, Section 2, Exercise 7 of Horowitz's Data Structures
 * in C. */

#include <stdio.h>

int recursiveFactorial(int n){
    int fact = 1;
    if (n == 0) fact = 1;
    else fact = n * recursiveFactorial(n - 1);
    return fact;
}

int iterativeFactorial(int n){
    int count = 0;
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

int main(){

    int num;
    printf("Please specify an integer to calculate factorial.\n");
    scanf("%d", &num);

    printf("The recursive factorial %d! is: %d\n", num, recursiveFactorial(num) );
    printf("The iterative factorial %d! is: %d\n", num, iterativeFactorial(num) );

    return 0;
}
