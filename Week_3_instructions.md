# Lab 3 – Arrays, Pointers, and Strings

In this lab you will practice three core topics in C programming:
1. Array processing (min, max, sum, average)
2. Pointers as function parameters (swap, modify)
3. Manual string handling (strlen, strcpy)

You will work on **three separate C source files**:

- `src/lab3_task1.c`
- `src/lab3_task2.c`
- `src/lab3_task3.c`

Each file already contains:
- A comment header where you fill in your **Name** and **Student ID**
- Function prototypes
- A `main` function with example tests (**do not modify `main`**)
- Placeholders (`// TODO`) where you need to write code

---
## Acquiring Lab 3 Files in Codespaces

There are three ways to get the new Lab 3 files into your Codespace.
Choose the method that fits your situation.

---

### Option A – Update Your Fork Using GitHub "Sync Fork" Button (Recommended)

If you don't want to use terminal commands in Codespaces, you can update your fork directly on the GitHub website.

#### Steps

1. Open your fork of the course repository on GitHub (e.g. `https://github.com/student123/Programming_Languages_C_2026_Fall_Labs`).
2. On the repository page, you should see a **"Sync fork"** button near the top of the page.
   - If your fork is behind the teacher's repository, GitHub will show something like:
     *"This branch is 3 commits behind mareksxb:main"*.
3. Click the **"Sync fork"** button, then click **"Update branch"** to bring your fork up to date.
4. After that, go back to your Codespace and run:
   ```bash
   git pull origin main --no-rebase
   ```
   This will download the updated files from your fork into your Codespace.

⚠️ **Note:** The "Sync fork" method updates your fork on GitHub, but you still need to run
`git pull origin main` inside your Codespace to get the new files locally.

### Option B – Update Your Existing Codespace

If you already forked the course repository in Week 1 and created a Codespace, you can simply **pull the new files**.

1. Open your existing Codespace.
2. Make sure you are on the `main` branch from the terminal:
   ```bash
   git checkout main
   ```
3. Check that you have the teacher's repository set as upstream:
   ```bash
   git remote -v
   ```
   You should see something like this in the output:
   ```
   origin    https://github.com/student123/Programming_Languages_C_2026_Fall_Labs.git (fetch)
   upstream  https://github.com/mareksxb/Programming_Languages_C_2026_Fall_Labs.git (fetch)
   ```
   If you do not see `upstream`, add it manually:
   ```bash
   git remote add upstream https://github.com/mareksxb/Programming_Languages_C_2026_Fall_Labs.git
   ```
4. Pull the new files from the teacher repository:
   ```bash
   git pull upstream main
   ```
5. After this, you should see the new files:
   ```
   src/lab3_task1.c
   src/lab3_task2.c
   src/lab3_task3.c
   Week_3_instructions.md
   ```

### Option C – Create a New Fork and Codespace (Only if Needed)

Use this option **only if**:
- You accidentally deleted your Codespace, **or**
- Your fork is broken and cannot be updated.

Steps:

1. Go to the [teacher repository](https://github.com/mareksxb/Programming_Languages_C_2026_Fall_Labs).
2. Click **Fork** to create your own copy under your GitHub account.
3. When forking, GitHub may ask for a repository name.
   - Example: if your GitHub username is `student123`, the default fork name will be
     `student123/Programming_Languages_C_2026_Fall_Labs`.
   - If you already created a fork in Week 1 or Week 2, you will need to **rename this new fork** (e.g. `Programming_Languages_C_2026_Fall_Labs_v2`) to avoid conflicts.
4. Open the newly forked repository in GitHub and click:
   **Code → Codespaces → Create Codespace on main**
5. You will now have a fresh Codespace with all files, including Lab 3.

**NOTE:** Option A is much preferred. At some point in your future jobs you will not be allowed to just fork anytime you need a fresh copy - that is highly unprofessional.

---

## General Rules (apply to all tasks)

- Fill in the header of every file in exactly this format (the grader reads it):
  ```c
   * Name: Jane Doe
   * Student ID: 123ABC456
  ```
- **Do not change** function names, parameter lists, return types, or the provided `main`.
- Do not add extra `printf` calls (no debug output) — the output is checked automatically.
- Your code must compile without errors.
  Warnings should also be fixed.
- Your functions will also be tested with **hidden inputs** that are different from the examples in `main`, so make sure they work in general, not just for the example values.

---

## Task 1 – Array Algorithms (`lab3_task1.c`)

Implement the following functions for integer arrays:
- `int array_min(int arr[], int size)` – return the smallest element
- `int array_max(int arr[], int size)` – return the largest element
- `int array_sum(int arr[], int size)` – return the sum of elements
- `float array_avg(int arr[], int size)` – return the average as a float

**Rules:**
- Do not include any headers besides `<stdio.h>` (this means no `<limits.h>` either).
- Write separate functions for each operation.
- You may assume `size >= 1` (the array is never empty) and that the sum fits in an `int`.
- The array may contain negative numbers.
- `array_avg` must return the **exact** average, not a truncated one (e.g. for `{1, 2}` the result must be `1.50`, not `1.00`). Watch out for integer division.

**Example:**
```c
int arr[] = {10, 20, 5, 30, 15};
printf("Min: %d\n", array_min(arr, 5));  // 5
printf("Max: %d\n", array_max(arr, 5));  // 30
printf("Sum: %d\n", array_sum(arr, 5));  // 80
printf("Avg: %.2f\n", array_avg(arr, 5));// 16.00
```

**Required output** of `lab3_task1.c`:
```
Min: 5
Max: 30
Sum: 80
Avg: 16.00
```

## Task 2 – Pointers in Function Parameters (`lab3_task2.c`)

Practice using pointers to modify values inside functions.

### Implement
- `void swap(int *x, int *y)` – swap the values of two integers
- `void modify_value(int *x)` – multiply the value by 2

### Rules
- Functions must modify the caller's variables via pointers.
- Functions must not print anything.
- `swap` must also work correctly when both pointers point to the same variable (e.g. `swap(&a, &a)` leaves `a` unchanged).

### Example
```c
int a = 3, b = 7;
printf("Before swap: a=%d, b=%d\n", a, b);

swap(&a, &b);
printf("After swap: a=%d, b=%d\n", a, b);

modify_value(&a);
printf("After modify_value: a=%d\n", a);
```

**Required output** of `lab3_task2.c`:
```
Before swap: a=3, b=7
After swap: a=7, b=3
After modify_value: a=14
```

## Task 3 – String Handling (`lab3_task3.c`)

Write your own versions of two basic string functions:

### Implement
- `int my_strlen(const char *str)` – return the number of characters (not counting `'\0'`)
- `void my_strcpy(char *dest, const char *src)` – copy the string `src` into `dest`, **including the terminating `'\0'`**

### Rules
- Do **not** include `<string.h>` and do not call any library string functions.
- Use loops or pointer arithmetic.
- You may assume `src` is a valid null-terminated string and that the caller has made `dest` large enough to hold it (your function does not need to check this).
- Your functions must also work for the empty string `""` (length 0, copy is an empty string).

### Example
```c
char text[] = "hello";
int len = my_strlen(text);       // 5

char buffer[100];
my_strcpy(buffer, text);
printf("%s\n", buffer);          // hello
```

**Required output** of `lab3_task3.c`:
```
Length: 16
Copy: Programming in C
```

---

## Output Format (Autograder)

Each program is graded automatically in two steps:

1. **Output check** – your file is compiled with the command above and run. Its standard output must match the "Required output" of that task **exactly**:
   - same text, spacing, and capitalization
   - one item per line, every line ending with a newline (`\n`)
   - no extra lines, spaces, or debug prints
   - `main` returns `0`
2. **Hidden tests** – your functions are called directly with additional inputs (e.g. negative numbers, single-element arrays, empty strings). The provided `main` is not used in this step.

Files that are still the original stub (unchanged `// TODO` placeholders) receive 0 points.

## Submit

Submit the link to your repository containing your **modified** `src/lab3_task1.c`, `src/lab3_task2.c`, and `src/lab3_task3.c`. Original stubs will not be counted as valid submissions and therefore will not allow you to take part in the graded task.
