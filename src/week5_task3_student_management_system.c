// week5_task3_student_management_system.c
// Name: Biloliddin  Surname: Gulomov  Student ID: 251ADB096
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // Load existing data so records survive between runs.
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                // Only claim the data was saved if it really was.
                if (save_students(students, count) != 0) {
                    fprintf(stderr, "Error: could not save data to %s\n", DATA_FILE);
                    printf("Goodbye!\n");
                } else {
                    printf("Data saved. Goodbye!\n");
                }
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// Loads records from DATA_FILE into arr (at most max). Returns the number loaded.
// A missing or empty file is not an error: it simply gives 0 records.
int load_students(Student arr[], int max) {
    if (arr == NULL || max <= 0) {
        return 0;
    }

    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;  // first run: no file yet
    }

    char line[LINE_LEN];
    int loaded = 0;

    // Checking "loaded < max" first means we never write past the end of arr.
    while (loaded < max && fgets(line, sizeof line, fp) != NULL) {
        // A line without '\n' that is not at end of file was longer than the buffer.
        // Treat it as malformed and throw away the rest of it.
        if (strchr(line, '\n') == NULL && !feof(fp)) {
            int c;
            while ((c = fgetc(fp)) != '\n' && c != EOF) { }
            continue;
        }

        Student tmp;
        memset(&tmp, 0, sizeof tmp);
        // %49[^,] reads a name that may contain spaces but stops at the comma.
        // Keep the line only if all three fields were parsed (blank lines give 0 or EOF).
        if (sscanf(line, "%49[^,],%d,%f", tmp.name, &tmp.id, &tmp.gpa) == 3) {
            arr[loaded] = tmp;
            loaded++;
        }
    }

    fclose(fp);
    return loaded;
}

// Overwrites DATA_FILE with all current records. Returns 0 on success, -1 on error.
int save_students(const Student arr[], int count) {
    if (count < 0 || (count > 0 && arr == NULL)) {
        return -1;
    }

    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    int result = 0;
    for (int i = 0; i < count; i++) {
        // One record per line: name,id,gpa (GPA with two decimals).
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            result = -1;
            break;
        }
    }

    // fclose can fail when it flushes buffered data, so check it too.
    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// Removes leading and trailing spaces/tabs in place and returns the start of the result.
static char *trim(char *s) {
    while (*s == ' ' || *s == '\t') {
        s++;
    }
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t')) {
        s[len - 1] = '\0';
        len--;
    }
    return s;
}

// Asks for name, ID and GPA, validates them and appends the student to arr.
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name_buf[LINE_LEN];
    char id_buf[LINE_LEN];
    char gpa_buf[LINE_LEN];

    // All three prompts are shown first; each one stops early on end of input.
    if (read_line("Enter name: ", name_buf, sizeof name_buf) != 0) {
        return;
    }
    if (read_line("Enter ID: ", id_buf, sizeof id_buf) != 0) {
        return;
    }
    if (read_line("Enter GPA: ", gpa_buf, sizeof gpa_buf) != 0) {
        return;
    }

    // Name: not empty, no comma (it is the field separator in the file),
    // and it must fit in the name array together with the '\0'.
    char *name = trim(name_buf);
    if (name[0] == '\0' || strchr(name, ',') != NULL || strlen(name) >= NAME_LEN) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // ID: the whole text must be an integer that fits in an int.
    char *end = NULL;
    errno = 0;
    long id_value = strtol(id_buf, &end, 10);
    if (end == id_buf || *end != '\0' || errno == ERANGE || id_value < INT_MIN || id_value > INT_MAX) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // GPA: the whole text must be a number in 0.0–4.0.
    // Written as "not (in range)" so that NaN is rejected as well.
    float gpa_value = strtof(gpa_buf, &end);
    if (end == gpa_buf || *end != '\0' || !(gpa_value >= 0.0f && gpa_value <= 4.0f)) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // Everything is valid: store the record and grow the count.
    strcpy(arr[*count].name, name);   // safe: length was checked above
    arr[*count].id = (int)id_value;
    arr[*count].gpa = gpa_value;
    (*count)++;

    printf("Student added successfully!\n");
}

// Prints all students, or a message if there are none.
void list_students(const Student arr[], int count) {
    if (count <= 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}