#include "sort.h"

static int rnd(const void *a, const void *b) {
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
  node_t *node_curr = list->head;

  // traverse the List
  while (node_curr) {
    node_t *min = node_curr;
    node_t *node_next = node_curr->next;

    // traverse the unsorted sublist
    while (node_next) {
      if (cmp[type->value][type->sort](min, node_next) >= 0)
        min = node_next;
      node_next = node_next->next;
    }

    // swap data
    void *tmp = node_curr->value;
    node_curr->value = min->value;
    min->value = tmp;
    node_curr = node_curr->next;
  }
}
