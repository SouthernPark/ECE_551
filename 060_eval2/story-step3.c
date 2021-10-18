#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //0.check argu
  if (argc != 3) {
    fprintf(stderr, "Incorrect argument number\n");
    return EXIT_FAILURE;
  }

  //1. load the category-words
  size_t n_words = 0;
  char ** words = loadFile(argv[1], &n_words);

  if (words == NULL) {
    //file can not be loaded
    exit(EXIT_FAILURE);
  }

  //2. convert the each line to categori words and store them in an array
  catarray_t * catArray = catToWords(words, n_words);
  if (catArray == NULL) {
    freeFile(words, n_words);
    exit(EXIT_FAILURE);
  }

  //3. load the story template
  size_t n_line = 0;
  char ** templates = loadFile(argv[2], &n_line);
  if (templates == NULL) {
    exit(EXIT_FAILURE);
  }
  //4. parse the templates using the given words and category
  //parseTemp(templates, n_line, catArray);
  for (size_t i = 0; i < n_line; i++) {
    //check the line is valid for the underscore
    checkLine(templates[i]);
    printLineStep1(templates[i], NULL);
  }

  //5. free words
  freeCatArray(catArray);
  freeFile(words, n_words);

  //6.free templates
  freeFile(templates, n_line);
}
