#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define alpha_sz 26
int frequen(FILE * stream) {
  //read char from the file one by one
  int arr[alpha_sz] = {0};
  int c;
  while ((c = fgetc(stream)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      arr[c - 'a']++;
    }
  }

  int max = 0;
  int maxIndex = -1;
  //find the most frequency character
  for (int i = 0; i < alpha_sz; i++) {
    if (arr[i] > max) {
      max = arr[i];
      maxIndex = i;
    }
  }

  return maxIndex;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "argu: need the input file name");
    return EXIT_FAILURE;
  }

  FILE * stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror("Failed to open the file");
    return EXIT_FAILURE;
  }

  //get the most frequency char in this file
  int c = frequen(stream);
  if (c == -1) {
    fprintf(stderr, "You file does not contain any alpha");
  }

  int key = (c + 26 - 4) % 26;
  fprintf(stdout, "%d\n", key);

  return EXIT_SUCCESS;
}
