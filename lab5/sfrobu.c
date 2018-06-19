//
//  sfrobu.c
//  Zhengfu Ding 104928991
//
//  Sorts frobnicated words in unfrobnicated 
//  order without sorting the 
//  unfrobnicated values into memeory
//  using systen calls to read stdin and write stdout
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <ctype.h>

int f = 0;   // -f option boolean

void checkFileError() {
  if(ferror(stdin)) {
    fprintf(stderr, "Error reading file\n");
    exit(1);
  }
}

void checkMemoryError(void* ptr) {
  if(ptr == NULL) {
    fprintf(stderr, "Error in memory\n");
    exit(1);
  }
}

// compare frobnicated words
int frobcmp(char const *a, char const *b)
{
  if (f) {
    if ((*a ^ 42) > UCHAR_MAX || (*a ^ 42) < 0 || (*b ^ 42) > UCHAR_MAX || (*b ^ 42) < 0) {
      fprintf(stderr, "Characters can't be used with '-f' options\n");
      exit(1);
    }
    // compares words character by character disregarding cases
    for(;; a++, b++) {
      if(*a == ' ' && *b == ' ') {
        return 0;
      }
      else if(*a == ' ' || (toupper(*a ^ 42) < toupper(*b ^ 42))) {
        return -1;
      }
      else if(*b == ' ' || (toupper(*a ^ 42) > toupper(*b ^ 42))) {
        return 1;
      }
    }
  }
  else {
    // compares words character by character
    for(;; a++, b++) {
      if(*a == ' ' && *b == ' ') {
	return 0;
      }
      else if(*a == ' ' || ((*a ^ 42) < (*b ^ 42))) {
	return -1;
      }
      else if(*b == ' ' || ((*a ^ 42) > (*b ^ 42))) {
	return 1;
      }
    }
  }
}

// takes pointers to words for qsort
int cmp(const void* input1, const void* input2)
{
  // cast pointers to pointers to use for frobcmp()
  const char* a = *(const char**)input1;
  const char* b = *(const char**)input2;
  return frobcmp(a,b);
}

int main(int argc, const char* argv[])
{
  // parse arguments
  if (argc > 2) {
    fprintf(stderr, "Too many arguments\n");
    exit(1);
  }
  else if (argc == 2) {
    if(!strcmp(argv[1], "-f")) {
      f = 1;
    } 
    else {
      fprintf(stderr, "Invalid arguments\n");
      exit(1);
    }
  }

  // check file status
  struct stat fileStatus;
  if(fstat(0, &fileStatus) < 0) {
    fprintf(stderr, "File status error\n");
    exit(1);
  }

  char* word;   // pointer to a word array
  int wordSize;  // tracks size of word array               
  int wordIndex; // tracks current letter    

  if(S_ISREG(fileStatus.st_mode)) {
    // for regular files, read entire file
    wordSize = fileStatus.st_size;
    wordIndex = wordSize;
    // allocate memory
    word = malloc(sizeof(char) * (wordSize+1));
    if (read(0, word, wordSize) < 0) {
      fprintf(stderr, "Error reading file\n");
      exit(1);
    }
  }
  else {
    // for irregular files, read character by character
    // allocate memory
    word = malloc(sizeof(char));
    checkMemoryError(word);
    wordSize = 1;
    wordIndex = 0;

    char* currentChar = malloc(sizeof(char*));
    while (read(0, currentChar, 1) > 0) {
      checkFileError();
      // add current character to word
      word[wordIndex] = *currentChar;
      wordIndex = wordIndex + 1;
      // if word is too small, double its size
      if(wordSize <= wordIndex) {
        wordSize = wordSize * 2;
        word = (char*) realloc(word, sizeof(char) * wordSize);
        checkMemoryError(word);
      }
    }
    free(currentChar);
  }
  
  word[wordIndex] = ' ';

  char** words; // array of pointers to words
  words = (char**) malloc(sizeof(char*));
  int wordsSize = 1;  // tracks size of words array
  int wordsIndex = 0; // tracks current word

  checkMemoryError(words);

  int x;
  int done = 1;  // boolean for each word
  for (x = 0; x < wordIndex; x++) {
    if (word[x] == ' ') {
      // end word
      done = 1;
    }
    else if (done) {
      done = 0;
      words[wordsIndex] = word + (x * sizeof(char));
      wordsIndex++;

      // if words is too small, double its size
      if (wordsSize <= wordsIndex) {
        wordsSize = wordsSize * 2;
        words = (char**) realloc(words, sizeof(char*) * wordsSize);
        checkMemoryError(words);
      }
    }
  }

  // sorts words
  qsort(words, wordsIndex, sizeof(char*), &cmp);

  // print sorted words
  int i;
  int j;
  for (i = 0; i < wordsIndex; i++) {
    for(j = 0; words[i][j] != ' ';j++) {
      if (write(1, words[i], j+1) <= 0) {
	fprintf(stderr, "Writing error\n");
      }
    }
  }

  // free memory
  free(word);
  free(words);
  exit(0);
}
