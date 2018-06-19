// tr2b.c
// Zhengfu Ding 104928991
//
// Takes two operands (from) and (to)
// that are byte strings of the same length,
// and copies stdin to stdout,
// transliterating every byte in (from)
// to the corresponding byte in (to)
// Unbuffered

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  char current[1];
  int identicalInFrom = 1;
  ssize_t readTo = read(0, current, 1);
  while (readTo > 0) {
    for (i = 0; i < strlen(from); i++) {
      if (current[0] == from[i]) {
	current[0] = to[i];
	write(1, current, 1);
	identicalInFrom = 1;
	break;
      }
      else {
	identicalInFrom = 0;
      }
    }
    if (!identicalInFrom) {
      write(1, current, 1);
    }
    readTo = read(0, current, 1);
  }

  return 0;
}
