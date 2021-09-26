#include "pandemic.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define seven_days 7
#define base_hundred_thousand 100000
/*
this function will check the format of the input line including:
    the ending \0
    the ending \n
    the length of name field should be smaller than 64
    whether the first char after the first comma is a number or not
Input: the pointer to the line
EXIT_FAILURE if the line is invalid
*/
void check_line(char * line) {
  //check whether the line is a string(check '\0' and '\n')
  const char * first_null = strchr(line, '\0');
  if (first_null == NULL) {
    fprintf(stderr, "The input is not a string (not ending with \\0) \n");
    exit(EXIT_FAILURE);
  }

  //check whether the first '\n' is right before the '\0'
  const char * first_nxt_line = strchr(line, '\n');
  if (first_nxt_line == NULL) {
    fprintf(stderr, "The input line is not a line (does not contain \\n) \n");
    exit(EXIT_FAILURE);
  }
  if (first_null != first_nxt_line + 1) {
    fprintf(stderr, "The input line format is not right \n");
    exit(EXIT_FAILURE);
  }
  //check whether there are two many commas in the string
  const char * first_comma = strchr(line, ',');
  if (first_comma == NULL) {
    fprintf(stderr, "The input line does not contain a comma \n");
    exit(EXIT_FAILURE);
  }
  //get the the first non-space char after the comma
  const char * first_num = first_comma + 1;
  while (*first_num == ' ') {
    first_num++;
  }

  //the nxt char can be +, -, 0123456789
  if ((*first_num != '-') && (*first_num != '+') &&
      (*first_num < '0' || *first_num > '9')) {
    fprintf(stderr, "The population field is invalid\n");
    exit(EXIT_FAILURE);
  }
  //const char * second_comma = strchr(first_comma + 1, ',');
  //if (second_comma != NULL) {
  //fprintf(stderr, "The input line has too many commas \n");
  //exit(EXIT_FAILURE);
  //}

  //check the length of the country name
  size_t name_len = (first_comma - line) / sizeof(char);
  //the length of the name should be smaller than MAX_NAME_LEN, cause we still need some space to hold \0
  if (name_len >= MAX_NAME_LEN) {
    fprintf(
        stderr, "The length of the country name is bigger than %d \n", MAX_NAME_LEN - 1);
    exit(EXIT_FAILURE);
  }
  //else we can put it into struct
}

/*
this function will check whether the population field is valid including:
   not contain char other than 0~9
   number can be hold in 64 bits unsigned integer
Input: the first pointer of the first number
EXIT_FAILURE if population field is invalid
*/
void checkPop(const char * first_num) {
  //check the population
  //the population is behind the comma but before '\n'
  //we need first to check they are 0~9
  while (*first_num != '\n') {
    if (*first_num < '0' || *first_num > '9') {
      fprintf(stderr, "There are characters other than 0~9 in population fild\n");
      exit(EXIT_FAILURE);
    }
    first_num++;
  }
}
/*
This function will fill the name field of the counrty struct
Input:the pointer of the first char or the line
      the pointer to the dest which is the conutry struct
*/
void fillTheName(const char * first_char, country_t * ans) {
  size_t index = 0;  //record the position where we should put the char
  for (; index < MAX_NAME_LEN - 1; index++) {
    //when we encounter a comma, we stop
    if (first_char[index] == ',') {
      break;
    }
    //else we put the char into name field
    ans->name[index] = first_char[index];
  }
  //set the last position with null terminator
  ans->name[index] = '\0';
}

/*                                                            
This function will fill the population field of the counrty struct  
Input:the pointer of the first number (the first pointer after the comma)               
      the pointer to the dest which is the conutry struct
EXIT_FAILURE if the population is out of bound     
*/
void fillThePop(const char * first_num, country_t * ans) {
  //use strtoul to convert string to 64 bits value
  errno = 0;
  ans->population = strtoul(first_num, NULL, 10);
  if (errno != 0) {
    perror("strtol:");
    exit(EXIT_FAILURE);
  }
}

country_t parseLine(char * line) {
  //WRITE ME

  /*check whether the line is valid*/
  check_line(line);

  /*check whether the population field is valid*/
  //get the first char
  const char * first_comma = strchr(line, ',');
  //checkPop(first_comma + 1);

  /*fill the country struct*/
  country_t ans;
  ans.name[0] = '\0';
  //fill the name field
  fillTheName(line, &ans);
  //fill the population field
  fillThePop(first_comma + 1, &ans);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < seven_days) {
    return;
  }

  // how senven-day running average, I am gonna to calculate
  size_t N = n_days - (seven_days - 1);
  //unsigned is 4 bytes, may be I should use uint_64 to do calculation
  uint64_t total_cases = 0;
  //calculate the sum of the first seven days
  for (int i = 0; i < seven_days; i++) {
    total_cases += data[i];
  }
  avg[0] = ((double)total_cases) / seven_days;
  for (size_t i = 1; i < N; i++) {
    //remove the old first day case
    total_cases -= data[i - 1];
    //add the new last day case
    total_cases += data[i + seven_days - 1];
    avg[i] = ((double)total_cases) / seven_days;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days == 0) {
    return;
  }

  uint64_t cum_sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    //the cum_sum of the [0..i] th day
    cum_sum += data[i];
    cum[i] = ((double)cum_sum) / pop * base_hundred_thousand;
  }

  return;
}

/*
the input of this functon is an array with size n_countries
this function will return the max 
*/
void maxForEachCountry() {
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
