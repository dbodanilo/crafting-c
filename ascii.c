#include <stdio.h>
#include <stdlib.h>

int main() {
  char str[10];

  while (scanf("%s", str) != EOF) {
    long int code = strtol(str, NULL, 2);
    char c = code;
    printf("%c ", c);
  }
  puts("");

  return 0;
}

