#include "../core/list.h"
#include "../core/plugin_manager.h"

#include "io.h"
#include "sort.h"

#include <stdio.h>

int read_csv(char *filename, int type_value, int type_sort) {

  // suppress warning, to be deleted
  (void)type_value, (void)type_sort;

  fprintf(stderr, "[Running] plugin \"csv\" is reading from \"%s\"...\n",
          filename);
  // TODO: read csv file and store data

  fprintf(stderr, "[Running] plugin \"csv\" is sorting elements...\n");
  // TODO: sort key-value pair

  fprintf(stderr, "[Running] writing to \"out/%s.csv\"\n", filename);
  // TODO: print sorted data

  return 0;
}

int init_txt(manager_t *m) {
  register_hook(m, "csv", read_csv);
  return 1;
}
