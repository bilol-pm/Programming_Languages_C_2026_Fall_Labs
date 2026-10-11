// week5_task1_file_io.c
// Name: Biloliddin  Surname: Gulomov  Student ID: 251ADB096
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char* argv[]) {
  FILE* fp = NULL;
  const char* filename = DEFAULT_FILENAME;
  char line[LINE_LEN];
  int line_count = 0;

  // BONUS: use the file name from the command line if one was given.
  if (argc > 1) {
    filename = argv[1];
  }

  // --- Part 1: write two lines to the file ---
  printf("Writing lines to %s...\n", filename);
  fp = fopen(filename, "w");
  if (fp == NULL) {
    // fopen can fail (no permission, bad path), so never use fp without
    // checking.
    perror(filename);
    return EXIT_FAILURE;
  }
  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");
  // Close so the data is flushed to disk before we read it back.
  fclose(fp);

  // --- Part 2: read the same file back line by line ---
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror(filename);
    return EXIT_FAILURE;
  }
  printf("Reading contents:\n");
  // fgets returns NULL at end of file, which ends the loop.
  while (fgets(line, LINE_LEN, fp) != NULL) {
    printf("%s", line);
    line_count++;
  }
  fclose(fp);

  // BONUS: report how many lines were read.
  printf("Lines read: %d\n", line_count);

  return EXIT_SUCCESS;
}