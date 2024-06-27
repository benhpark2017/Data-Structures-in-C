/**Solutions to Chapter 1, Section 2, Exercise 11 of Horowitz's Data Structures
 * in C.*/

#include <stdio.h>

// Function to move a disk from source tower to destination tower
void moveDisk(int disk, char source, char destination) {
    printf("Move disk %d from tower %c to tower %c\n", disk, source, destination);
}

// Recursive function to solve Towers of Hanoi problem
void towersOfHanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        moveDisk(1, source, destination);
        return;
    }

    // Move n-1 disks from source to auxiliary tower
    towersOfHanoi(n - 1, source, destination, auxiliary);

    // Move the nth disk from source to destination tower
    moveDisk(n, source, destination);

    // Move the n-1 disks from auxiliary to destination tower
    towersOfHanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n;

    // Get the number of disks from the user
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    // Validate input
    if (n <= 0) {
        printf("Number of disks should be greater than 0.\n");
        return 1;
    }

    // Call the Towers of Hanoi function
    towersOfHanoi(n, 'A', 'B', 'C');

    return 0;
}
