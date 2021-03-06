#include "function.h"

//find the largest elements that are smaller than 0 in [low, high)
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }
  if (low == high) {
    return low;
  }
  int left = low;
  int right = high;

  while (left < right) {
    int mid = (right - left + 1) / 2 + left;
    //if f(mid) <= 0, then mid can be the answer
    //but elements in the right of mid can be the results
    int temp = f->invoke(mid);
    if (temp == 0) {
      if (mid == high) {
        return high - 1;
      }
      return mid;
    }
    else if (temp < 0) {
      left = mid;
    }
    //if f(mid) > 0, then mid can not be the answer
    else {
      right = mid - 1;
    }
  }

  //printf("%d\n", left);
  //the resulting reuslt is either smaller or equal to 0, or bigger than 0
  //if it is smaller or equal to 0, then left is what want to find
  if (left == high) {
    return high - 1;
  }

  return left;
}
