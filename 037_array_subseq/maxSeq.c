#include <stdio.h>
#include <stdlib.h>

size_t maxOne(size_t x, size_t y) {
  if (x > y) {
    return x;
  }
  else {
    return y;
  }
}

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }

  size_t max = 0;
  //I am gonna to use two pointers
  //inside the two pointer is the increasing order
  size_t left = 0;
  size_t right = 1;

  while (right <= n) {
    while (right < n && right - 1 >= 0 && array[right] > array[right - 1]) {
      right++;
    }

    max = maxOne(right - left, max);  //right - left, max , the bigger one

    //then move the left to the right
    left = right;
    right++;
  }

  return max;
}
