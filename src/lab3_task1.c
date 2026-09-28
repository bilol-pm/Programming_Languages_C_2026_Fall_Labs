/*
 * Lab 3, Task 1
 * Name: <your name>
 * Student ID: <your student ID>
 *
 * Implement array algorithms:
 *   - find minimum value
 *   - find maximum value
 *   - calculate sum
 *   - calculate average
 *
 * Rules:
 *   - Write separate functions for each operation.
 *   - Work with int arrays.
 *   - Do not include any headers besides <stdio.h>.
 *   - You may assume size >= 1 and that the sum fits in an int.
 *   - Average must return a float and must NOT be truncated
 *     (e.g. {1, 2} -> 1.50, not 1.00).
 *   - Do not modify main.
 *
 * Example:
 *   int arr[] = {1, 2, 3, 4, 5};
 *   min = array_min(arr, 5); // 1
 *   max = array_max(arr, 5); // 5
 *   sum = array_sum(arr, 5); // 15
 *   avg = array_avg(arr, 5); // 3.0
 *
 * Required output:
 *   Min: 5
 *   Max: 30
 *   Sum: 80
 *   Avg: 16.00
 */

#include <stdio.h>

// Function prototypes
int array_min(int arr[], int size);
int array_max(int arr[], int size);
int array_sum(int arr[], int size);
float array_avg(int arr[], int size);

int main(void) {
    int arr[] = {10, 20, 5, 30, 15};
    int size = 5;

    printf("Min: %d\n", array_min(arr, size));
    printf("Max: %d\n", array_max(arr, size));
    printf("Sum: %d\n", array_sum(arr, size));
    printf("Avg: %.2f\n", array_avg(arr, size));

    return 0;
}

// Implement functions below
int array_min(int arr[], int size) {
    // TODO: return smallest element
    return 0; // placeholder
}

int array_max(int arr[], int size) {
    // TODO: return largest element
    return 0; // placeholder
}

int array_sum(int arr[], int size) {
    // TODO: return sum of elements
    return 0; // placeholder
}

float array_avg(int arr[], int size) {
    // TODO: return average as float (avoid integer division)
    return 0.0f; // placeholder
}
