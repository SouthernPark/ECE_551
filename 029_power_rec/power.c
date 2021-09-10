#include <stdio.h>
#include <stdlib.h>

unsigned helper(unsigned x, unsigned y, unsigned ans) {
  if (y <= 0) {
    return ans;
  }
  if (x == 0) {
    return 0;
  }
  return helper(x, y - 1, x * ans);
}

//assume this functione will calculate x to the power of y
unsigned power(unsigned x, unsigned y) {
  return helper(x, y, 1);
}
