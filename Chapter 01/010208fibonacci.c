/**Solutions to Chapter 1, Section 2, Exercise 8 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>

int recursiveFibonacci(int n){
    int result = 0;
    if (n <= 1) result = n;
    else result = recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
    return result;
}

int iterativeFibonacci(int n){
    int result;
    if (n <= 1) result = n;

    int fibonacci[n+1];
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    for (int i = 2; i <= n; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    return fibonacci[n];
}

int main(){
    int num;
    printf("Please specify an integer to calculate the number"
           " in the Fibonacci sequence.\n");
    scanf("%d", &num);

    printf("The number %d in the Fibonacci sequence is: %d\n", num, recursiveFibonacci(num - 1));
    printf("The number %d in the Fibonacci sequence is: %d\n", num, iterativeFibonacci(num - 1));

    return 0;
}
