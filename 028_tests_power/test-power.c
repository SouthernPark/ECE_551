#include <stdio.h>
#include <stdlib.h>

//decalre the prototype and it is implemented in other function
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expeted_ans);

int main(void) {
  //check incorrect input like the negative one (maybe it is a bad idear)

  //check for correct input----------
  //check if base is 0

  run_check(0, 0, 1);
  run_check(0, 1, 0);

  //check if power is 0

  run_check(1, 0, 1);

  //check power is 1

  run_check(0, 1, 0);
  run_check(1, 1, 1);

  //run some normal cases
  run_check(3, 20, 3486784401);
  run_check(3, 3, 27);
  run_check(20, 3, 8000);
  run_check(20, 3, 8000);
  run_check(20, 3, 8000);

  //run some overflow

  //run_check(4294967296, 0, 1);
  //run_check(4294967295, 2, 18446744065119617000);
  //run_check(4294967296, 1, 4294967296);

  return EXIT_SUCCESS;
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    //exit(EXIT_SUCCESS);
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
