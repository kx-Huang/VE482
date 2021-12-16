#include "interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run(int argc, char **argv) {
  // error argument number
  if (argc != 3) {
    fprintf(stderr, "[Error] wrong argument number.\n");
    return -1;
  }

  // get value type and sort type
  char *filename = argv[1];
  type_t type;
  type.value = get_value_type(filename);
  type.sort = get_sort_type(argv[2]);

  // discover and regist plugins
  manager_t *m = new_manager();
  void *fd_list = discover_plugins(m, "plugins");

  // apply hook
  char *extension = get_file_ext(filename);
  apply_hook(m, filename, extension, (int)type.value, (int)type.sort);

  // close plugins
  close_all_plugins(fd_list);

  // free manager
  free_manager(m);

  return 0;
}

// get data type of node value
value_t get_value_type(char *arg) {
  // read filename
  char arg_buffer[MAX_ARG_LEN] = {0};
  strcpy(arg_buffer, arg);

  // tokenize filename
  char *token = NULL;
  token = strtok(arg_buffer, "_");
  token = strtok(NULL, "_.");

  // return value type
  if (strcmp(token, "char*") == 0)
    return CHAR;
  else if (strcmp(token, "int") == 0)
    return INT;
  else if (strcmp(token, "double") == 0)
    return DOUBLE;
  return ERROR_VALUE_TYPE;
}

// get sorting type
sort_t get_sort_type(char *arg) {
  // return sort type
  if (strcmp(arg, "rand") == 0)
    return RANDOM;
  else if (strcmp(arg, "inc") == 0)
    return INCREASE;
  else if (strcmp(arg, "dec") == 0)
    return DECREASE;
  return ERROR_SORT_TYPE;
}

// get file extension
char *get_file_ext(char *filename) {
  char *dot = strrchr(filename, '.');
  if (dot == NULL) {
    fprintf(stderr, "[Error] no extension found in input file: %s", filename);
    exit(0);
  }
  return dot + 1;
}
