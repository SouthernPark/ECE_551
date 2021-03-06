#include <assert.h>
#include <math.h>

#include "function.h"

//binary search
int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  //I computed the maximum number of invocations of f
  int remains = 1;
  if (high > low) {
    remains = ((int)log2(high - low)) + 1;
  }
  //wrap f in a CountedIntFn,
  CountedIntFn count(remains, f, mesg);
  //perform the binary search
  int res = binarySearchForZero(&count, low, high);
  //check the answer
  assert(res == expected_ans);
}

int main(void) {
  Function<int, int> * sin = new SinFunction();
  check(sin, 0, 150000, 52359, "testing for sin function");
  check(sin, 52359, 150000, 52359, "testing for sin function");
  delete sin;

  Function<int, int> * negSqure = new NegSquareFunction();  // -(x+1)^2
  //check(negSqure, -1000, 0, -1, "testing for -(x+1)^2 function");
  check(negSqure, -2, -1, -2, "testing for -(x+1)^2 function");
  //all negative
  check(negSqure, -1000, -500, -501, "testing for -(x+1)^2 function");

  delete negSqure;
  Function<int, int> * linear = new LinearFunction();  //y = x - 2.5
  //check(linear, 0, 0, 0, "testing for x - 2.5");
  check(linear, 0, 1024, 2, "testing for x - 2.5");
  check(linear, 0, 3, 2, "testing for x - 2.5");
  check(linear, 1, 3, 2, "testing for x - 2.5");
  check(linear, 2, 3, 2, "testing for x - 2.5");
  check(linear, 1, 2, 1, "testing for x - 2.5");
  //all positive
  check(linear, 10, 1024, 10, "testing for x - 2.5");

  delete linear;

  Function<int, int> * segFunc = new SegFunction();
  check(segFunc, -1, 1, -1, "testing for seg func");
  check(segFunc, 0, 1, 0, "testing for seg func");
  delete segFunc;

  Function<int, int> * constFunc = new ConstFunction();
  check(constFunc, -1000, 1000, 999, "check for constant");
  delete constFunc;
}
