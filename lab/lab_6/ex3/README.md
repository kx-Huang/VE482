# README

- name: ex3
- author: Kexuan Huang
- date: 2021.11.4
- description: plugin-based programming
- build:
  ```sh
  #!/bin/bash
  make
  ```
  - generate binary: `l6`, `l6_memory_check`
  - generate dynamic library: `plugins/txt.so`, `plugins/csv.so`
- run:
  ```bash
  #!/bin/bash
  ./l6 test/rand_int.txt inc
  ```
