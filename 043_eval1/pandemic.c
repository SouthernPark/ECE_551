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
    whether then ending \0 and \n are ajacent
    the length of name field should be smaller than 64
    
Input: the pointer to the line
EXIT_FAILURE if the line is invalid
*/
void check_line(char * line) {
  //check whether line is null
  if (line == NULL) {
    fprintf(stderr, "The input line is null");
    exit(EXIT_FAILURE);
  }
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
  //check whether there is a comma
  const char * first_comma = strchr(line, ',');
  if (first_comma == NULL) {
    fprintf(stderr, "The input line does not contain a comma \n");
    exit(EXIT_FAILURE);
  }
}
/*
 This function will check whether the length of the country's name is smaller than
64 or not.
The length of the name should be smaller than MAX_NAME_LEN, cause we still need some space to hold \0
Input: the start of the counrty field, the next end of the counrty field
Exit failure if the length is bigger or equal to 64
*/
void checkName(const char * start, const char * first_comma) {
  //check the length of the country name
  size_t name_len = (first_comma - start) / sizeof(char);
  if (name_len >= MAX_NAME_LEN) {
    fprintf(
        stderr, "The length of the country name is bigger than %d \n", MAX_NAME_LEN - 1);
    exit(EXIT_FAILURE);
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
EXIT_FAILURE if the population is out of bound or the population field is not valid     
*/
uint64_t readThePop(char * first_num) {
  //use strtoul to convert string to 64 bits value

  //set the error number to 0 before use strtoul, can help to check overflow
  errno = 0;
  //end ptr is the pointer the first invalid char
  char ** endptr = &first_num;
  uint64_t pop = strtoul(first_num, endptr, 10);
  //check whether the char before the first invalid char is 0~9
  if (*(*endptr - 1) < '0' || *(*endptr - 1) > '9') {
    fprintf(stderr, "There is no valid number in the population field");
    exit(EXIT_FAILURE);
  }
  //check overflow
  if (errno != 0) {
    perror("strtol:");
    exit(EXIT_FAILURE);
  }

  return pop;
}

country_t parseLine(char * line) {
  //WRITE ME

  /*check whether the line is valid*/
  check_line(line);

  /*check whether the population field is valid*/
  //get the first char
  char * first_comma = strchr(line, ',');

  /*check whether the name field is valid*/
  checkName(line, first_comma);

  /*fill the country struct*/
  country_t ans;
  ans.name[0] = '\0';
  //fill the name field
  fillTheName(line, &ans);
  //fill the population field
  ans.population = readThePop(first_comma + 1);
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
  double total_cases = 0;
  //calculate the sum of the first seven days
  for (int i = 0; i < seven_days; i++) {
    total_cases += data[i];
  }
  avg[0] = total_cases / seven_days;
  for (size_t i = 1; i < N; i++) {
    //remove the old first day case
    total_cases -= data[i - 1];
    //add the new last day case
    total_cases += data[i + seven_days - 1];
    avg[i] = total_cases / seven_days;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days == 0) {
    return;
  }

  double cum_sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    //the cum_sum of the [0..i] th day
    cum_sum += data[i];
    cum[i] = cum_sum / pop * base_hundred_thousand;
  }

  return;
}

/*
This function will find the maximum case in a counrty
Input: The data of a particular counrty
       The number of days the data measured
Output: the max case in this country theses days
*/
unsigned findMaxCaseInACounrty(const unsigned * data, size_t n_days) {
  unsigned max = 0;
  for (size_t i = 0; i < n_days; i++) {
    if (data[i] > max) {
      max = data[i];
    }
  }

  return max;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_days == 0 || n_countries == 0) {
    return;
  }
  //the counrty with the maximum cases
  long first_max = -1;
  size_t first_max_index = 0;
  //the counrty with the second maximum cases
  long second_max = -1;

  for (size_t i = 0; i < n_countries; i++) {
    unsigned tmp = findMaxCaseInACounrty(data[i], n_days);
    if (tmp > first_max) {
      first_max = tmp;
      first_max_index = i;
    }
    else {
      if (tmp > second_max) {
        second_max = tmp;
      }
    }
  }

  if (first_max == second_max) {
    printf("There is a tie between at least two countries\n");
    return;
  }

  unsigned max = (unsigned)first_max;

  printf("%s has the most daily cases with %u\n", countries[first_max_index].name, max);

  return;
}
