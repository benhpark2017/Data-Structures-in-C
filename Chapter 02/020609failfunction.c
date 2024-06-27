/**Solutions to Chapter 2, Section 6, Exercise 9 of Horowitz's Fundamentals of
 * Data Structures in C. The pattern of data type string is passed through the
 * failureFunction.
 */

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 20

int failure[MAX_SIZE];
void failureFunction(char *pattern);

int main() {
    int t;
    char patternOne[] = "aaaab";
    char patternTwo[] = "ababaa";
    char patternThree[] = "abaabaab";
    failureFunction(patternOne);
    for (t = 0; t < strlen(patternOne); ++t)
        printf("%d  ", failure[t]);
    printf("\n");

    failureFunction(patternTwo);
    for (t = 0; t < strlen(patternTwo); ++t)
        printf("%d  ", failure[t]);
    printf("\n");

    failureFunction(patternThree);
    for (t = 0; t < strlen(patternThree); ++t)
        printf("%d  ", failure[t]);
    printf("\n");

    return 0;
}

void failureFunction(char *pattern) {
    int n = strlen(pattern);
    failure[0] = -1;
    for (int j = 1; j < n; j++) {
        int i = failure[j - 1];
        while ((pattern[j] != pattern[i+1]) && (i >= 0))
            i = failure[i];
        if (pattern[j] == pattern[i + 1])
            failure[j] = i + 1;
        else
            failure[j] = -1;
    }
}
