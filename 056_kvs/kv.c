#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this function will split according to the first '='
kvpair_t split(char * line) {
  kvpair_t kv;
  char * first_equal = strchr(line, '=');
  char * first_new_line = strchr(line, '\n');
  *first_equal = '\0';
  kv.key = strdup(line);
  *first_new_line = '\0';
  kv.value = strdup(first_equal + 1);
  return kv;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  kvarray_t * pairs = malloc(sizeof(*pairs));
  pairs->arr = NULL;
  pairs->sz = 0;
  char * line = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    pairs->arr = realloc(pairs->arr, (i + 1) * (sizeof(*pairs->arr)));
    pairs->arr[i] = split(line);
    pairs->sz = i + 1;
    i++;
  }

  free(line);
  fclose(f);
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->sz; i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].value);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->sz; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

  for (size_t i = 0; i < pairs->sz; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }

  return NULL;
}
