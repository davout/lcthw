#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "David FRANCOIS";

void scope_demo(int count)
{
  log_info("Count is %d", count);

  if(count > 10) {
    int count = 100;
    log_info("In this scope count is %d", count);
  }

  log_info("Count at exit is %d", count);

  count = 3000;

  log_info("Count after assign is %d", count);
}


int main(int argc, char *argv[])
{
  // Test THE_AGE accessors
  log_info("The age is %d", get_age());
  set_age(100);
  log_info("The age is now %d", get_age());

  // Test THE_SIZE extern
  log_info("THE_SIZE is %d", THE_SIZE);
  print_size();

  // Test the ratio function static
  log_info("Ratio at first %f", update_ratio(2.0));
  log_info("Ratio again %f", update_ratio(10.0));
  log_info("Ratio finally %f", update_ratio(200.0));

  // Test the scope demo
  int count = 4;
  scope_demo(count);
  scope_demo(count * 20);

  log_info("Count after calling scope_demo %d", count);

  return 0;
}
