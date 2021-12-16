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

static int rnd(const void *a, const void *b) {
  (void)a, (void)b;
  return (((rand()) % 2) * 2 - 1);
}

static int int_inc(const void *a, const void *b) {
  return *((int *)(((node_t *)a)->value)) - *((int *)(((node_t *)b)->value));
}

static int int_dec(const void *a, const void *b) {
  return *(int *)(((node_t *)b)->value) - *(int *)(((node_t *)a)->value);
}

static int double_inc(const void *a, const void *b) {
  return *(double *)(((node_t *)a)->value) > *(double *)(((node_t *)b)->value)
             ? 1
             : -1;
}

static int double_dec(const void *a, const void *b) {
  return *(double *)(((node_t *)a)->value) < *(double *)(((node_t *)b)->value)
             ? 1
             : -1;
}

static int char_inc(const void *a, const void *b) {
  return strcmp((char *)(((node_t *)a)->value), (char *)(((node_t *)b)->value));
}

static int char_dec(const void *a, const void *b) {
  return strcmp((char *)(((node_t *)b)->value), (char *)(((node_t *)a)->value));
}

int (*const cmp[3][3])(const void *,
                       const void *) = {{rnd, char_inc, char_dec},
                                        {rnd, int_inc, int_dec},
                                        {rnd, double_inc, double_dec}};

void list_sort(list_t *list, type_t *type) {
  // no need to sort
  size_t length = list->length;
  if (length < 2)
    return;

  // use an array to store node data
  node_t *node_it = list->head;
  node_t *vec_node = malloc(sizeof(node_t) * length);
  for (size_t i = 0; i < length; i++) {
    memcpy(vec_node + i, node_it, sizeof(node_t));
    node_it = node_it->next;
  }

  // quick sort
  qsort(vec_node, length, sizeof(node_t), cmp[type->value][type->sort]);

  // switch key-value data according to sorted array
  node_it = list->head;
  for (size_t i = 0; i < length; i++) {
    node_it->key = vec_node[i].key;
    node_it->value = vec_node[i].value;
    node_it = node_it->next;
  }

  // free node array
  free(vec_node);
}

// print list
void list_print(char *path, list_t *list, value_t type) {
  FILE *fout = fopen(path, "w");
  node_t *node_it = list->head;
  for (size_t i = 0; node_it != NULL; i++) {
    if (type == CHAR) {
      fprintf(fout, "%s=%s\n", node_it->key, (char *)node_it->value);
    } else if (type == INT)
      fprintf(fout, "%s=%d\n", node_it->key, *((int *)(node_it->value)));
    else if (type == DOUBLE)
      fprintf(fout, "%s=%f\n", node_it->key, *((double *)(node_it->value)));
    node_it = node_it->next;
  }
  fclose(fout);
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
