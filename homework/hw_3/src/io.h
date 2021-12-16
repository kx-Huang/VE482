#ifndef IO_H
#define IO_H

#define MAX_ARG_LEN 1024
#define MAX_LINE_LEN 2048

#include "list.h"

extern char *name_sort_type[3];
extern char *name_value_type[3];

value_t get_value_type(char *arg);
sort_t get_sort_type(char *arg);
void cascade_input_pair(list_t *list, char *path, value_t type);

#endif
