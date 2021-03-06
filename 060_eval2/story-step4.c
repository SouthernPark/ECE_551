#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //0.check argu
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "Incorrect argument number\n");
    return EXIT_FAILURE;
  }
  //this variable will record whether -n is given or not
  int notReuse = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "The second argument should be -n. \n");
      exit(EXIT_FAILURE);
    }
    else {
      //we are not allowed to reuse
      notReuse = 1;
    }
  }

  //1. load the category-words
  size_t n_words = 0;
  char ** words = NULL;
  if (argc == 3) {
    words = loadFile(argv[1], &n_words);
  }
  else {
    words = loadFile(argv[2], &n_words);
  }

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
  char ** templates = NULL;
  if (argc == 3) {
    templates = loadFile(argv[2], &n_line);
  }
  else {
    templates = loadFile(argv[3], &n_line);
  }
  if (templates == NULL) {
    exit(EXIT_FAILURE);
  }
  //4. parse the templates using the given words and category
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->name = NULL;
  usedWords->words = NULL;
  usedWords->n_words = 0;
  for (size_t i = 0; i < n_line; i++) {
    //check the line is valid for the underscore
    checkLine(templates[i]);
    printLineStep3(templates[i], catArray, usedWords, notReuse);
  }
  //5. free words
  freeCatArray(catArray);
  freeFile(words, n_words);

  //6.free templates
  freeFile(templates, n_line);

  //7. free words
  freeWords(usedWords);
}
