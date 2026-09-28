/*
 * Lab 3, Task 2
 * Name: Biloliddin Gulomov
 * Student ID: 251ADB096
 *
 * Practice using pointers as function parameters.
 * Implement:
 *   - swap (exchange values of two ints)
 *   - modify_value (multiply given int by 2)
 *
 * Rules:
 *   - Use pointers to modify variables in the caller.
 *   - Functions must not print anything.
 *   - swap(&a, &a) must leave a unchanged.
 *   - Do not modify main.
 *
 * Example:
 *   int a = 3, b = 7;
 *   swap(&a, &b);     // now a = 7, b = 3
 *   modify_value(&a); // now a = 14
 *
 * Required output:
 *   Before swap: a=3, b=7
 *   After swap: a=7, b=3
 *   After modify_value: a=14
 */

#include <stdio.h>

// Function prototypes
void swap(int *x, int *y);
void modify_value(int *x);

int main(void) {
    int a = 3, b = 7;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After swap: a=%d, b=%d\n", a, b);

    modify_value(&a);
    printf("After modify_value: a=%d\n", a);

    return 0;
}

// Implement functions below
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void modify_value(int *x) {
    *x = *x * 2;
}