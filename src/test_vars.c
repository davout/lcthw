#include <stdio.h>
#include "dbg.h"

void try_change(int i)
{
  i = 1000;
}

int main(int argc, char *argv[])
{
  int x = 10;
  try_change(x);
  log_info("X: %d", x);
  return 0;
}
