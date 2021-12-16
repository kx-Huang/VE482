#include "sort.h"

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

void sort_list(list_t *list, type_t *type) {
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
