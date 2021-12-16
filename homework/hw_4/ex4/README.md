# README

- path: ex4
- author: Kexuan Huang
- date: 2021.10.24
- description: source code for Ex.4
- usage: creates two threads which increment a common global variable.
- feature: semaphore is used to solve the problem of generating a random and inaccurate output
- Compile and Run:
  ```bash
  #!/bin/bash
  clang cthread.c -o ex4 -lpthread
  ./ex4
  ```
