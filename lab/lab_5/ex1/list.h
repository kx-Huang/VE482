#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *key;
  void *value;
  struct Node *next;
} node_t;

typedef struct List {
  node_t *head;
  size_t length;
} list_t;

// list construct and destruct
list_t *list_init(void);
node_t *node_init(char *key, void *value);
void node_free(node_t *node);
void list_free(list_t *list);

// dynamic methods
void list_insert(list_t *list, char *key, void *val);
void list_append(list_t *list, node_t *node);

// static methods
void *list_search(list_t *list, char *key);

#endif
