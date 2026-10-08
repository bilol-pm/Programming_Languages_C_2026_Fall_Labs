#include <stdio.h>
#include <string.h>

/* A Student groups related data into one custom type. */
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  struct Student s1;
  struct Student s2;

  /* Arrays cannot be assigned with '=', so copy the string with strcpy. */
  strcpy(s1.name, "Alice Johnson");
  s1.id = 1001;
  s1.grade = 9.1f;

  strcpy(s2.name, "Bob Smith");
  s2.id = 1002;
  s2.grade = 8.7f;

  /* Dot operator accesses fields; %.1f prints 1 decimal place. */
  printf("Student 1: %s, ID: %d, Grade: %.1f\n", s1.name, s1.id, s1.grade);
  printf("Student 2: %s, ID: %d, Grade: %.1f\n", s2.name, s2.id, s2.grade);

  return 0;
}