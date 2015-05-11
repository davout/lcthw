#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) 
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(struct Person *who)
{
  assert(who != NULL);

  free(who->name);
  free(who);
}

void Person_age(struct Person *who, int years)
{
  who->age += years;
  who->height -= (years/10);
  who->weight += (years/8);
}

void Person_print(struct Person *who)
{
  printf("---------------------------\n");
  printf("Name   : %s\n", who->name);
  printf("Age    : %d\n", who->age);
  printf("Height : %d\n", who->height);
  printf("Weight : %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  struct Person *david    = Person_create("David FRANCOIS", 31, 189, 75);
  struct Person *nicolas  = Person_create("Nicolas PAPON", 32, 180, 74);

  Person_print(david);
  Person_print(nicolas);

  Person_age(david, 20);
  Person_age(nicolas, 30);

  Person_print(david);
  Person_print(nicolas);

  //Person_destroy(david);
  //Person_destroy(nicolas);

  return 0;
}

