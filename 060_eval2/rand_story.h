#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

/* story-step1*/
//any functions you want your main to use
char ** loadFile(char * fileName, size_t * n);
void freeFile(char ** temp, size_t N);

//void parseLine(char * line, catarray_t * cats);
void checkLine(char * line);
void printLineStep1(char * line, catarray_t * catArr);

//void parseTemp(char ** temp, size_t n, catarray_t * cats);

/* story-step2*/

struct _kv_t {
  char * cat;
  char * val;
};

typedef struct _kv_t _kv;

_kv * lineTokv(char * line);

catarray_t * catToWords(char ** file, size_t n);

void freeCat(category_t cat);
void freeCatArray(catarray_t * catArr);

/* story-step3 */
void printLineStep3(char * line, catarray_t * catArr, category_t * words, int remove);
void freeWords(category_t * words);

#endif
