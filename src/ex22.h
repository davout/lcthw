#ifndef _ex22_h
#define _ex22_h

// Makes THE_SIZE in ex22.c available to other .c files
extern int THE_SIZE;

// gets and sets an internal variable in ex22.c
int get_age();
void set_age(int age);

// updates a specific static variable that's inside udpate_ratio
double update_ratio(double ratio);

void print_size();

#endif

