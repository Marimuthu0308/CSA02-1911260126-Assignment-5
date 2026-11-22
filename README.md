# CSA02-1911260126-Assignment-5
# CSA02 – C Programming
## Assignment 5 – Modular, Memory-Aware and Persistent Program Engineering

**Student Name:** MARIMUTHU  
**Register Number:** 1911260126  
**Course Outcome:** CO5  
**Maximum Marks:** 50  
**Compiler:** GCC  
**Repository:** https://github.com/Marimuthu0308/CSA02-1911260126-Assignment-5

---

## Assignment Overview

This assignment focuses on designing and implementing a modular C program for a District Blood Bank Network.

The system manages donor details and blood-stock records while demonstrating important C programming concepts such as functions, recursion, pointers, dynamic memory allocation, file handling, and memory safety.

## Objectives

- Design a program using modular functions.
- Implement recursive algorithms and compare their efficiency.
- Understand pointers and pointer arithmetic.
- Allocate and manage memory dynamically.
- Store and retrieve records using text and binary files.
- Handle invalid and adversarial inputs safely.
- Compare program performance and memory usage.

---

## Part A – Design & Pseudocode (25 Marks)

### Task A1 – Decompose the Program into Functions

- Identify the functions required for the blood bank system.
- Prepare a structure chart.
- Define function prototypes and parameters.
- Demonstrate how a function can return multiple values.
- Compare pointer parameters and structure return methods.

### Task A2 – Design with Recursion

- Develop recursive pseudocode for digital root.
- Implement fast power using recursion.
- Trace recursive calls and the call stack.
- Compare linear recursion and halving recursion.
- Explain recursion risks and iterative alternatives.

### Task A3 – Design with Pointers

- Demonstrate pointer arithmetic.
- Explain pointer operations using an array.
- Create a function that returns a pointer to the lowest-stock element.
- Design a command-line interface for blood bank operations.

### Task A4 – Design Dynamic Memory Use

- Design a growable donor list.
- Use `realloc()` to increase capacity.
- Explain memory leaks, dangling pointers, and double free.
- Compare fixed-size growth and capacity doubling.

### Task A5 – Design File Storage

- Store donor records in a text file.
- Store stock records in a binary file.
- Explain the advantages of text and binary storage.
- Demonstrate updating a binary record in place.

---

## Part B – Implementation & Experimental Investigation (25 Marks)

### Task B1 – Implement and Instrument Recursive Functions

- Implement linear power and fast power.
- Count recursive function calls.
- Compare the number of calls for different exponents.
- Test base cases and odd/even exponent cases.
- Implement an iterative alternative.

### Task B2 – Engineer Adversarial Inputs

- Test long donor names.
- Handle missing or read-only files.
- Validate incorrect command-line arguments.
- Handle invalid blood groups and quantities.
- Use AddressSanitizer to check memory safety.

### Task B3 – Text File vs Binary File

- Write and read donor records using text files.
- Write and read donor records using binary files.
- Compare logical fields in both formats.
- Measure file size and read/write time.
- Update the 50,000th record.
- Compare text and binary file performance.

### Task B4 – Final Engineering Decision

- Implement a growable donor list.
- Demonstrate dynamic memory allocation using `realloc()`.
- Release allocated memory safely.
- Generate a nightly donor eligibility report.
- Compare memory and runtime strategies.
- Select a suitable storage strategy for a large blood bank network.

---

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Standard: C11
- File Handling: Text and Binary Files
- Memory Management: Dynamic Memory Allocation
- Testing: AddressSanitizer

---

## Compilation and Execution

Compile a C program using GCC:

```bash
gcc -std=c11 -Wall -Wextra -pedantic source_file.c -o program
```

Run the program on Windows:

```bash
program.exe
```

Example for Task B1:

```bash
gcc -std=c11 -Wall -Wextra -pedantic task_b1.c -o task_b1
task_b1.exe
```

Example for Task B4:

```bash
gcc -std=c11 -Wall -Wextra -pedantic task_b4.c -o task_b4
task_b4.exe
```

Replace the source filename with the actual filename in the repository.

---

## Memory Safety Testing

Compile the program with AddressSanitizer:

```bash
gcc -std=c11 -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer task_b4.c -o task_b4_asan
```

Run the generated executable and check for:

- Out-of-bounds memory access
- Use-after-free errors
- Memory leaks
- Incorrect memory allocation

---

## Expected Output – Growable Donor List

```text
added 7001 (O+): size = 1, capacity = 2
added 7002 (A+): size = 2, capacity = 2
added 7003 (B-): size = 3, capacity = 4
added 7004 (AB+): size = 4, capacity = 4
added 7005 (O-): size = 5, capacity = 8
```

This output demonstrates how the donor list increases its capacity when the allocated memory becomes full.

---

## Experimental Results

The following measurements must be completed using the actual program execution:

- Text and binary file sizes.
- Text and binary read/write times.
- Time required to update the 50,000th record.
- Recursion limit test results.
- Peak memory usage.
- Runtime of different donor-storage strategies.
- AddressSanitizer or Valgrind results.

Actual measurements depend on the computer, compiler, and storage device. Do not include fabricated values.

---

## Conclusion

This assignment demonstrates modular C programming and efficient memory management through a District Blood Bank Network.

It covers functions, recursion, pointers, dynamic memory allocation, text and binary file handling, input validation, and memory-safety testing.

The assignment also compares different engineering approaches and helps identify suitable strategies for managing donor records efficiently in a large blood bank network.

---

**Submitted by:** MARIMUTHU  
**Register Number:** 1911260126
