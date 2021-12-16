#ifndef EX3_PLUGIN_UTILITY_H
#define EX3_PLUGIN_UTILITY_H

#include "plugin_manager.h"

#define MAX_PATH_LEN 1024

typedef struct plugin_fd_node {
  void *fd;
  struct plugin_fd_node *next;
} fd_node_t;

typedef struct plugin_fd_list {
  fd_node_t *head;
} fd_list_t;

typedef int (*reg_fn_t)(manager_t *);

void *discover_plugins(manager_t *m, char *dir_name);
void close_all_plugins(void *fd_list);

#endif // EX3_PLUGIN_UTILITY_H
