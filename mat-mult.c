#include <stdlib.h>
#include <stdio.h>

int validateArguments(int argc, char **argv, int *m, int *n, int *seed) {
  // Check the program has the correct number of arguments
  if (argc != 4) {
    printf("Incorrect argument count");
    printf("Usage: ./mat-mult <M> <N> <seed>");
    return 0;
  }

  *m = atoi(argv[1]);
  // Check m argument
  if (*m < 1 || *m > 99) {
    printf("Incorrect argument m\n");
    printf("m must be an integer between 1 and 99\n");
    return 0;
  }

  *n = atoi(argv[2]);
  // Check n argument
  if (*n < 1 || *n > 99) {
    printf("Incorrect argument n\n");
    printf("n must be an integer between 1 and 99\n");
    return 0;
  }

  *seed = atoi(argv[3]);
  // Check seed argument
  if (*seed == 0 && argv[3][0] != '0') {
    printf("Incorrect argument seed\n");
    printf("seed must be an integer\n");
    return 0;
  }

  return 1;
}

void main(int argc, char **argv) {
  int m, n, seed;

  if(!validateArguments(argc, argv, &m, &n, &seed)) {
      printf("Returning\n");
      return;
    }

    // Set the seed according to the command line argument
    srand(seed);

  return;
}
