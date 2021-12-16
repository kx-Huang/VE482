#include "ui.h"

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

void print_list(char *path, list_t *list, value_t type) {
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

int ui_cmd(int argc, char *argv[]) {
  // wrong argument number
  if (argc != 3) {
    printf("Error: wrong argument number!\n");
    return -1;
  }

  // get value data type and sorting type
  type_t type;
  type.value = get_value_type(argv[1]);
  type.sort = get_sort_type(argv[2]);

  // read key-value pair from file to list
  printf("reading %s\n", argv[1]);
  list_t *list = list_init();
  cascade_input_pair(list, argv[1], type.value);

  // sort list according to argument
  printf("sorting elements\n");
  sort_list(list, &type);

  // write sorted list to file
  char path[MAX_ARG_LEN] = {0};
  sprintf(path, "%s_%s.txt", name_sort_type[type.sort],
          name_value_type[type.value]);
  printf("writing %s\n", path);
  print_list(path, list, type.value);

  // test list search function
  // void *res = list_search(list, "e");
  // if (res != NULL) {
  //   if (type.value == INT) {
  //     printf("Found: %d\n", *(int *)res);
  //   } else if (type.value == DOUBLE) {
  //     printf("Found: %f\n", *(double *)res);
  //   } else if (type.value == CHAR) {
  //     printf("Found: %s\n", (char *)res);
  //   }
  // }

  // free list
  list_free(list);
  return 0;
}

void free_argv(char *argv[2]) {
  for (size_t i = 0; i < 2; i++)
    free(argv[i]);
}

void ui_menu() {
  printf("========================================================\n");
  printf("Hello! Welcome to VE482 Lab 5 Ex1.\n");
  while (1) {
    printf("--------------------------------------------------------\n"
           "command format: [ [input filename] [sort type] | exit ]\n"
           "input filename: <sorttype>_<datatype>.txt\n"
           "sort type: rand, inc, dec\n"
           "data type: int, char(string), double\n"
           "exit: exit this program\n"
           "sample input: rand_int.txt inc\n"
           "sample input: exit\n"
           "--------------------------------------------------------\n"
           "# ");

    type_t type;
    char *argv[2];
    char input[MAX_LINE_LEN];
    for (size_t i = 0; i < 2; i++)
      argv[i] = (char *)malloc(sizeof(char) * MAX_ARG_LEN);

    // read input line
    if (fgets(input, MAX_ARG_LEN, stdin) == NULL) {
      printf("Error: get input failed!\n");
      free_argv(argv);
      break;
    }

    // parse first command
    char *token = strtok(input, " \n");
    if (token == NULL) {
      printf("Error: parse input failed!\n");
      free_argv(argv);
      break;
    }
    strcpy(argv[0], token);

    // check command "exit"
    if (strcmp(argv[0], "exit") == 0) {
      free_argv(argv);
      break;
    }

    // parse second command
    token = strtok(NULL, "\n");
    if (token == NULL) {
      printf("Error: parse input failed!\n");
      free_argv(argv);
      break;
    }
    strcpy(argv[1], token);

    // get value and sort type
    type.value = get_value_type(argv[0]);
    type.sort = get_sort_type(argv[1]);

    // read key-value pair from file to list
    printf("reading %s\n", argv[0]);
    list_t *list = list_init();
    cascade_input_pair(list, argv[0], type.value);

    // sort list according to argument
    printf("sorting elements\n");
    sort_list(list, &type);

    // write sorted list to file
    char path[MAX_ARG_LEN] = {0};
    sprintf(path, "%s_%s.txt", name_sort_type[type.sort],
            name_value_type[type.value]);
    printf("writing %s\n", path);
    print_list(path, list, type.value);

    // free list
    list_free(list);
  }
}
