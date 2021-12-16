# README

- name: zathura-txt
- author: Kexuan Huang
- date: 2021.11.4
- description: plugin for zathura supporting open txt files
- build zathura-txt:
  ```sh
  #!/bin/bash
  meson build
  cd build
  ninja
  ninja install
  ```
- open txt file:
  ```sh
  #!/bin/bash
  zathura [FILENAME].txt
  ```
