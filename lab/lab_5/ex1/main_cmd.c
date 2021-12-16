#include "ui.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Error: wrong argument number!\n");
    return -1;
  }
  return ui_cmd(argc, argv);
}
