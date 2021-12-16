#include "list.h"

// return empty list
list_t *list_init(void) {
  list_t *list = malloc(sizeof(list_t));
  list->head = NULL;
  list->length = 0;
  return list;
}

// return empty node
node_t *node_init(char *key, void *value) {
  node_t *node = malloc(sizeof(node_t));
  node->key = key;
  node->value = value;
  node->next = NULL;
  return node;
}

// free node
void node_free(node_t *node) {
  free(node->key);
  free(node->value);
}

// free list
void list_free(list_t *list) {
  node_t *node_it = list->head;
  while (node_it != NULL) {
    node_t *node_tmp = node_it;
    node_free(node_it);
    node_it = node_it->next;
    free(node_tmp);
  }
  free(list);
}

// insert key-value node into list
void list_insert(list_t *list, char *key, void *value) {
  list_append(list, node_init(key, value));
}

// append node at the end of list
void list_append(list_t *list, node_t *node) {
  if (list->head == NULL) {
    list->head = node;
  } else {
    node_t *node_it = list->head;
    while (node_it->next != NULL)
      node_it = node_it->next;
    node_it->next = node;
  }
  list->length++;
}

// search list by key
void *list_search(list_t *list, char *key) {
  if (list->length == 0)
    return NULL;
  node_t *node_it = list->head;
  while (node_it != NULL) {
    if (strcmp(key, node_it->key) == 0)
      return node_it->value;
    node_it = node_it->next;
  }
  return NULL;
}
