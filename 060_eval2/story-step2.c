#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //0.check argu
  if (argc != 2) {
    fprintf(stderr, "Incorrect argument number\n");
    return EXIT_FAILURE;
  }

  //1. load the file
  size_t n = 0;
  char ** file = loadFile(argv[1], &n);

  if (file == NULL) {
    //file can not be loaded
    exit(EXIT_FAILURE);
  }

  //2. convert the each line to categori words and store them in an array
  catarray_t * catArray = catToWords(file, n);
  if (catArray == NULL) {
    freeFile(file, n);
    exit(EXIT_FAILURE);
  }
  printWords(catArray);

  //3. free
  freeCatArray(catArray);
  freeFile(file, n);
}
