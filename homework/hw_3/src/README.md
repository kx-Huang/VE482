# README

- path: ./src
- author: Kexuan Huang
- date: 2021.10.20
- description: source code for Ex.2
- functionality:
  - read from a file named `[SORTTYPE]_[DATATYPE].txt`
  - read the format `somestring=somedata`
  - store the string-data pair into a link list
  - sort the link list with respect to the data field
  - search list for given key
  - write to a file named `[SORTTYPE]_[DATATYPE].txt`
- build:
  ```sh
  #!/bin/sh
  cd src
  make
  ```
- run:
  For example, we read from `./input/dec_char*.txt` and sort to increasing order and write to `./inc_char*.txt`
  ```sh
  #!/bin/sh
  ./ex2 input/dec_char*.txt inc
  ```
