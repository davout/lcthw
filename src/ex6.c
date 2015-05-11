#include <stdio.h>

int main(int argc, char *argv[]) {
  int distance = 100;
  float power = 2.345f;
  double super_power = 56789.23479;
  char initial = 'M';
  char first_name[] = "David";
  char last_name[] = "François";

  printf("You're %d miles away.\n", distance);
  printf("You have a %f power level.\n", power);
  printf("You have a %f super power level.\n", super_power);
  printf("Your name is %s %c %s.\n", first_name, initial, last_name);

  return 0;
}
