#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  unsigned long allcd = 0;

  srand(time(NULL));

  while(1) {
    int *fuckyou = (int *)malloc(1024);
    if(fuckyou == NULL) {
      printf("Failed to allocate moar, already allocated %lu bytes.\n", allcd);
      return 1;
    } else {
      *fuckyou = rand();
      allcd += 1024;
    }
  }

  return 0;
}

