#include "rand_story.h"

#include <string.h>

/*Fuctions used for story-step1*/

//this function will load the template from the file specified by the file name
//The input is file name and the address which will record the number of lines of tjefile
//output: loaded templates
char ** loadTemp(char * fileName, size_t * n) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    perror("Can not open file:");
    return NULL;
  }
  char ** lines = NULL;
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    char ** tmp = realloc(lines, ((*n) + 1) * sizeof(*lines));
    if (tmp == NULL) {
      free(line);
      free(lines);
      fprintf(stderr, "Can not realloc");
      return NULL;
    }
    lines = tmp;
    lines[*n] = strdup(line);
    (*n)++;
  }

  free(line);
  fclose(f);

  return lines;
}

//this function will free the heap memo occupied by the tempalte
void freeTemp(char ** temp, size_t N) {
  for (size_t i = 0; i < N; i++) {
    free(temp[i]);
  }

  free(temp);
}

//this function will check whether all the underscores are matchable
//we can do this by check whether the number of '_' in the line is even or not
int matchable(char * line) {
  int count = 0;
  const char * temp = line;
  while (*temp != '\0') {
    if (*temp == '_') {
      count++;
    }
    temp++;
  }
  if (count % 2 == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

//this function will print the substring line[i, j]
void printStr(char * line, size_t i, size_t j) {
  int len = j - i + 1;
  char * str = strndup(line + i, len);
  printf("%s", str);
  free(str);
}

//this function will find the first '_' after line[index]
//return the index of the first '_' after line[index]
//return len if there doest not exit one
long findUnderScore(char * line, size_t index, size_t len) {
  for (size_t i = index; i < len; i++) {
    if (line[i] == '_') {
      return i;
    }
  }

  return len;
}

void printCat(char * line, size_t i, size_t j) {
  char * cat = strndup(line + i, j - i + 1);
  const char * str = chooseWord(cat, NULL);
  printf("%s", str);
  free(cat);
}

//this function will return
void parseLine(char * line) {
  //1. check whether _ exist in this line
  char * first = strchr(line, '_');
  if (first == NULL) {
    //just print this line and return if does not exit '_'
    printf("%s", line);
    return;
  }
  //2. check whether there is a underscore that can not be matched
  if (matchable(first) == 0) {
    fprintf(stderr, "There is one '_' in the line that can not be matched\n");
    exit(EXIT_FAILURE);
  }

  //3. print the line
  size_t len = strlen(line);
  //left, right pointer for the substring
  size_t left = 0;
  size_t right = 0;
  while (left < len) {
    //find the first underscore
    right = findUnderScore(line, right, len);
    printStr(line, left, right - 1);

    left = right;
    //if there is one underscore, we need to print according to category
    if (left < len) {
      //find the matching underscore
      right = findUnderScore(line, right + 1, len);
      printCat(line, left, right);
      right++;
      left = right;
    }
  }
}
//this function will parse each line of the template
void parseTemp(char ** temp, size_t n) {
  for (size_t i = 0; i < n; i++) {
    parseLine(temp[i]);
  }
}
