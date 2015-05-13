#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self)
{
  assert(self != NULL);

  Object *obj = self;

  if(obj) {
    if(obj->description) free(obj->description);
    free(obj);
  }
}

void Object_describe(void *self)
{
  Object *obj = self;
  printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
  // Do nothing
  return 1;
}

void *Object_move(void *self, Direction direction)
{
  printf("You can't go that way.\n");
  return NULL;
}

int Object_attack(void *self, int damage)
{
  printf("You can't attack that.\n");
  return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
  // Setup default functions in case they aren't set
  if(!proto.init) proto.init = Object_init;
  if(!proto.describe) proto.describe = Object_describe;
  if(!proto.destroy) proto.destroy = Object_destroy;
  if(!proto.attack) proto.attack = Object_attack;
  if(!proto.move) proto.move = Object_move;

  // this seems weird, but we can make a struct of one size,
  // then point a different pointer to it to "cast" it
  Object *el = calloc(1, size);
  *el = proto;

  // copy the description over
  el->description = strdup(description);

  if(!el->init(el)) {
    el->destroy(el);
    return NULL;
  } else {
    // all done, we made an object of any type
    return el;
  }
}

