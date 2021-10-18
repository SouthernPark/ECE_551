#include "rand_story.h"

#include <string.h>

/*Fuctions used for story-step1*/

//this function will load the file specified by the file name
//The input is file name and the address which will record the number of lines of tjefile
//output: loaded file
char ** loadFile(char * fileName, size_t * n) {
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
void freeFile(char ** temp, size_t N) {
  for (size_t i = 0; i < N; i++) {
    free(temp[i]);
  }

  free(temp);
}

//this fucntion will count how many underscores, this line has
int underscoreCount(char * line) {
  int count = 0;
  const char * temp = line;
  while (*temp != '\0') {
    if (*temp == '_') {
      count++;
    }
    temp++;
  }
  return count;
}

//this function will check whether all the underscores are matchable
//we can do this by check whether the number of '_' in the line is even or not
int matchable(char * line) {
  int count = underscoreCount(line);
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

void printCat(char * line, size_t i, size_t j, catarray_t * catArr) {
  if (catArr != NULL && j == i + 1) {
    fprintf(stderr, "The __ underscore matchin is invalid\n");
    exit(EXIT_FAILURE);
  }
  char * cat = strndup(line + i + 1, j - i - 1);
  const char * str = chooseWord(cat, catArr);
  printf("%s", str);
  free(cat);
}

//this function will print the line replaced by word in catArr
void printLineStep1(char * line, catarray_t * catArr) {
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
      printCat(line, left, right, catArr);
      right++;
      left = right;
    }
  }
}

int isNum(char * line) {
  char ** end = &line;
  int num = strtol(line, end, 10);
  if (**end != '\0') {
    return -1;
  }
  return num;
}

int validNum(int num, int len) {
  if (num < 1 || num > len) {
    return 0;
  }
  return 1;
}

void addToWords(category_t * words, char * str) {
  words->words = realloc(words->words, (words->n_words + 1) * sizeof(*words->words));
  words->words[words->n_words] = str;
  words->n_words++;
}

//free the memo used for recordind the words that have been used
void freeWords(category_t * words) {
  free(words->words);
  free(words);
}

void printCatStep3(char * line,
                   size_t i,
                   size_t j,
                   catarray_t * catArr,
                   category_t * words) {
  if (catArr != NULL && j == i + 1) {
    fprintf(stderr, "The __ underscore matchin is invalid\n");
    exit(EXIT_FAILURE);
  }

  char * cat = strndup(line + i + 1, j - i - 1);
  int num = isNum(cat);
  if (num == -1 || validNum(num, words->n_words) == 0) {
    //then category is not a number
    const char * str = chooseWord(cat, catArr);
    printf("%s", str);
    addToWords(words, (char *)str);
  }
  else {
    printf("%s", words->words[words->n_words - num]);
    addToWords(words, words->words[words->n_words - num]);
  }

  free(cat);
}

//this function will print the line replaced by word in catArr
void printLineStep3(char * line, catarray_t * catArr, category_t * words) {
  //print the line
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
      printCatStep3(line, left, right, catArr, words);
      right++;
      left = right;
    }
  }
}

void checkLine(char * line) {
  //1. check whether _ exist in this line
  char * first = strchr(line, '_');
  if (first == NULL) {
    //just return if does not exit '_'
    return;
  }
  //2. check whether there is a underscore that can not be matched
  if (matchable(first) == 0) {
    fprintf(stderr, "There is one '_' in the line that can not be matched\n");
    exit(EXIT_FAILURE);
  }
}

/*Function for story-step2*/

//this function convert a line with cat:word format into key value pair
//format
_kv * lineTokv(char * line) {
  //check whether there is a : inside the line
  char * colon = strchr(line, ':');
  if (colon == NULL) {
    fprintf(stderr, "This line does not have a colon\n");
    return NULL;
  }
  _kv * res = malloc(sizeof(*res));
  res->cat = NULL;
  res->val = NULL;

  char * newLine = strchr(line, '\n');
  *newLine = '\0';
  res->val = strdup(colon + 1);
  *colon = '\0';
  res->cat = strdup(line);

  return res;
}

size_t findKey(catarray_t * array, size_t n, char * key) {
  for (size_t i = 0; i < n; i++) {
    if (strcmp(array->arr[i].name, key) == 0) {
      return i;
    }
  }

  return n;
}

//for each line in the file, this function will extract its category and word
//Then the category and word will be put into kvs_t
catarray_t * catToWords(char ** file, size_t n) {
  catarray_t * array = malloc(sizeof(*array));
  if (array == NULL) {
    fprintf(stderr, "Can not malloc \n");
    return NULL;
  }
  array->arr = NULL;
  array->n = 0;
  for (size_t i = 0; i < n; i++) {
    _kv * kv = lineTokv(file[i]);
    if (kv == NULL) {
      freeCatArray(array);
      return NULL;
    }
    size_t index = findKey(array, array->n, kv->cat);
    if (index == array->n) {
      array->arr = realloc(array->arr, (array->n + 1) * sizeof(*array->arr));
      array->arr[array->n].name = kv->cat;
      array->arr[array->n].words = malloc(sizeof(*array->arr[n].words));
      array->arr[array->n].words[0] = kv->val;
      array->arr[array->n].n_words = 1;
      array->n++;
    }
    else {
      array->arr[index].words =
          realloc(array->arr[index].words,
                  (array->arr[index].n_words + 1) * sizeof(*array->arr[index].words));

      array->arr[index].words[array->arr[index].n_words] = kv->val;
      array->arr[index].n_words++;
      free(kv->cat);
    }

    free(kv);
  }

  return array;
}

//free the words and name in one category
void freeCat(category_t cat) {
  for (size_t i = 0; i < cat.n_words; i++) {
    free(cat.words[i]);
  }
  free(cat.words);
  free(cat.name);
}

//free the categories and words
void freeCatArray(catarray_t * catArr) {
  for (size_t i = 0; i < catArr->n; i++) {
    freeCat(catArr->arr[i]);
  }

  free(catArr->arr);
  free(catArr);
}
