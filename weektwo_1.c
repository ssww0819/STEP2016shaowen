/*
ファイルに格納された正方行列を読み込み、掛け算をする
3*3の行列matrix1.txt matrix2.txt で計算して、結果をチェックした。
しかし、計算量とサイズの関係を調べるには、いろいろなサイズの行列のファイルを作らなければならないので、weektwo_2を作った
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time() {
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

int main (int argc, char* argv[]) {

  //Read the first matrix from file, the column and the row are the same (N*N)

  FILE *fp1;
  fp1 = fopen(argv[1], "r");

  if (fp1 == NULL) {
    printf("File open failed\n");
    return 1;
  }

  int c;
  int size_1 = 0;
  while ((c = getc(fp1)) != EOF) {
    if (c == '\n') {
      size_1++;
    }
  }

  fseek(fp1, 0L, SEEK_SET);

  //put the first matrix into **matrix1
  int a;
  double **matrix1;
  matrix1 = (double**)malloc(sizeof(double*) * size_1);
  for (a = 0; a < size_1; a++) {
    *(matrix1 + a) = (double*)malloc(sizeof(double) * size_1);
  }  
  int i, j;
  for (i = 0; i < size_1; i++) {
    for (j = 0; j < (size_1 - 1); j++) {
      fscanf(fp1, "%lf,", *(matrix1+i)+j);      
    }
    fscanf(fp1, "%lf\n", *(matrix1+i)+j);
  }

  //read the second matrix and put it into **matrix2
  FILE *fp2;
  fp2 = fopen(argv[2], "r");

  if (fp2 == NULL) {
    printf("File open failed\n");
    return 1;
  }

  int size_2 = 0;
  while ((c = getc(fp2)) != EOF) {
    if (c == '\n') {
      size_2++;
    }
  }
  
  double **matrix2;
  matrix2 = (double**)malloc(sizeof(double*) * size_2);
  for (a = 0; a < size_2; a++) {
    *(matrix2 + a) = (double*)malloc(sizeof(double) * size_2);
  }
  
  if (size_1 != size_2) {
    printf("Disable to multiply because the size is different\n");
    exit(1);
  }
  else {
    fseek(fp2, 0L, SEEK_SET); 
    int i, j;
    for (i = 0; i < size_1; i++) {
      for (j = 0; j < (size_1 - 1); j++) {
	fscanf(fp2, "%lf,", *(matrix2+i)+j);      
      }
      fscanf(fp2, "%lf\n", *(matrix2+i)+j);
    }
  }
  
  double **matrix3;
  matrix3 = (double**) malloc(sizeof(double*) * size_1);
  for (a = 0;a < size_1;a++) {
    *(matrix3 + a) = (double*)malloc(sizeof(double) * size_1);
  }
  
  //calculate and measure the time
  double begin = get_time();

  multiply(matrix3, matrix1, matrix2, size_1);

  double end = get_time();
  printf("time: %.12lf sec\n", end - begin);

  //print matrix1,2,3 for debug
  printf("matrix1 = \n");
  for (i = 0;i < size_1;i++) {
    for (j = 0;j < size_1;j++) {
      if(j == size_1 - 1) {
	printf("%f\n",matrix1[i][j]);
      } else {
	printf("%f,",matrix1[i][j]);
      }
    }
  }
  printf("matrix2 = \n");
  for (i = 0;i < size_1;i++) {
    for (j = 0;j < size_1;j++) {
      if(j == size_1 - 1) {
	printf("%f\n",matrix2[i][j]);
      } else {
	printf("%f,",matrix2[i][j]);
      }
    }
  }
  printf("matrix1 * matrix2 = \n");
  for (i = 0;i < size_1;i++) {
    for (j = 0;j < size_1;j++) {
      if(j == size_1 - 1) {
	printf("%f\n",matrix3[i][j]);
      } else {
	printf("%f,",matrix3[i][j]);
      }
    }
  }
  
  return 0;
}

