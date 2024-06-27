/**Solutions to Chapter 1, Section 2, Exercise 9 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>

int iterativeBinomialCoeff(int n, int m){
    if (m < 0 || m > n) return 0; //invalid input, return 0
    int result = 1;
    for (int i = 1; i <= m; i++){
        result *= n - (m - i);
        result /= i;
    }
    return result;
}

int recursiveBinomialCoeff(int n, int m){
    if (m < 0 || m > n) return 0; //invalid input, return 0

    int result = 1;
    if (m == 0 || m == n) return 1; //basis case

    result = recursiveBinomialCoeff(n - 1, m)
              + recursiveBinomialCoeff(n - 1, m - 1);
    return result;
}

int main(){
    int n = 1, m = 1;
    printf("Please specify the integer n.\n");
    scanf("%d", &n);

    printf("Please specify the integer m.\n");
    scanf("%d", &m);

    printf("The iterative binomial coefficient %d choose %d is %d\n", n, m, iterativeBinomialCoeff(n, m));
    printf("The recursive binomial coefficient %d choose %d is %d\n", n, m, recursiveBinomialCoeff(n, m));
}
