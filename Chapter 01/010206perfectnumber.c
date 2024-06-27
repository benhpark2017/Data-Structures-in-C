/**Solution to Horowitz's Data Structures, Chapter 1, Section 2, Exercise 6.
 * FYI: for numbers up to 100,000, the numbers where n matches the sum of
 * divisors are 6, 28, 496, 8128.
 */


#include <stdio.h>

int isPerfectNumber(int n) {
    int sum = 0;

    for (int i = 1; i < n; i++)
        if (n % i == 0)
            sum += i;

    return sum == n;
}

int main() {
    int n;

    // Input the positive number
    printf("Enter a positive number: ");
    scanf("%d", &n);

    // Check if it is a perfect number
    if (isPerfectNumber(n))
        printf("\n%d is a perfect number.\n", n);
    else printf("\n%d is not a perfect number.\n", n);

    return 0;
}
