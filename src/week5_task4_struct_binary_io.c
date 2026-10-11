// week5_task4_struct_binary_io.c   (BONUS)
// Name: Biloliddin  Surname: Gulomov  Student ID: 251ADB096
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

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
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

int main(void) {
    Student s1 = {0};          // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        fprintf(stderr, "Error: could not save %s\n", bin_file);
        return EXIT_FAILURE;
    }

    // Save the same record as text ("name age gpa") so the two file sizes can be compared.
    FILE *tf = fopen(txt_file, "w");
    if (tf == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }
    if (fprintf(tf, "%s %d %.2f\n", s1.name, s1.age, s1.gpa) < 0) {
        fprintf(stderr, "Error: could not write %s\n", txt_file);
        fclose(tf);
        return EXIT_FAILURE;
    }
    if (fclose(tf) != 0) {
        fprintf(stderr, "Error: could not close %s\n", txt_file);
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Error: could not load %s\n", bin_file);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));

    return EXIT_SUCCESS;
}

// Writes the whole struct to the file in binary. Returns 0 on success, -1 on error.
int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "wb");   // "wb" = write, binary mode
    if (fp == NULL) {
        return -1;
    }

    int result = 0;
    // fwrite returns the number of items written; we asked for exactly 1.
    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        result = -1;
    }

    // fclose flushes buffered data and can fail too, so check it.
    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// Reads one struct from a binary file into *out. Returns 0 on success, -1 on error.
int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");   // "rb" = read, binary mode
    if (fp == NULL) {
        return -1;
    }

    // Read into a temporary so *out stays untouched if the file is too short.
    Student tmp = {0};
    size_t items = fread(&tmp, sizeof(Student), 1, fp);

    // Close the file in every case, before deciding what to return.
    fclose(fp);

    if (items != 1) {
        return -1;   // file shorter than one record
    }

    // A damaged file might not contain '\0' in the name, so force a terminator.
    tmp.name[MAX_NAME_LEN - 1] = '\0';

    *out = tmp;
    return 0;
}

// Returns the size of the file in bytes, or -1 on error.
long file_size(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // Jump to the end of the file; ftell then tells us the offset, i.e. the size.
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);   // returns -1 on error
    fclose(fp);

    return size;
}