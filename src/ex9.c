#include <stdio.h>

int main(int argc, char* argv[]) {

  int numbers[4] = { 0 };
  char name[4] = { 'a', 'a', 'a', 'a' };

  // print them out raw
  printf("The numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
  printf("The name: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

  // Print the name like a string
  printf("Name: %s\n", name);

  // Setup
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  name[0] = 'D';
  name[1] = 'a';
  name[2] = 'v';
  name[3] = '\0';

  // print them out initialized
  printf("The numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
  printf("The name: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

  // Print the name like a string
  printf("Name: %s\n", name);

  // Another way to setup a string
  char* dave = "Dav";

  printf("Dave: %s\n", dave);

  printf("Dave each: %c %c %c %c\n", dave[0], dave[1], dave[2], dave[3]);

  return 0;
}
