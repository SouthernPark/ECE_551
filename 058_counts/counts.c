#include "counts.h"

//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->arr = NULL;
  counts->sz = 0;
  counts->unknown = 0;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    int find = -1;
    for (size_t i = 0; i < c->sz; i++) {
      if (strcmp(c->arr[i].count, name) == 0) {
        find = 1;
        c->arr[i].value++;
        break;
      }
    }

    if (find == -1) {
      c->arr = realloc(c->arr, (++c->sz) * sizeof(*c->arr));
      c->arr[c->sz - 1].count = strdup(name);
      c->arr[c->sz - 1].value = 1;
    }

    return;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    fprintf(outFile, "%s: %lu\n", c->arr[i].count, c->arr[i].value);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->unknown);
  }
  int status = fclose(outFile);
  if (status == EOF) {
    perror("can not close file:");
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    free(c->arr[i].count);
  }
  free(c->arr);
  free(c);
}
