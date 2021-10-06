#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);

  char * out = malloc((len + 8) * sizeof(*out));
  size_t i = 0;
  for (; i < len; i++) {
    out[i] = inputName[i];
  }

  char * postfix = ".counts";
  for (int j = 0; j < 8; j++) {
    out[i] = postfix[j];
    i++;
  }

  return out;
}
