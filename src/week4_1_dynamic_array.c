#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;

  /* Prompt has NO newline, as required by the lab. */
  printf("Enter number of elements: ");

  /* scanf returns how many items it read. If it is not 1, the user typed
     something that is not a number (or input ended). Also reject n <= 0. */
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  /* Allocate n integers; sizeof(int) keeps this portable. */
  int* arr = malloc((size_t)n * sizeof(int));
  if (arr == NULL) { /* always check malloc */
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  long long sum = 0; /* wider type avoids overflow */
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input.\n");
      free(arr); /* free BEFORE exiting -> no leak */
      return 1;
    }
    sum += arr[i];
  }

  /* Cast to double so the division is floating point (7 8 -> 7.50). */
  double average = (double)sum / n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  free(arr); /* one malloc -> one free */
  return 0;
}