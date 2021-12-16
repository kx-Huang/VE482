#include "lab5_dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dlistFreeNodes(dlist this);

typedef struct Node {
  char *key;
  struct Node *next;
  dlistValue value;
} node_t;

typedef struct List {
  node_t *head;
  dlistValueType type;
  int length;
} list_t;

dlist createDlist(dlistValueType type) {
  dlist list = (list_t *)malloc(sizeof(list_t));
  ((list_t *)list)->type = type;
  ((list_t *)list)->head = NULL;
  ((list_t *)list)->length = 0;
  if (type == DLIST_UNKOWN)
    return NULL;
  return list;
}

int dlistIsEmpty(dlist_const this) { return ((list_t *)this)->length == 0; }

void dlistAppend(dlist this, const char *key, dlistValue value) {
  // create new node
  node_t *node = (node_t *)malloc(sizeof(node_t));

  // insert key
  node->key = malloc(strlen(key) + 1);
  strcpy(node->key, key);

  // insert value
  if (((list_t *)this)->type == DLIST_INT)
    node->value.intValue = value.intValue;
  else if (((list_t *)this)->type == DLIST_DOUBLE)
    node->value.doubleValue = value.doubleValue;
  else if (((list_t *)this)->type == DLIST_STR) {
    node->value.strValue = malloc(strlen(value.strValue) + 1);
    strcpy(node->value.strValue, value.strValue);
  }
  node->next = NULL;

  // append new node to list
  if (((list_t *)this)->head == NULL) {
    ((list_t *)this)->head = node;
  } else {
    node_t *node_it = ((list_t *)this)->head;
    while (node_it->next != NULL)
      node_it = node_it->next;
    node_it->next = node;
  }
  ((list_t *)this)->length++;
}

static int rnd(const void *a, const void *b) {
  (void)a, (void)b;
  return (((rand()) % 2) * 2 - 1);
}

static int int_inc(const void *a, const void *b) {
  return (*(node_t **)a)->value.intValue - (*(node_t **)b)->value.intValue;
}

static int int_dec(const void *a, const void *b) {
  return (*(node_t **)b)->value.intValue - (*(node_t **)a)->value.intValue;
}

static int double_inc(const void *a, const void *b) {
  return (*(node_t **)a)->value.doubleValue > (*(node_t **)b)->value.doubleValue
             ? 1
             : -1;
}

static int double_dec(const void *a, const void *b) {
  return (*(node_t **)a)->value.doubleValue < (*(node_t **)b)->value.doubleValue
             ? 1
             : -1;
}

static int char_inc(const void *a, const void *b) {
  return strcmp((*(node_t **)a)->value.strValue,
                (*(node_t **)b)->value.strValue);
}

static int char_dec(const void *a, const void *b) {
  return strcmp((*(node_t **)b)->value.strValue,
                (*(node_t **)a)->value.strValue);
}

int (*const cmp[3][3])(const void *,
                       const void *) = {{rnd, int_inc, int_dec},
                                        {rnd, char_inc, char_dec},
                                        {rnd, double_inc, double_dec}};

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
  // no need to sort
  size_t length = (size_t)(((list_t *)this)->length);
  if (length == 0)
    return;

  // use an array to store node data
  node_t *node_it = ((list_t *)this)->head;
  node_t **vec_node = malloc(sizeof(node_t) * length);
  for (size_t i = 0; i < length; i++) {
    vec_node[i] = node_it;
    node_it = node_it->next;
  }

  // quick sort
  qsort(vec_node, length, sizeof(node_t *),
        cmp[((list_t *)this)->type - 1][method - 1]);

  // free destination list
  if (((list_t *)listDst)->length != 0)
    dlistFreeNodes(listDst);

  // initialize destination list
  ((list_t *)listDst)->length = (int)length;
  ((list_t *)listDst)->head = vec_node[0];

  // move node to destination list
  node_it = ((list_t *)listDst)->head;
  for (size_t i = 1; i < length; i++) {
    node_it->next = vec_node[i];
    node_it = node_it->next;
  }
  node_it->next = NULL;
  ((list_t *)this)->length = 0;

  // free node array
  free(vec_node);
}

void dlistPrint(dlist_const this) {
  if (((list_t *)this)->length == 0)
    return;
  node_t *node_it;
  for (node_it = ((list_t *)this)->head; node_it != NULL;
       node_it = node_it->next) {
    if (((list_t *)this)->type == DLIST_INT)
      fprintf(stderr, "%s=%d\n", node_it->key, node_it->value.intValue);
    else if (((list_t *)this)->type == DLIST_DOUBLE)
      fprintf(stderr, "%s=%lf\n", node_it->key, node_it->value.doubleValue);
    else if (((list_t *)this)->type == DLIST_STR)
      fprintf(stderr, "%s=%s\n", node_it->key, (node_it->value.strValue));
  }
}

void dlistFreeNodes(dlist this) {
  if (((list_t *)this)->length == 0)
    return;
  node_t *node_it = ((list_t *)this)->head;
  while (node_it != NULL) {
    node_t *node_tmp = node_it;
    free(node_tmp->key);
    if (((list_t *)this)->type == DLIST_STR)
      free(node_it->value.strValue);
    node_it = node_it->next;
    free(node_tmp);
  }
  ((list_t *)this)->length = 0;
}

void dlistFree(dlist this) {
  dlistFreeNodes(this);
  free(this);
}
