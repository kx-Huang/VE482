#include "lab5_dlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dlistSortMethod getSortMethod(char *order) {
  if (strcmp(order, "rand") == 0)
    return Dsort_list_RAND;
  if (strcmp(order, "inc") == 0)
    return Dsort_list_INC;
  if (strcmp(order, "dec") == 0)
    return Dsort_list_DEC;
  return Dsort_list_UNKOWN;
}

static dlistValueType getValueType(char *fileName) {
  const char s[3] = "_.";
  strtok(fileName, s);
  char *dataTypeStr = strtok(NULL, s);
  if (strcmp(dataTypeStr, "char*") == 0)
    return DLIST_STR;
  if (strcmp(dataTypeStr, "int") == 0)
    return DLIST_INT;
  if (strcmp(dataTypeStr, "double") == 0)
    return DLIST_DOUBLE;
  return DLIST_UNKOWN;
}

int run(char *fileName, char *order) {
  FILE *fp = fopen(fileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);
  dlistValueType type = getValueType(fileName);
  dlistSortMethod method = getSortMethod(order);
  if (type == DLIST_UNKOWN || method == Dsort_list_UNKOWN)
    exit(EXIT_FAILURE);
  dlist listDst = createDlist(type), list = createDlist(type);
  char line[1024], key[256];
  while (fgets(line, sizeof(line), fp)) {
    dlistValue value;
    if (type == DLIST_STR) {
      value.strValue = malloc(1024);
      sscanf(line, "%[^=]=%s", key, value.strValue);
    }
    if (type == DLIST_INT) {
      sscanf(line, "%[^=]=%d", key, &value.intValue);
    }
    if (type == DLIST_DOUBLE) {
      sscanf(line, "%[^=]=%lf", key, &value.doubleValue);
    }
    dlistAppend(list, key, value);
    if (type == DLIST_STR)
      free(value.strValue);
  }
  fclose(fp);
  dlistSort(list, listDst, method);
  dlistSort(list, listDst, method);
  dlistPrint(listDst);
  dlistFree(list);
  dlistFree(listDst);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3)
    return -1;
  run(argv[1], argv[2]);
  return 0;
}
