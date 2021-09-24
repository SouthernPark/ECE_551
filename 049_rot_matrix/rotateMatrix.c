#include <stdio.h>
#include <stdlib.h>
#define row_size 12
#define mat_sz 10
//load one line to the dest
char * loadOneLine(FILE * f, char * dest) {
  char * res = fgets(dest, row_size, f);
  if (res = NULL) {
    fprintf(stderr, "The number of rows is less than 10");
    return NULL;
  }
  if (dest[row_size - 1] != '\0' || dest[row_size - 2] != '\n') {
    fprintf(stderr, "the lenth of one row is not 10\n");
    return NULL;
  }

  return dest;
}

int main(int argc, char ** argv) {
  //firstly check the number of argc
  if (argc != 2) {
    fprintf(stderr, "Wrong arguments\n");
    return EXIT_FAILURE;
  }
  //file checking
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("File open problem:\n");
    return EXIT_FAILURE;
  }
  //create a char array to sotre
  //load the data into the arr
  char input[12][12];
  for (int i = 0; i < mat_sz; i++) {
    char * res = loadOneLine(f, input[i]);
    if (res == NULL) {
      return EXIT_FAILURE;
    }
  }

  //check whetehr there is still some data
  char left[12];
  char * left_res = fgets(left, row_size, f);
  if (left_res != NULL) {
    fprintf(stderr, "there are two many lines\n");
    return EXIT_FAILURE;
  }

  //rotate the matrix
  //make a copy
  char copy[mat_sz][mat_sz];
  for (int i = 0; i < mat_sz; i++) {
    for (int j = 0; j < mat_sz; j++) {
      copy[i][j] = input[i][j];
    }
  }

  //rotate
  for (int i = 0; i < mat_sz; i++) {
    for (int j = 0; j < mat_sz; j++) {
      input[j][-i + 9] = copy[i][j];
    }
  }

  for (int i = 0; i < mat_sz; i++) {
    printf("%s", input[i]);
  }

  return EXIT_SUCCESS;
}
