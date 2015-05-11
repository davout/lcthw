#include <stdio.h>

int main(int argc, char* argv[]) {

  if (argc <= 1) {
    printf("You didn't provide any arguments, you suck\n");
  }
  else if (argc <= 4) {
    printf("You provided %d arguments, that's neat-o!\n", argc - 1);
    printf("Here they are!\n");

    for(int i = 1; i < argc; i++) {
      printf("Argument %d: %s\n", i, argv[i]);
    }
  }
  else {
    printf("You provided %d arguments, that's too much bitch!11\n", argc - 1);
  }


  return 0;
}
