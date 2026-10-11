# 🧠 Week 5 – Files & Modular Programming

This week we explore **file input/output (I/O)** and **modular program design** in C.
You will learn to read and write files, store structured data, and create a simple management system that persists between runs.

Pull the new starter files into your course repository: they go in the `src/` folder, and the
course `Makefile` already knows about them. Build with `make lab5`; the programs are created in `bin/`.

> ⚙️ **Your work is checked by an autograder.** It compiles each program with the same flags as
> the course Makefile (`gcc -std=c11 -Wall -Wextra -Wpedantic -O2`), runs it in an empty folder, feeds it input, and inspects
> both the console output and the files it creates. Follow the **exact messages, file names,
> file formats and function signatures** given below — they are part of the specification.
> The autograder also simulates a failing `fopen()` to check that you handle `NULL` correctly.

---

## 🧾 Task 1: Read and Write Data from Files

### Implement
Complete `src/week5_task1_file_io.c` so that it:
1. Opens a text file for writing (default name: `data.txt`).
2. Writes **at least two** lines of text into it using `fprintf()`.
3. Closes the file properly.
4. Opens the same file again for reading.
5. Reads its contents line by line using `fgets()` and prints each line to the console.

### Rules
- Always check that the file pointer returned by `fopen()` is **not `NULL`**. If it is, print an
  error message (e.g. with `perror()`) and return a **non-zero** exit code.
- Print `Writing lines to <filename>...` before writing and `Reading contents:` before reading.
- Close every opened file using `fclose()`.
- Keep the text short (2–3 lines). The program must **not** wait for keyboard input.
- The program must compile without warnings.

### Bonus (not graded, but recommended)
- Accept an optional file name as a **command-line argument**: `./bin/week5_task1_file_io notes.txt`
  writes to and reads from `notes.txt` instead of `data.txt`.
- Count the lines read and print `Lines read: N` at the end.

### Example
```bash
$ ./bin/week5_task1_file_io
Writing lines to data.txt...
Reading contents:
Hello, file I/O in C!
This is another line.
Lines read: 2
```

---

## 🧾 Task 2: Save and Load Structured Records

### Implement
Complete `src/week5_task2_struct_save_load.c` so that it:
1. Uses the provided `Student` type (a `struct Student` with a name, age, and GPA).
2. Saves one student record to `student.txt` using `save_student()`.
3. Loads that record back from the file using `load_student()`.
4. Prints the loaded record to confirm that it matches the original.

### Required function signatures
```c
int save_student(const Student *s, const char *filename);  // returns 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // returns 0 on success, -1 on error
```
Returning a status code lets `main()` (and the autograder) know whether the operation worked.

### Rules
- Save the data as **one line** in the text format `name age gpa`, e.g. `Alice 21 3.75`.
  For this task the name is a single word (no spaces).
- Use `fprintf()` for writing and `fscanf()` for reading.
- In `load_student()`, check that `fscanf()` returned **3** (all three fields read). Use a field
  width for the name (`%49s`) so a long name cannot overflow the array.
- Return `-1` if the file cannot be opened or the data cannot be read. Do not call `exit()` inside
  these functions — let `main()` decide what to do.
- Avoid global variables.
- Print the loaded record exactly in the format `Loaded student: <name>, <age>, GPA <gpa>`
  with the GPA printed using `%.2f`.

### Example
```bash
$ ./bin/week5_task2_struct_save_load
Saving student to file...
Loading student from file...
Loaded student: Alice, 21, GPA 3.75
```

---

## 🧾 Task 3: Mini-Project – Student Management System with File Persistence

### Implement
Complete `src/week5_task3_student_management_system.c` so that it:
1. Allows listing, adding, and saving students.
2. Uses an array of `Student` (name, ID, GPA) to store data in memory.
3. Loads existing data from `students.txt` at startup.
4. Saves all students back to the file before exiting.
5. Displays a simple text-based menu with options (list / add / save and exit).

The menu loop and a safe input helper `read_line()` are already provided — you do not need to
change `main()` except where it is marked `TODO`.

### Required function signatures
```c
int  load_students(Student arr[], int max);              // returns number of records loaded
int  save_students(const Student arr[], int count);      // returns 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
```

### File format (`students.txt`)
One record per line, fields separated by commas, in the order **name, ID, GPA**:
```text
Alice,101,3.80
Mary Ann,102,3.50
```
Names may contain spaces but not commas. Write the GPA with `%.2f`.
Tip: read each line with `fgets()` and parse it with `sscanf(line, "%49[^,],%d,%f", ...)`.

### Rules
- `load_students()`:
  - If `students.txt` does **not exist**, this is not an error (first run) — return `0`.
  - An **empty** file must also load `0` students without errors.
  - Skip blank or malformed lines.
  - Never load more than `max` records (do not overflow the array).
- `save_students()` overwrites the file with all current records.
- `add_student()`:
  - Prompt with `Enter name: `, `Enter ID: `, `Enter GPA: ` (use `read_line()`).
  - Reject an empty name, a name containing a comma, a non-numeric ID, or a GPA outside
    `0.0`–`4.0` by printing `Invalid input. Student not added.`
  - If the array is full, print `Cannot add more students (limit reached).`
  - On success print `Student added successfully!`
- `list_students()`: print one student per line showing ID, name and GPA (`%.2f`).
  If there are no students, print `No students found.`
- Option 3 (or end of input) saves and prints `Data saved. Goodbye!`
- Maintain clean and readable code with comments, and compile without warnings.

### Example
```text
$ ./bin/week5_task3_student_management_system
Loaded 0 student(s) from students.txt

=== Student Management System ===
1. List students
2. Add student
3. Save and Exit
Select an option: 2
Enter name: Alice
Enter ID: 101
Enter GPA: 3.8
Student added successfully!

=== Student Management System ===
1. List students
2. Add student
3. Save and Exit
Select an option: 1
ID    Name                 GPA
101   Alice                3.80

=== Student Management System ===
1. List students
2. Add student
3. Save and Exit
Select an option: 3
Data saved. Goodbye!
```

---

## 💾 Bonus Task 4: Binary File Version (Advanced)

### Implement
Extend **Task 2** to save and load the `Student` record in **binary format** using `fwrite()` and
`fread()`. Complete the starter file `src/week5_task4_struct_binary_io.c`.

Your program should:
1. Use the same `Student` type as in Task 2.
2. Save the struct directly in binary format to `student.bin`.
3. Load the struct back and print its contents.
4. Also save the same record in text format to `student.txt` and compare the two file sizes.

### Required function signatures
```c
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // size in bytes, -1 on error
```

### Rules
- Use modes `"wb"` (write binary) and `"rb"` (read binary).
- Use `fwrite(s, sizeof(Student), 1, fp)` and `fread(out, sizeof(Student), 1, fp)`, and check that
  each call returns `1`.
- Implement `file_size()` with `fseek(fp, 0, SEEK_END)` and `ftell(fp)`.
- Print confirmation messages during save and load.
- Check file pointer validity before any file operations.

### Example
```bash
$ ./bin/week5_task4_struct_binary_io
Saving student in binary format...
Loading student from binary file...
Loaded student: Alice, 21, GPA 3.75
Text file size: 14 bytes
Binary file size: 60 bytes
```

> 🔍 **Think about it:** the binary size is `sizeof(Student)` — the full 50-byte name array plus
> padding plus the `int` and `float` — so it is usually *larger* than the text version here. It
> can also differ between compilers and machines (padding, `int` size, byte order). That is why
> binary files are fast but not portable. Zero-initialise the struct (`Student s = {0};`) so
> unused name bytes do not write leftover memory to disk.

---

## 🛠️ Building and running

Use the course `Makefile` from the repository root. It builds only the sources that exist, so
Task 4 is included automatically once you create it.

| Command | What it does |
|---|---|
| `make lab5` | Compile all Week 5 programs into `bin/` |
| `make run-lab5` | Compile and run all Week 5 programs in order (Task 3 waits for menu input) |
| `./bin/week5_task3_student_management_system` | Run a single program |
| `make debug` | Rebuild everything with `-g` for debugging with `gdb` |
| `make clean` | Remove `bin/` |

The programs create `data.txt`, `student.txt`, `students.txt` and `student.bin` in the folder you
run them from. These are generated files: do not commit them (add them to `.gitignore`).

---

## 📚 Authoritative Resources

### File I/O in C
- **GNU C Library – I/O on Streams**
  https://www.gnu.org/software/libc/manual/html_node/I_002fO-on-Streams.html
- **ISO C `stdio.h` Reference (cppreference)**
  https://en.cppreference.com/w/c/io

### Structs and Modular Programming
- **C struct (Programiz)**
  https://www.programiz.com/c-programming/c-structures
- **Header Files in C (GeeksforGeeks)**
  https://www.geeksforgeeks.org/c/header-files-in-c-cpp-and-its-uses/

### Binary Files
- **C File I/O (TutorialsPoint)**
  https://www.tutorialspoint.com/cprogramming/c_file_io.htm
- **`fwrite` reference (cplusplus.com)**
  https://cplusplus.com/reference/cstdio/fwrite/

---

## ✅ Learning Outcomes

After completing Week 5, you will be able to:
- Read and write data to text and binary files in C.
- Detect and handle file errors (`NULL` from `fopen()`, failed reads).
- Persist and reload structured records using `struct`.
- Implement a small modular project with file persistence, split into well-defined functions.
- Compare text and binary file storage formats and explain their trade-offs.

---

## 🧩 Submission Instructions

Submit the **URL of your GitHub repository** in the Moodle submission field.

1. Put your files in the `src/` folder of your course repository (keep the exact file names):
   - `src/week5_task1_file_io.c`
   - `src/week5_task2_struct_save_load.c`
   - `src/week5_task3_student_management_system.c`
   - *(optional bonus)* `src/week5_task4_struct_binary_io.c`
2. Fill in the header comment with your **Name**, **Surname**, and **Student ID** in every file.
3. Check that everything compiles **without errors or warnings**:
   ```bash
   make clean
   make lab5
   ```
4. **Commit and push** before the deadline. The autograder grades the last commit pushed
   **before the deadline** on your default branch; later commits are ignored.
5. Make sure the repository is accessible to the instructor (public, or the instructor is added as
   a collaborator if it is private).
