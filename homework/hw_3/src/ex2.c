#include "ex2.h"

int main(int argc, char *argv[]) {
  // missing argument
  if (argc < 3)
    return 0;

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
  list_sort(list, &type);

  // write sorted list to file
  char path[MAX_ARG_LEN] = {0};
  sprintf(path, "%s_%s.txt", name_sort_type[type.sort],
          name_value_type[type.value]);
  printf("writing %s\n", path);
  list_print(path, list, type.value);

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
