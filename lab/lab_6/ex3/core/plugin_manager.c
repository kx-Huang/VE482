#include "plugin_manager.h"

#include <stdlib.h>
#include <string.h>

manager_t *new_manager() {
  manager_t *m = malloc(sizeof(manager_t));
  m->hook_list = NULL;
  return m;
}

void free_manager(manager_t *m) {
  hook_list_t *hook_list_node = m->hook_list;
  while (hook_list_node) {
    hook_list_t *next = hook_list_node->next;
    free(hook_list_node->extension);
    free(hook_list_node);
    hook_list_node = next;
  }
  free(m);
}

void register_hook(manager_t *m, char *extension, hook_t hook) {
  hook_list_t *node = malloc(sizeof(hook_list_t));
  node->extension = malloc(sizeof(char *));
  strcpy(node->extension, extension);
  node->hook = hook;
  node->next = m->hook_list;
  m->hook_list = node;
}

int apply_hook(manager_t *m, char *filename, char *extension, int value_type,
               int sort_type) {
  hook_list_t *hook_list_node = m->hook_list;
  while (hook_list_node) {
    if (strcmp(extension, hook_list_node->extension) == 0)
      return hook_list_node->hook(filename, value_type, sort_type);
    hook_list_node = hook_list_node->next;
  }
  return 0;
}
