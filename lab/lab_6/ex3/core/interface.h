#ifndef INTERFACE_H
#define INTERFACE_H

#include "plugin_utility.h"

#define MAX_ARG_LEN 1024
#define MAX_LINE_LEN 1024

typedef enum Sort {
  ERROR_SORT_TYPE = -1,
  RANDOM = 0,
  INCREASE = 1,
  DECREASE = 2,
} sort_t;

typedef enum Value {
  ERROR_VALUE_TYPE = -1,
  CHAR = 0,
  INT = 1,
  DOUBLE = 2,
} value_t;

typedef struct Type {
  value_t value;
  sort_t sort;
} type_t;

int run(int argc, char **argv);
value_t get_value_type(char *arg);
sort_t get_sort_type(char *arg);
char *get_file_ext(char *filename);

#endif // INTERFACE_H
