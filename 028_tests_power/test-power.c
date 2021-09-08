#include <stdio.h>
#include <stdlib.h>

//decalre the prototype and it is implemented in other function
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expeted_ans);

int main(void) {
  run_check(2, 2, 3);
  //check incorrect input like the negative one (maybe it is a bad idear)

  //check for correct input----------
  //check if base is 0
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(0, 4294967295, 0);

  //check if power is 0
  run_check(4294967295, 0, 1);
  run_check(1, 0, 1);
  run_check(4294967294, 0, 1);
  //check if base is 1
  run_check(1, 2147483647, 1);
  run_check(1, 2147483648, 1);
  run_check(1, 2147483649, 1);

  //check power is 1
  run_check(4294967295, 1, 4294967295);
  run_check(0, 1, 0);
  run_check(1, 1, 1);
  run_check(4294967294, 1, 4294967294);
  run_check(2147483646, 1, 2147483646);
  run_check(-1, 1, -1);
  run_check(2147483647, 1, 2147483647);
  //checking overflow if first is int
  run_check(2147483647, 1, 2147483647);
  run_check(2147483648, 1, 2147483648);
  run_check(2147483649, 1, 2147483649);

  //run some normal cases
  run_check(3, 20, 3486784401);
  run_check(3, 3, 27);
  run_check(20, 3, 8000);
  run_check(20, 3, 8000);
  run_check(20, 3, 8000);
  run_check(65535, 2, 4294836225);

  //run some overflow

  //check
  run_check(-1, 0, 1);
  run_check(-2147483648, 0, 1);
  run_check(-2147483648, 1, -2147483648);
  run_check(-1, -1, -1);
  run_check(-1, 2, 1);
  //run_check(4294967296, 0, 1);
  //run_check(4294967295, 2, 18446744065119617000);
  //run_check(4294967296, 1, 4294967296);
  run_check(2, 2, 3);
  return EXIT_SUCCESS;
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    exit(EXIT_SUCCESS);
  }
  else {
    printf(
        "%u power to %u is not correct, the correct answer should be %u ranther than %u ",
        x,
        y,
        expected_ans,
        ans);
    exit(EXIT_FAILURE);
  }
}
