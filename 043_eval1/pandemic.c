#include "pandemic.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  //check whether the line is a string(check '\0' and '\n')
  char * first_null = strchr(line, '\0');
  if (first_null == NULL) {
    fprintf(stderr, "The input is not a string (not ending with \\0) \n");
    exit(EXIT_FAILURE);
  }
  //check whether the first '\n' is right before the '\0'
  char * first_nxt_line = strchr(line, '\n');
  if (first_nxt_line == NULL) {
    fprintf(stderr, "The input line is not a line (does not contain \\n) \n");
    exit(EXIT_FAILURE);
  }
  if (first_null != first_nxt_line + 1) {
    fprintf(stderr, "The input line format is not right \n");
    exit(EXIT_FAILURE);
  }
  //check whether there are two many commas in the string
  char * first_comma = strchr(line, ',');
  if (first_comma == NULL) {
    fprintf(stderr, "The input line does not contain a comma \n");
    exit(EXIT_FAILURE);
  }
  char * second_comma = strchr(first_comma + 1, ',');
  if (second_comma != NULL) {
    fprintf(stderr, "The input line has too many commas \n");
    exit(EXIT_FAILURE);
  }

  //fill the country struct
  country_t ans;
  ans.name[0] = '\0';
  //check how many chars before the comma
  char * first_char = line;
  //check the length of the country name
  int name_len = (first_comma - first_char) / sizeof(char);
  //the length of the name should be smaller than MAX_NAME_LEN, cause we still need some space to hold \0
  if (name_len >= MAX_NAME_LEN) {
    fprintf(
        stderr, "The length of the country name is bigger than %d \n", MAX_NAME_LEN - 1);
    exit(EXIT_FAILURE);
  }
  //else we can put it into struct
  int index = 0;  //record the position where we should put the char
  for (; index < MAX_NAME_LEN - 1; index++) {
    //when we encounter a comma, we stop
    if (first_char[index] == ',') {
      break;
    }
    ans.name[index] = first_char[index];
  }
  //set the last position with null terminator
  ans.name[index] = '\0';

  //check the population
  //the population is behind the comma but before '\n'
  //we need first to check they are 0~9
  char * first_num = first_comma + 1;
  while (*first_num != '\n') {
    if (*first_num < '0' || *first_num > '9') {
      fprintf(stderr, "There are characters other than 0~9 in population fild\n");
      exit(EXIT_FAILURE);
    }
    first_num++;
  }
  //reset the pointer of the first number
  first_num = first_comma + 1;
  //use strtoul to convert string to 64 bits value
  errno = 0;
  ans.population = strtoul(first_num, NULL, 10);
  if (errno != 0) {
    perror("strtol:");
    exit(EXIT_FAILURE);
  }

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
