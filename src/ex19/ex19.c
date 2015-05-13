#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game_mechanics.h"

int Map_init(void *self)
{
  Map *map = self;

  // Make some rooms for a small map
  Room *hall = NEW(Room, "The great hall");
  Room *throne = NEW(Room, "The throne room");
  Room *arena = NEW(Room, "The arena with the minotaur");
  Room *kitchen = NEW(Room, "The kitchen, you have the knife now");

  // Put the bad guy in the arena
  arena->bad_guy = NEW(Monster, "The evil minotaur");

  // The actual map
  hall->north = throne;
  throne->south = hall;
  throne->west = arena;
  arena->east = throne;
  throne->east = kitchen;
  kitchen->west = throne;

  map->start = hall;
  map->location = hall;

  return 1;
}

Object MapProto = {
  .init = Map_init,
  .attack = Map_attack,
  .move = Map_move,
};

int process_input(Map *game)
{
  printf("\n > ");
  char ch = getchar();
  getchar(); // discard <Enter>

  int damage = rand() % 4;

  switch(ch) {
    case EOF:
      printf("Giving up? You suck.");
      return 0;
      break; // not necessary?

    case 'n':
      game->_(move)(game, NORTH);
      break;

    case 's':
      game->_(move)(game, SOUTH);
      break;

    case 'e':
      game->_(move)(game, EAST);
      break;

    case 'w':
      game->_(move)(game, WEST);
      break;

    case 'a':
      game->_(attack)(game, damage);
      break;

    case 'l':
      printf("You can go:\n");
      if (game->location->north) printf("NORTH\n");
      if (game->location->south) printf("SOUTH\n");
      if (game->location->east) printf("EAST\n");
      if (game->location->west) printf("WEST\n");
      break;

    case '\n': // Enter pressed, do nothing
      break;

    default:
      printf("What?: %d\n", ch);
  }

  return 1;
}

int main(int argc, char *argv[])
{
  // setup the randomness
  srand(time(NULL));

  // make our map to work with
  Map *game = NEW(Map, "The hall of the Minotaur.");

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(process_input(game)) {
  }

  return 0;
}

