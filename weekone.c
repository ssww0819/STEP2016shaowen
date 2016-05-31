#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 17

int compare_char(const void *a, const void *b) {
  return *(char*)a - *(char*)b;
}

int main(int argc, char* argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");  //dictionary
  if (fp == NULL) {
    printf("File open failed\n");
    return 1;
  }
  char input[17];
  puts("Please type 16 characters");
  fgets(input, 17, stdin);
  //printf("%s\n", input);
  
  int c;
  int ct = 0;
  while (( c = getc(fp)) != EOF) {
    if (c == '\n') {
      ct++;
    }
  }

  fseek(fp, 0L, SEEK_SET);

  //printf("%d\n", ct);

  const int size_d = ct;

  char dictionary[size_d][MAX];

  int i = 0;
  
  while (fscanf(fp, "%s\n", dictionary[i])!= EOF) {
    //printf("%s\n", dictionary[i]);
    i++;
  }
  qsort(input, 16, sizeof(char), compare_char);

  //printf("%s\n", input);

  char dictionary_sort[size_d][MAX];

  char *a, *b;
  a = (char*)malloc(sizeof(char));
  b = (char*)malloc(sizeof(char));
  int len = 0;
  int match = 0;
  int maxlen = 0;
  char result[MAX];

  for (i = 0; i < size_d; i++) {
    strcpy(dictionary_sort[i], dictionary[i]);
    if (dictionary_sort[i][0] >= 65 && dictionary_sort[i][0] <= 90) {
      dictionary_sort[i][0] = dictionary_sort[i][0] + 32;
    }
    len = strlen(dictionary_sort[i]);
    qsort(dictionary_sort[i], strlen(dictionary_sort[i]), sizeof(char), compare_char);
    //printf("%s\n", dictionary_sort[i]);
    a = input;
    b = dictionary_sort[i];
    match = 0;
    while ((*a) != '\0' && (*b) != '\0') {
      if ((*a) == (*b)) {
	a++;
	b++;
	match++;
      }
      else {
	a++;
      }
    }
    if (match == len && len > maxlen) {
      maxlen = len;
      strcpy(result, dictionary[i]);
    }
  }

  printf("The longest word using the given 16 letters is %s\n", result);

  return 0;
  
}
