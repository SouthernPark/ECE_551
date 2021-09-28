#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f = NULL;
  if (argc == 1) {
    f = stdin;
    if (f == NULL) {
      fprintf(stderr, "Can not read from stdin");
      return EXIT_FAILURE;
    }
  }
  else {
    f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("can not open the file:");
      return EXIT_FAILURE;
    }
  }

  char ** lines = NULL;
  size_t i = 0;
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) != -1) {
    //store the line to lines
    char ** tmp = realloc(lines, (i + 1) * sizeof(*tmp));
    if (tmp == NULL) {
      fprintf(stderr, "run out of memo");
      return EXIT_FAILURE;
    }
    lines = tmp;
    lines[i] = strdup(line);
    i++;
  }
  free(line);
  //close the file
  fclose(f);

  //sort the data
  sortData(lines, i);
  //printz
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }

  free(lines);

  return EXIT_SUCCESS;
}
