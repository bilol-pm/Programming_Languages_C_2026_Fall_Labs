#include <stdio.h>
#include <stdlib.h>

/* Same struct as in Task 2. */
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  int n;

  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }

  /* One block of memory holding n Student records. */
  struct Student* students = malloc((size_t)n * sizeof(struct Student));
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);

    /* %49s leaves room for '\0' in name[50] -> prevents buffer overflow.
       scanf must return 3 (name, id, grade all read successfully). */
    if (scanf("%49s %d %f", students[i].name, &students[i].id,
              &students[i].grade) != 3) {
      printf("Invalid input.\n");
      free(students); /* free before exit */
      return 1;
    }
  }

  /* One empty line, then the table. */
  printf("\n");
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  free(students);
  return 0;
}