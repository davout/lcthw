#include <stdio.h>

int main(int argc, char* argv[]) {

  int areas[] = { 10, 12, 13, 14, 20 };
  char name[] = "David F.";
  char full_name[] = { 'D', 'a', 'v', 'i', 'd', '\0' };

  printf("The size of an int %ld.\n", sizeof(int));
  printf("The size of areas (int[]) %ld.\n", sizeof(areas));
  printf("The number of ints in areas %ld.\n", sizeof(areas)/sizeof(int));
  printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);
  printf("The size of a char %ld.\n", sizeof(char));
  printf("The size of name (char[]) %ld.\n", sizeof(name));
  printf("The number of chars in name %ld.\n", sizeof(name)/sizeof(char));
  printf("The size of full_name (char[]) %ld.\n", sizeof(full_name));
  printf("The number of chars in full_name %ld.\n", sizeof(name)/sizeof(char));

  printf("Name and full name, %s, %s.\n", name, full_name); 

  return 0;
}

