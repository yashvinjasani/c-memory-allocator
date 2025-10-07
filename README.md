# c-memory-allocator

# Efficient Memory Allocation in C (mymalloc)

### [View the Live Interactive Showcase](https://yashvinjasani.github.io/c-memory-allocator/mymalloc_web_page.html)

---

This project is a custom implementation of a dynamic memory allocator in C, replicating the core functionality of `malloc()` and `free()`. It is designed to be efficient, robust, and to demonstrate a deep understanding of low-level memory management, including strategies to combat fragmentation and handle common allocation errors.

## Testing Strategy

The allocator was validated using a comprehensive suite of tests to ensure correctness, performance, and reliability under stress.

### Test 1: Malloc Reserves Unallocated Memory
* **Requirement:** `malloc()` reserves unallocated memory.
* **Detection Method:** When successful, `malloc()` returns a pointer to an object that does not overlap with any other allocated object.
* **Expected Outcome:** The test should output "no overlap detected" to indicate there was no memory overlap.

### Test 2: Free Deallocates Memory
* **Requirement:** `free()` deallocates the memory.
* **Detection Method:** When `free()` runs successfully, it will make the allocated heap free and the memory can be used by another `malloc`. If a chunk using most of the heap space is freed, another `malloc` big enough to exceed the heap's scope can be allocated.
* **Expected Outcome:** `Test2.c` should run successfully and should not give any error.

### Test 3: Coalescing Adjacent Free Blocks
* **Requirement:** `malloc()` and `free()` arrange so that adjacent free blocks are coalesced.
* **Detection Method:** Allocate chunks until the heap is almost full, then free two chunks back-to-back and try to allocate space as big as both deallocated chunks combined.
* **Expected Outcome:** `Test3.c` should run successfully and should not give any error.

### Test 4: Error Detection and Reporting
* **Requirement:** Detect and report errors in `free()` usage.
* **Detection Method:** Use `free()` with a pointer not obtained by `malloc`, an address which is not the start of the chunk, and call `free()` twice.
* **Expected Outcome:** `Test4_1.c`, `Test4_2.c`, and `Test4_3.c` should each output an error.

### Test 5: Leak Detection and Reporting
* **Requirement:** Leaked objects are detected and reported.
* **Detection Method:** Do not free chunks that have been allocated by `malloc`.
* **Expected Outcome:** `Test5.c` should report how many bytes are leaked.

---

## How to Compile and Run

To compile all test executables, use the provided Makefile:
```bash
make all

To run a specific test:

```bash
./[Test_file_name]
```
To clean up all compiled object files and executables:
```bash
make clean
```
---
Author

Yashvin Jasani 

LinkedIn: www.linkedin.com/in/yashvin-jasani-61190a2a4
