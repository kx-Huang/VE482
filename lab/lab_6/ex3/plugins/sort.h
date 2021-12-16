#ifndef SORT_H
#define SORT_H

#include "../core/list.h"
#include <stdlib.h>
#include <string.h>

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

static char *name_sort_type[3] = {"rand", "inc", "dec"};
static char *name_value_type[3] = {"char*", "int", "double"};

void sort_list(list_t *list, type_t *type);

#endif // SORT_H
