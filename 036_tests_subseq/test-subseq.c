#include <stdio.h>
#include <stdlib.h>

//decalre the func we want to test
size_t maxSeq(int * array, size_t n);

void test(int * array, size_t n, size_t expected);

int main(void) {
  int arr0[1] = {0};
  //array with 0 length
  test(arr0, 0, 0);
  //array with 1 length
  int arr1[] = {0};
  test(arr1, 1, 1);
  int arr2[] = {1};
  test(arr2, 1, 1);
  int arr3[] = {2147483647};
  test(arr3, 1, 1);
  int arr4[] = {-2147483648};
  test(arr4, 1, 1);

  //array with 2 length
  int arr5[] = {1, 2};
  test(arr5, 2, 2);

  int arr6[] = {2, 1};
  test(arr6, 2, 1);

  //test not always increasing sequnce
  int arr7[] = {1, 2, 3, 1, 2, 3, 4};
  test(arr7, 7, 4);

  int arr8[] = {3, 2, 1};
  test(arr8, 3, 1);

  //test strictly equal
  int arr9[] = {1, 1};
  test(arr9, 2, 1);

  int arr10[] = {1, 2, 3, 3, 3, 4, 5, 6, 7, 7};
  test(arr10, 10, 5);

  //test all negative number
  int arr11[] = {-2147483648, -1000, -500, 0, 2147483647, 1, 2, 3};
  test(arr11, 8, 5);

  return EXIT_SUCCESS;
}

void test(int * array, size_t n, size_t expected) {
  if (maxSeq(array, n) != expected) {
    exit(EXIT_FAILURE);
  }
}
