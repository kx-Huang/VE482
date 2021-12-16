#include "../core/list.h"
#include "../core/plugin_manager.h"

#include "io.h"
#include "sort.h"

#include <stdio.h>

int read_txt(char *filename, int type_value, int type_sort) {
  // initialize list
  list_t *list = list_init();

  // insert input pair to list
  fprintf(stderr, "[Running] plugin \"txt\" is reading from \"%s\"...\n",
          filename);
  cascade_input_pair(list, filename, type_value);

  // sort key-value pair
  fprintf(stderr, "[Running] plugin \"txt\" is sorting elements...\n");
  type_t type;
  type.value = type_value;
  type.sort = type_sort;
  sort_list(list, &type);

  // print list
  char path[MAX_ARG_LEN] = {0};
  sprintf(path, "out/%s_%s.txt", name_sort_type[type.sort],
          name_value_type[type.value]);
  fprintf(stderr, "[Running] writing to \"%s\"\n", path);
  print_list(path, list, type.value);

  // free list
  list_free(list);
  return 0;
}

int init_txt(manager_t *m) {
  register_hook(m, "txt", read_txt);
  return 1;
}
