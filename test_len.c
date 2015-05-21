#include <stdio.h>

int main(int argc, char **argv)
{
  char test_str[] = "test";
  char *test_str2 = "test";

  //*test_str2 = "toto";
  //*test_str = "toto";

  //printf("Actual string length: 5, including \\0\n");

  //printf("Length of first string: %d\n", sizeof(test_str));
  //printf("Length of second string: %d\n", sizeof(test_str2));
  //printf("Length of first string: %d\n", sizeof(test_str));

  //printf("Length of de-reference: %d\n", sizeof(*test_str));
  //printf("Length of de-reference: %d\n", sizeof(*test_str2));

  printf("test_str: %s\n", test_str);
  printf("test_str2: %s\n", test_str2);

  //printf("*test_str: %s\n", *test_str);
  //printf("*test_str2: %s\n", *test_str2);

  *test_str2 = 'y';
  printf("test_str2: %s\n", test_str2);

}

