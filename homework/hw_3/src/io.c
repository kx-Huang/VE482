#include "io.h"

char *name_sort_type[3] = {"rand", "inc", "dec"};
char *name_value_type[3] = {"char*", "int", "double"};

// get data type of node value
value_t get_value_type(char *arg) {
  // read filename
  char arg_buffer[MAX_ARG_LEN] = {0};
  strcpy(arg_buffer, arg);

  // tokenize filename
  char *token = NULL;
  token = strtok(arg_buffer, "_");
  token = strtok(NULL, "_.");

  // return value type
  if (strcmp(token, "char*") == 0)
    return CHAR;
  else if (strcmp(token, "int") == 0)
    return INT;
  else if (strcmp(token, "double") == 0)
    return DOUBLE;
  return ERROR_VALUE_TYPE;
}

// get sorting type
sort_t get_sort_type(char *arg) {
  // return sort type
  if (strcmp(arg, "rand") == 0)
    return RANDOM;
  else if (strcmp(arg, "inc") == 0)
    return INCREASE;
  else if (strcmp(arg, "dec") == 0)
    return DECREASE;
  return ERROR_SORT_TYPE;
}

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
