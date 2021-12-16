# README

- path: ex3
- author: Kexuan Huang
- date: 2021.10.24
- description: source code for Ex.3
- files: a Bash script which generates a file composed of one integer per line. The script should read the last number in the file, add one to it, and append the result to the file.
  - race_add.sh: script which may lead to race condition
  - race_free_add.sh: script which prevent the race condition
- Run the script in both background and foreground at the same time:
  ```bash
  #!/bin/bash
  bash race_add.sh & bash race_add.sh
  ```
