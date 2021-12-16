#include "io.h"
#include "../core/list.h"

#include <stdlib.h>
#include <string.h>

// read key-value pair from file
void cascade_input_pair(list_t *list, char *path, value_t type) {
  // setup buffers
  char *buffer = malloc(sizeof(char) * MAX_LINE_LEN);
  memset(buffer, 0, MAX_LINE_LEN);
  char *value_buffer = NULL;
  char *key_buffer = NULL;

  // read key-value pair from file
  FILE *fin = fopen(path, "r");
  while (fgets(buffer, MAX_LINE_LEN, fin) != NULL) {
    // initialize key-value pair
    char *key = NULL;
    void *value = NULL;

    // tokenize key and raw value
    key_buffer = strtok(buffer, "=");
    value_buffer = strtok(NULL, "\n");

    // get inserted key
    size_t key_length = strlen(key_buffer) + 1;
    key = malloc(sizeof(char) * key_length);
    memset(key, 0, key_length);
    strcpy(key, key_buffer);

    // get inserted value with corresponding type
    if (type == CHAR) {
      size_t value_length = strlen(value_buffer) + 1;
      value = malloc(sizeof(char) * value_length);
      memset(value, 0, value_length);
      strcpy(value, value_buffer);
    } else if (type == INT) {
      value = malloc(sizeof(int));
      *(int *)value = atoi(value_buffer);
    } else if (type == DOUBLE) {
      value = malloc(sizeof(double));
      *(double *)value = atof(value_buffer);
    }
    // insert key-value into list
    list_insert(list, key, value);

    // reset buffer for new line
    memset(buffer, 0, MAX_LINE_LEN);
  }
  fclose(fin);
  free(buffer);
}

void print_list(char *path, list_t *list, value_t type) {
  (void)path;
  node_t *node_it = list->head;
  for (size_t i = 0; node_it != NULL; i++) {
    if (type == CHAR) {
      fprintf(stdout, "%s=%s\n", node_it->key, (char *)node_it->value);
    } else if (type == INT)
      fprintf(stdout, "%s=%d\n", node_it->key, *((int *)(node_it->value)));
    else if (type == DOUBLE)
      fprintf(stdout, "%s=%f\n", node_it->key, *((double *)(node_it->value)));
    node_it = node_it->next;
  }
}
