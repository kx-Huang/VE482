#ifndef UI_H
#define UI_H

#define MAX_ARG_LEN 1024
#define MAX_LINE_LEN 1024

#include "sort.h"

extern char *name_sort_type[3];
extern char *name_value_type[3];

void ui_menu();
int ui_cmd(int argc, char *argv[]);
value_t get_value_type(char *arg);
sort_t get_sort_type(char *arg);
void cascade_input_pair(list_t *list, char *path, value_t type);
void print_list(char *path, list_t *list, value_t type);

#endif
