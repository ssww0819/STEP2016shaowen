#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("File open failed\n");
    return 1;
  }

  int c;
  int ct;
  while (( c = getc(fp)) != EOF) {
    if (c == '\n') {
      ct++;
    }
  }

  fseek(fp, 0L, SEEK_SET);

  //printf("%d\n", ct);
  
}
