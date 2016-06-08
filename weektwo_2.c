/*
行列の初期化をコードの中で行う。
これで、いろいろなサイズの行列の掛け算をして、計算量とサイズの関係を調べる
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

double c(int i, int j, int m, double** A, double **B) {
  double sum = 0;
  int k;
  for (k = 0;k < m;k++) {
    sum += A[i][k] * B[k][j];
  }
  return sum;
}

void multiply (double **sol, double **A, double **B, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      sol[i][j] = c(i, j, size, A, B);
    }
  }
}

int main(int argc, char** argv)
{
  int size = atoi(argv[1]);
  int a;
  int i,j;
  double **matrix1;
  matrix1 = (double**)malloc(sizeof(double*) * size);
  for (a = 0; a < size; a++) {
    *(matrix1 + a) = (double*)malloc(sizeof(double) * size);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      matrix1[i][j] = i * size + j;    
    }
  }
  double **matrix2;
  matrix2 = (double**)malloc(sizeof(double*) * size);
  for (a = 0; a < size; a++) {
    *(matrix2 + a) = (double*)malloc(sizeof(double) * size);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      matrix2[i][j] = j * size + i;    
    }
  }
  double **matrix3;
  matrix3 = (double**) malloc(sizeof(double*) * size);
  for (a = 0;a < size;a++) {
    *(matrix3 + a) = (double*)malloc(sizeof(double) * size);
  }
  
  double begin = get_time();

  multiply(matrix3, matrix1, matrix2, size);
  
  double end = get_time();
  
  printf("time: %.6lf sec\n", end - begin);
  // Print C for debugging. Comment out the print before measuring the execution time.
  /*
  double sum = 0;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      sum += matrix3[i][j];
    }
  }
  printf("sum: %.6lf\n", sum);
  */
  for (a = 0; a < size; a++) {
    free (*(matrix1 + a));
  }
  free(matrix1);
  free(matrix2);
  free(matrix3);

  return 0;
}
