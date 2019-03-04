#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ONE_OVER_THOUSAND 1E-3
#define MILION 1E6

int ** placeForMatrix(int size);
void fillMatrix(int **matrix, int size);
void fillTempMatrix(int **matrix, int size);
void swap(int *x, int *y);
void swapPointers(int **x, int **y);
void multiplication(int **matrix1, int **matrix2, int size, int **result);
void dMatrixMultiplication(int **matrix1, int **matrix2, int size, int **result);
void transposition(int **matrix, int size);
void transposeMatrix(int **matrix, int size, int **result);
void multiplicationT(int **matrix1, int **matrix2, int size, int **result);
void dMatrixMultiplicationT(int **matrix1, int **matrix2, int size, int **result);
void dMatrixLoopOptimazation(int **matrix1, int **matrix2, int size, int **result);
void optimisedMultiplication(int **matrix1, int **matrix2, int size, int **result);

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("wrong input arguments!\n");
    exit(1);
  }
  int size = atoi(argv[1]);
  printf("size: %d\n", size);
  int **matrix1 = placeForMatrix(size);
  int **matrix2 = placeForMatrix(size);
  fillMatrix(matrix1, size);
  fillMatrix(matrix2, size);
  int **result = placeForMatrix(size);
  fillTempMatrix(result, size);
  multiplication(matrix1, matrix2, size, result);
  multiplicationT(matrix1, matrix2, size, result);
  optimisedMultiplication(matrix1,matrix2,size,result);

return 0;
}

int ** placeForMatrix(int size) {
  int **matrix = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    matrix[i] = (int *)malloc(size * sizeof(int));
  }
  return matrix;
}

void fillMatrix(int **matrix, int size) {
  time_t t;
  srand(time(&t));
    for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = rand()%100;
    }
  }
}

void fillTempMatrix(int **matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = 0;
    }
  }
}

void swap(int *x, int *y) {
  *x = *x + *y;
  *y = *x - *y;
  *x = *x - *y;
}

void swapPointers(int **x, int **y) {
  int *tmp = *x;
  *x = *y;
  *y = tmp;
}

void multiplication(int **matrix1, int **matrix2, int size, int **result) {
  struct timespec start, end;
  clock_gettime(CLOCK_REALTIME, &start);
  time_t t1ns = start.tv_nsec/MILION;
  time_t t1s = start.tv_sec;
  dMatrixMultiplication(matrix1, matrix2, size, result);
  clock_gettime(CLOCK_REALTIME, &end);
  time_t t2ns = end.tv_nsec/MILION;
  time_t t2s = end.tv_sec;
  double multiplicationTime = (t2s - t1s) + (t2ns - t1ns) * ONE_OVER_THOUSAND;
  printf("multiplication time\n");
  printf("%.*lfs\n", 3, multiplicationTime);
}

void dMatrixMultiplication(int **matrix1, int **matrix2, int size, int **result) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        result[i][j] += matrix1[i][k]*matrix2[k][j];
      }
    }
  }
}

void transposition(int **matrix, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int k = i + 1; k < size; k++) {
      swap(&matrix[i][k], &matrix[k][i]);
    }
  }
}

void transposeMatrix(int **matrix, int size, int **result) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      int *p1 = &result[i][j];
      int *p2 = &matrix[j][i];
      swapPointers(&p1, &p2);
    }
  }
}

void dMatrixMultiplicationT(int **matrix1, int **matrix2, int size, int **result) {
  int **transposed = placeForMatrix(size);
  transposeMatrix(matrix2, size, transposed);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        result[i][j] += transposed[i][k]*matrix1[j][k];
      }
    }
  }
}

void multiplicationT(int **matrix1, int **matrix2, int size, int **result) {
  struct timespec start, end;
  clock_gettime(CLOCK_REALTIME, &start);
  time_t t1ns = start.tv_nsec/MILION;
  time_t t1s = start.tv_sec;
  dMatrixMultiplicationT(matrix1, matrix2, size, result);
  clock_gettime(CLOCK_REALTIME, &end);
  time_t t2ns = end.tv_nsec/MILION;
  time_t t2s = end.tv_sec;
  double multiplicationTime = (t2s - t1s) + (t2ns - t1ns) * ONE_OVER_THOUSAND;
  printf("transposition multiplication time\n");
  printf("%.*lfs\n", 3, multiplicationTime);
}

void dMatrixLoopOptimazation(int **matrix1, int **matrix2, int size, int **result) {
  int ac00, ac01, ac10, ac11;
  for (int i = 0; i < size; i += 2) {
    for (int j = 0; j < size; j += 2) {
      ac00 = ac01 = ac10 = ac11 = 0;
      for (int k = 0; k < size; k++) {
        ac00 += matrix2[k][j + 0] * matrix1[i + 0][k];
        ac01 += matrix2[k][j + 1] * matrix1[i + 0][k];
        ac10 += matrix2[k][j + 0] * matrix1[i + 1][k];
        ac11 += matrix2[k][j + 1] * matrix1[i + 1][k];
      }
      result[i + 0][j + 0] = ac00;
      result[i + 0][j + 1] = ac01;
      result[i + 1][j + 0] = ac10;
      result[i + 1][j + 1] = ac11;
    }
  }
}

void optimisedMultiplication(int **matrix1, int **matrix2, int size, int **result) {
  struct timespec start, end;
  clock_gettime(CLOCK_REALTIME, &start);
  time_t t1ns = start.tv_nsec/MILION;
  time_t t1s = start.tv_sec;
  dMatrixLoopOptimazation(matrix1, matrix2, size, result) ;
  clock_gettime(CLOCK_REALTIME, &end);
  time_t t2ns = end.tv_nsec/MILION;
  time_t t2s = end.tv_sec;
  double multiplicationTime = (t2s - t1s) + (t2ns - t1ns) * ONE_OVER_THOUSAND;
  printf("optimised multiplication time\n");
  printf("%.*lfs\n", 3, multiplicationTime);
}