#ifndef IO_H
#define IO_H

#define MAX_ARG_LEN 2048
#define MAX_LINE_LEN 2048

#include "sort.h"

void cascade_input_pair(list_t *list, char *path, value_t type);
void print_list(char *path, list_t *list, value_t type);

#endif // IO_H
