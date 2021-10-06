#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 11
int main(void) {
  char * testData[NUM_TESTS] = {"apple",
                                "banana",
                                "apple",
                                "frog",
                                "sword",
                                "bear",
                                "frog",
                                "apple",
                                "zebra",
                                "knight",
                                "Lt.Commander"};
  counts_t * testCounts = createCounts();
  for (int i = 0; i < NUM_TESTS; i++) {
    addCount(testCounts, testData[i]);
  }
  printCounts(testCounts, stdout);
  freeCounts(testCounts);
  return EXIT_SUCCESS;
}
