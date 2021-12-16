# README

- file: ex1
- author: Kexuan Huang
- date: 2021.10.23
- description: source code for Lab 5 Ex.1
- functionality:
  - command line interface / menu user interface
  - read from a file named `[SORTTYPE]_[DATATYPE].txt`
  - read the format `somestring=somedata`
  - store the string-data pair into a link list
  - sort the link list with respect to the data field
  - search list for given key
  - write to a file named `[SORTTYPE]_[DATATYPE].txt`
- build:
  ```sh
  #!/bin/sh
  make
  ```
- run:
  - command line interface:
    For example, we read from `./input/dec_char*.txt` and sort to increasing order and write to `./inc_char*.txt`
    ```sh
    #!/bin/sh
    ./cmd input/rand_int.txt inc
    ```
  - menu user interface:
    follow the prompt and input `exit` to exit or commands.
    ```sh
    #!/bin/sh
    ./menu
    ```
