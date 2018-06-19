// tr2b.c
// Zhengfu Ding 104928991
//
// Takes two operands (from) and (to)
// that are byte strings of the same length,
// and copies stdin to stdout,
// transliterating every byte in (from)
// to the corresponding byte in (to)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
  // check arguments
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of arguments\n");
    exit(1);
  }

  // (from) and (to)
  char *from = argv[1];
  char *to = argv[2];
  
  // check if (from) and (to) are equal length
  if (strlen(from) != strlen(to)) {
    fprintf(stderr, "Inputs are not of equal length\n");
    exit(1);
  }

  // check for duplicates
  int i;
  int j;
  for (i = 0; i < strlen(from); i++) {
    for (j = i+1; j < strlen(from); j++) {
      if (from[j] == from[i]) {
	fprintf(stderr, "From has duplicate bytes\n");
	exit(1);
      }
    }
  }

  // for each character stdin, print corresponding character to stdout, else print same character
  char current = getchar();
  int identicalInFrom = 0;
  while (current != EOF) {
    for (i = 0; i < strlen(from); i++) {
      if (current == from[i]) {
	  putchar(to[i]);
	  identicalInFrom = 1;
	  break;
      }
      else {
	identicalInFrom = 0;
      }
    }
    if (!identicalInFrom) {
      putchar(current);
    }
    current = getchar();
  }

  return 0;
}
