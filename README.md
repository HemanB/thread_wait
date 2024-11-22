# Nested Locks Without Deadlock

## Objectives

- More creating posix threads (pthreads) and joining on them
- Synchronize for concurrent access to multiple elements, each with their own lock
- Understand risks of deadlock in this scenario
- Implement a locking strategy to avoid deadlock

---



## Overview

This lab builds on what you learned about locking and deadlock.    This
lab focuses on *deadlock*.   As in the other threads labs, you create and initialize some threads and mutexes
with the pthreads API.   Please use the capital-P
variants of the pthreads API
for correct autograding.  They are declared in [mythreads.h](mythreads.h).   E.g., use `Pthread_create` instead of `pthread_create`.

## What to do


There is one program for you complete in this lab: **array.c**. You need to fill
in the functions `update_two` and `create_and_wait_threads`.

---

### `create_and_wait_threads`

This function is to create four threads that invoke `thread_worker`, and then join/wait for all of them to
complete.   Pass one argument to `thread_worker`, a pointer to an integer.   The integer is in the range `[0-3]`
providing an identifier for the thread.    

The start function `thread_worker` is 
declared in `mythreads.h` and is provided in `thread_util.o`.   It calls your `update_two` many times in a loop.  


---

### `update_two`

This function takes two index values for the `array[]` as arguments.   They are different:
one of them is less than the other (by the < operator).   Let us name the lower index `lower` and other `higher`. 
Update `array[lower]` and `array[higher]` as follows. 

```
update_entry(lower);
array[higher] += array[lower];
```

`update_entry` is declared in `mythreads.h` and is provided in `thread_util.o`. 

This update should complete atomically: no other thread updates either of those array elements
while `update_two` is in progress.   

Your locking solution must preserve this atomicity of `update_two`.    It should allow concurrent calls
to `update_two` to execute in parallel when they do not conflict, i.e., they do not violate the atomicity
property.   Your solution should be free of deadlock.  

Note: `update_two` is called concurrently from multiple threads,
and the index values passed may overlap.  `update_two` may be  called with any index in the range `0` to `SIZE-1` in either
of the arguments.   The test harness is designed to induce deadlock if it can occur in your code.

**Hint:** You will use one lock per array element, and write `update_two` to hold locks on both elements
while updating.   You can read up on [Chapter 32 of OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-bugs.pdf) (opens a PDF)
for a guide to preventing deadlock in that scenario.   This scenario is common in atomc database
operations called *transactions*.


During development your program may deadlock, and you may have to type `^C` to
terminate it if it doesn't complete quickly.  Remember you can always run `ps`
in the terminal to see the processes you have running and use the Unix `kill`
command to terminate  instances of the `array` program by process ID.

---

### Local Testing and Submission

Run your program manually for debugging, etc. using the following command

```bash
./array
```

To run the test harness use the following command

```bash
python3 test_kit.py ALL
```

Commit your completed `array.c` and submit to Gradescope in the usual fashion.

