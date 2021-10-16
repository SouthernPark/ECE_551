#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
//any functions you want your main to use
char ** loadTemp(char * fileName, size_t * n);
void freeTemp(char ** temp, size_t N);

void parseLine(char * line);

void parseTemp(char ** temp, size_t n);

//_matches * parseTemp(char * temp);

#endif
