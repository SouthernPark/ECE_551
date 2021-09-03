#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double compute(int age, double initial, retire_info info) {
  int year = age / 12;
  int mon = age % 12;
  printf("Age %3d month %2d you have $%.2lf\n", year, mon, initial);
  double res = initial * (1 + info.rate_of_return / 12) + info.contribution;
  return res;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int end = startAge + working.months;
  while (startAge < end) {
    initial = compute(startAge, initial, working);
    startAge++;
  }
  end = startAge + retired.months;
  while (startAge < end) {
    initial = compute(startAge, initial, retired);
    startAge++;
  }
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000.0;
  working.rate_of_return = 0.045;

  retire_info retire;
  retire.months = 384;
  retire.contribution = -4000.0;
  retire.rate_of_return = 0.01;

  retirement(327, 21345, working, retire);
}
