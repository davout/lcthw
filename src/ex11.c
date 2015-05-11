#include <stdio.h>

int main(int argc, char *argv[]) {

  int i = argc - 1;

  while(i >= 0) {
    printf("arg %d: %s\n", i, argv[i]);
    i--;
  }

  char *states[] = {
    "California",
    "Oregon",
    "Liberland"
  };

  int num_states = 3;
  i = num_states - 1;

  while(i >= 0) {
    printf("State %d: %s\n", i, states[i]);
    i--;
  }

  return 0;
}
