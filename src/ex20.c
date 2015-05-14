#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>


void test_debug() { debug("Testing debug"); }

void test_error() { log_err("Testing error log."); }

void test_warn() { log_warn("Testing warn log."); }

void test_info() { log_info("Testing info."); }

int main(int argc, char *argv[])
{
  test_debug();
  test_error();
  test_warn();
  test_info();

  log_info("Trying first memory allocation");
  void *allocated;
  for(int i = 0; i < (1024 * 1024); i++) {
    allocated = calloc(1024 * 1024 * 1024, 1);
    check_mem(NULL);
  }

  return 0;

error:
  printf("In error block\n");
  if(allocated != NULL) free(allocated);
  return 1;
}


