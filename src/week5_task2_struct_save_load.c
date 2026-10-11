// week5_task2_struct_save_load.c
// Name: Biloliddin  Surname: Gulomov  Student ID: 251ADB096
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int save_student(const Student *s, const char *filename);  // 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // 0 on success, -1 on error

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    // main() decides what to do on failure; the functions only report it.
    if (save_student(&s1, filename) != 0) {
        fprintf(stderr, "Error: could not save student to %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    if (load_student(filename, &loaded) != 0) {
        fprintf(stderr, "Error: could not load student from %s\n", filename);
        return EXIT_FAILURE;
    }

    // Print the loaded record so we can see it matches the original.
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

// Writes one line "name age gpa" to the file. Returns 0 on success, -1 on error.
int save_student(const Student *s, const char *filename) {
    // Guard against bad arguments so we never dereference NULL.
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;  // file could not be opened for writing
    }

    int result = 0;
    // fprintf returns a negative number if writing failed.
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        result = -1;
    }

    // fclose can also fail (e.g. disk full when flushing), so check it too.
    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// Reads one record "name age gpa" from the file into *out. Returns 0 on success, -1 on error.
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;  // file missing or not readable
    }

    // Read into a temporary so *out is not half-filled when the data is bad.
    Student tmp = {0};
    // %49s leaves room for the terminating '\0' in the 50-byte name array.
    int fields = fscanf(fp, "%49s %d %f", tmp.name, &tmp.age, &tmp.gpa);

    // Close the file in every case, before deciding what to return.
    fclose(fp);

    if (fields != 3) {
        return -1;  // empty file or malformed line
    }

    *out = tmp;
    return 0;
}