#ifndef EX3_PLUGIN_MANAGER_H
#define EX3_PLUGIN_MANAGER_H

typedef int (*hook_t)(char *, int, int);

typedef struct hook_list {
  char *extension;
  hook_t hook;
  struct hook_list *next;
} hook_list_t;

typedef struct plugin_manager {
  hook_list_t *hook_list;
} manager_t;

manager_t *new_manager();
void free_manager(manager_t *m);
void register_hook(manager_t *m, char *extension, hook_t hook);
int apply_hook(manager_t *m, char *filename, char *extension, int value_type,
               int sort_type);

#endif // EX3_PLUGIN_MANAGER_H
