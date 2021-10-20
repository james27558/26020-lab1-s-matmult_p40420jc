#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

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

int** allocate2DArray(int i, int j) {
  int **matrix = malloc(i * sizeof(int*));
  if (matrix == NULL) return NULL;

  // Allocate the rows of the 2D matrix
  for (int k = 0; k < i; k++) {
    matrix[k] = malloc(j * sizeof(int));
    if (matrix[k] == NULL) return NULL;

  }

  return matrix;
}

void fill2DArrayWithRand(int **matrix, int i, int j) {
  for (int k = 0; k < i; k++) {
    // Set the elements in this row to random numbers between 1 and 99
    for (int l = 0; l < j; l++) {
      matrix[k][l] = rand() % 100;
    }
  }
}

void print2DArray(int **matrix, int rowCount, int columnCount) {
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < columnCount; j++) {
      printf("%d ", matrix[i][j]);
    }

    printf("\n");
  }
}

void printMatrix1(int **matrix, int row, int column) {
  printf("MATRIX 1:\n");
  print2DArray(matrix, row, column);
}

void printMatrix2(int **matrix, int row, int column) {
  printf("MATRIX 2:\n");
  print2DArray(matrix, row, column);
}

void printResult(int **result, int row, int column) {
  printf("RESULT:\n");
  print2DArray(result, row, column);
}

void multiplyMatricies(int **m1, int **m2, int **outputMatrix, int m1RowDim, int m1ColDim, int m2RowDim, int m2ColDim) {
  for (int i = 0; i < m1RowDim; i++) {
    for (int j = 0; j < m2ColDim; j++) {
      int sum = 0;

      for (int k = 0; k < m1ColDim; k++) {
        sum += m1[i][k] * m2[k][j];
        //printf("[%d][%d] sum += m1[%d][%d] (%d) * m2[%d][%d] (%d)\n", i, j, i, k, m1[i][k], k, j, m2[k][j]);
      }

      outputMatrix[i][j] = sum;
    }
  }
}

void main(int argc, char **argv) {
  int m, n, seed;

  // Validate the command line arguments
  if(!validateArguments(argc, argv, &m, &n, &seed)) {
      printf("Exiting...\n");
      return;
    }

    // Set the seed according to the command line argument
    srand(seed);

    // Allocate memory for the first array
  int **matrix1 = allocate2DArray(m, n);

  if (matrix1 == NULL) {
    printf("An error occured while allocating memory for matrix1");
    return;
  }

  // Allocate memory for the second array
  int **matrix2 = allocate2DArray(n, m);

  if (matrix2 == NULL) {
    printf("An error occured while allocating memory for matrix2");
    return;
  }

  // Put random numbers in the matricies
  fill2DArrayWithRand(matrix1, m, n);
  fill2DArrayWithRand(matrix2, n, m);

  // Print matrix 1 and matrix 2
  printMatrix1(matrix1, m, n);
  printMatrix2(matrix2, n, m);

  int **result = allocate2DArray(m, m);

  struct timeval tStart, tEnd, tElapsed;

  gettimeofday(&tStart, NULL);
  multiplyMatricies(matrix1, matrix2, result, m, n, n, m);
  gettimeofday(&tEnd, NULL);

  timersub(&tEnd, &tStart, &tElapsed);

  printResult(result, m, m);

  printf("EXECUTION TIME: %lu.%06lu seconds\n", tElapsed.tv_sec, tElapsed.tv_usec);

  return;
}
