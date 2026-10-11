# 🧩 Week 4 – Dynamic Memory & Structures

This week focuses on using pointers for **dynamic memory allocation**, creating and using **structures**, and combining both ideas to build a small **in-memory database**.  
All programs should compile cleanly without warnings using the provided Makefile.

> ⚙️ **This week is graded by an autograder.** It builds your programs, feeds them input, and compares the output with the expected output. Follow the **prompts and output formats exactly** as written below — spelling, capitalisation, punctuation, spacing and number of decimal places all matter. Programs that produce the right numbers in a different format will fail the tests.

---

## 🧠 Task 1 – Create Dynamic Arrays with `malloc`

### Implement
Write a C program that:
- Asks the user for the number of elements.
- Dynamically allocates memory for an integer array using `malloc`.
- Reads integers from user input and stores them in the array.
- Calculates and prints the sum and average of the entered numbers.
- Frees all allocated memory before the program exits.

The file should be named:  
`src/week4_1_dynamic_array.c`

### Rules
- Always **check** if `malloc` returned a valid pointer.
- Use `sizeof(int)` when allocating memory.
- Avoid memory leaks: every successful `malloc` should have a corresponding `free`.
- Use clear, formatted output with `printf`.

### Required input and output format
| Step | Exact text / format |
|---|---|
| First prompt | `Enter number of elements: ` (no newline after it) |
| Second prompt | `Enter N integers: ` where `N` is the number entered (no newline after it) |
| Sum line | `Sum = <sum>` — printed as a whole number |
| Average line | `Average = <average>` — printed with **2 decimal places** (`%.2f`) |

The average must be computed in floating point (e.g. `7 8` gives `Average = 7.50`, not `7.00`). The integers may be entered on one line separated by spaces or on separate lines.

### Error handling
| Situation | Print (on its own line) | Exit code |
|---|---|---|
| Number of elements is not a number, or is `0` or negative | `Invalid size.` | `1` |
| `malloc` returns `NULL` | `Memory allocation failed.` | `1` |
| One of the integers cannot be read | `Invalid input.` (free the array first) | `1` |

On success the program returns `0`.

### Example
```
Enter number of elements: 5
Enter 5 integers: 10 20 30 40 50
Sum = 150
Average = 30.00
```

---

## 🎓 Task 2 – Define and Use a `struct` (Student Record)

### Implement
Write a C program that defines and uses a structure called `Student`.  
Each student has:
- `char name[50]`
- `int id`
- `float grade`

The program should:
- Declare **two** `Student` variables.
- Assign the values below to their fields in your code (this program reads **no input**).
- Print the information of each student in the format below.

| Variable | `name` | `id` | `grade` |
|---|---|---|---|
| Student 1 | `Alice Johnson` | `1001` | `9.1` |
| Student 2 | `Bob Smith` | `1002` | `8.7` |

The file should be named:  
`src/week4_2_struct_student.c`

### Rules
- Use `struct` keyword for the definition.
- Access fields using the dot (`.`) operator.
- Use `strcpy()` to assign a string to the `name` field.

### Required output format
One line per student, with the grade printed with **1 decimal place** (`%.1f`):
```
Student <k>: <name>, ID: <id>, Grade: <grade>
```

### Expected output (exactly)
```
Student 1: Alice Johnson, ID: 1001, Grade: 9.1
Student 2: Bob Smith, ID: 1002, Grade: 8.7
```

---

## 🗂️ Task 3 – Build an In-Memory Database (Array of Structs)

### Implement
Create a C program that:
- Defines a `struct Student` (same as in Task 2).
- Dynamically allocates memory for an **array of Student records** using `malloc`.
- Prompts the user for the number of students.
- Reads each student’s name, ID, and grade from the user.
- Prints all student records in a formatted table.
- Frees all allocated memory before exit.

The file should be named:  
`src/week4_3_struct_database.c`

### Rules
- Reuse your `struct Student` definition from Task 2.
- Use `malloc(n * sizeof(struct Student))` for allocation, and check the result.
- Names are a **single word without spaces**. Read them with `scanf("%49s", students[i].name)` — the `49` stops a long name from overflowing the 50-byte array.
- Free the allocated memory before program termination.

### Required input and output format
| Step | Exact text / format |
|---|---|
| First prompt | `Enter number of students: ` (no newline after it) |
| Prompt for each student | `Enter data for student K: ` where `K` counts from 1 (no newline after it) |
| Input for each student | `<name> <id> <grade>` separated by whitespace, e.g. `Alice 1001 9.1` |
| After all input | one empty line, then the table |
| Table header | `printf("%-6s %-11s %s\n", "ID", "Name", "Grade");` |
| Each row (in input order) | `printf("%-6d %-11s %.1f\n", id, name, grade);` |

### Error handling
| Situation | Print (on its own line) | Exit code |
|---|---|---|
| Number of students is not a number, or is `0` or negative | `Invalid number.` | `1` |
| `malloc` returns `NULL` | `Memory allocation failed.` | `1` |
| A student's name, ID or grade cannot be read | `Invalid input.` (free the array first) | `1` |

On success the program returns `0`.

### Example
```
Enter number of students: 3
Enter data for student 1: Alice 1001 9.1
Enter data for student 2: Bob 1002 8.7
Enter data for student 3: Carol 1003 9.5

ID     Name        Grade
1001   Alice       9.1
1002   Bob         8.7
1003   Carol       9.5
```

### Optional bonus (not autograded)
You may add extra output **after** the table, for example `Average grade = 9.10` or the top student. Do not change or reorder the required lines above — the tests check those.

---

## 🤖 How the autograder checks your work

For each task the autograder:
1. **Builds** your program with the provided Makefile. Any compiler warning counts as a failed build.
2. **Runs** it with several inputs, including the examples above, other valid inputs and the invalid cases from the error-handling tables.
3. **Compares** the output with the expected output. Prompts appear on the same line as the next output because the input is not echoed — that is expected. Trailing spaces at the end of lines are ignored; everything else must match.
4. **Checks the exit code** (`0` on success, `1` on the listed errors).
5. **Checks memory** with Valgrind: the program must not leak memory or access memory it does not own.

Tips:
- Don't print anything extra (debug messages, “Press any key…”, menus) before or between the required lines.
- Don't wait for extra input at the end of the program.
- Test your program yourself with the examples above before you push.

---

## 💾 Submission Instructions

Your work is submitted through your **GitHub repository** — the autograder runs on the code in it.

1. Make sure all three files are in the `src/` folder with the exact names given above.
2. Commit and push your work:
   ```bash
   git add .
   git commit -m "Week 4 completed"
   git push
   ```
3. Check on GitHub that your latest commit is there and the files are in `src/`.
4. Submit the **URL to your GitHub repository** in Moodle.  
   Example:  
   ```
   https://github.com/yourusername/RTU_Programming_Languages_C_Lab_Fall_2025
   ```

Only work that has been **pushed to GitHub before the deadline** is graded.

---

## 📚 Web Resources on Dynamic Memory & Structs in C

Note: Some of these are not formal, but should provide a reasonable overview.

### Dynamic Memory Allocation
- [GeeksforGeeks — Dynamic Memory Allocation in C (malloc, calloc, realloc, free)](https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)  
- [Programiz — C Dynamic Memory Allocation](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)  
- [Learn-C.org — Dynamic Allocation (interactive)](https://www.learn-c.org/en/Dynamic_allocation)  
- [cppreference — `malloc` (C)](https://en.cppreference.com/w/c/memory/malloc)  *(see also `free` and `realloc` linked on that page)*

### Structures (`struct`)
- [Microsoft Learn — Structure Declarations (C)](https://learn.microsoft.com/en-us/cpp/c-language/structure-declarations?view=msvc-170)  
- [GeeksforGeeks — Structures in C](https://www.geeksforgeeks.org/c/structures-c/)  
- [Programiz — C struct](https://www.programiz.com/c-programming/c-structures)


---

✅ **Reminder:**  
- Your code must compile without warnings using the provided Makefile.  
- Follow the prompts and output formats exactly — the autograder compares them character by character.  
- Comment your code clearly — explain *why* each important step is done.  
- Always free dynamically allocated memory.  
- Programs that crash or leak memory will lose points.
