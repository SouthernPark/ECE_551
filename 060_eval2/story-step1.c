#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  //0.check argu
  if (argc != 2) {
    fprintf(stderr, "Incorrect argument number\n");
    return EXIT_FAILURE;
  }
  //1.load the story template

  size_t n = 0;
  char ** templates = loadTemp(argv[1], &n);

  //2.parse and replace the templates
  parseTemp(templates, n);
  //3.free templates
  freeTemp(templates, n);
}
