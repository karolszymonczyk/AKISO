#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define ONE_OVER_THOUSAND 1E-3
#define MILION 1E6

//gcc -o script script.c -lpthread

int rowsDone = 0;

typedef struct {
  int **matrix1;
  int **matrix2;
  int **result;
  int size;
} Matrices;

int ** placeForMatrix(int size);
void matrixFill(int **matrix, int size);
void *matrixMultiplication(void *vargp);

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("wrong input arguments!\n");
    exit(1);
  }
  struct timespec start, end;
  int matrixSize = atoi(argv[1]);
  int threadsAmount = atoi(argv[2]);
  Matrices matrix;
  matrix.matrix1 = placeForMatrix(matrixSize);
  matrix.matrix2 = placeForMatrix(matrixSize);
  matrix.result = placeForMatrix(matrixSize);
  matrix.size = matrixSize;

  printf("Filling matrix with random values...\n");

  matrixFill(matrix.matrix1, matrixSize);
  matrixFill(matrix.matrix2, matrixSize);
  pthread_t ptIDs[threadsAmount];

  printf("Multiplication...\n");

  clock_gettime(CLOCK_REALTIME, &start);
  time_t t1ns = start.tv_nsec/MILION;
  time_t t1s = start.tv_sec;

  for (int i = 0; i < threadsAmount; i++) {
    pthread_create(&ptIDs[i], NULL, matrixMultiplication, (void *)&matrix);
  }

  clock_gettime(CLOCK_REALTIME, &end);
  time_t t2ns = end.tv_nsec/MILION;
  time_t t2s = end.tv_sec;
  double multiplicationTime = (t2s - t1s) + (t2ns - t1ns) * ONE_OVER_THOUSAND;
  printf("multiplication time: %.*lfs\n", 3, multiplicationTime);

  return 0;
}

int ** placeForMatrix(int size) {
  int **matrix = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    matrix[i] = (int *)malloc(size * sizeof(int));
  }
  return matrix;
}

void matrixFill(int **matrix, int size) {
  time_t t;
  srand(time(&t));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = (rand()%2);
    }
  }
}

void *matrixMultiplication(void *vargp) {
  Matrices *matrix = (Matrices*)&vargp;
  for (int i = rowsDone ; i < rowsDone; rowsDone++) {
    for (int j = 0; j < (*matrix).size; j++) {
      int value = 0;
      for (int k = 0; k < (*matrix).size; k++) {
        value |= ((*matrix).matrix1[i][k] & (*matrix).matrix2[k][j]);
        if (value) {
          break;
        }
      }
      (*matrix).result[i][j] = value;
    }
  }
}