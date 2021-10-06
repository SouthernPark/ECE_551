#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

char * match(char * key, kvarray_t * kvPairs) {
  for (size_t i = 0; i < kvPairs->sz; i++) {
    if (strcmp(key, kvPairs->arr[i].key) == 0) {
      return kvPairs->arr[i].value;
    }
  }

  return NULL;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  //init counts_t
  counts_t * counts = malloc(sizeof(*counts));
  counts->arr = NULL;
  counts->sz = 0;
  counts->unknown = 0;
  //open file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Can not open file:");
    return NULL;
  }
  char * line = NULL;
  size_t sz = 0;
  //get and add each line to counts
  while (getline(&line, &sz, f) >= 0) {
    *(strchr(line, '\n')) = '\0';
    //whether current line matches a word in kv
    char * m = match(line, kvPairs);
    if (m != NULL) {
      addCount(counts, m);
    }
    else {
      addCount(counts, NULL);
    }
  }

  free(line);

  if (fclose(f) == EOF) {
    perror("Can not close file:");
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "the argument should be >= 3");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    //perror("Can not open file:");
    return EXIT_FAILURE;
  }
  //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * out_name = computeOutputFileName(argv[i]);
    FILE * f = fopen(out_name, "w");
    printCounts(c, f);
    free(out_name);
    //free count
    freeCounts(c);
  }
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
