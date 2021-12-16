#include <stdlib.h>

int main() {
  int *large_array;
  for (;; large_array++)
    large_array = malloc(1073741824 * sizeof(int));
  return 0;
}