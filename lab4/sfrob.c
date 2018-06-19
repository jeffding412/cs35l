//
//  sfrob.c
//  Zhengfu Ding
//  104928991
//  May 3, 2018
//
//  Sorts frobnicated words in unfrobnicated 
//  order without sorting the 
//  unfrobnicated values into memeory
//

#include <stdio.h>
#include <stdlib.h>

void checkFileError() {
  if(ferror(stdin)) {
    fprintf(stderr, "Error reading file");
    exit(1);
  }
}

void checkMemoryError(void* ptr) {
  if(ptr == NULL) {
    fprintf(stderr, "Error in memory");
    exit(1);
  }
}

// compare frobnicated words
int frobcmp(char const *a, char const *b)
{
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

// takes pointers to words for qsort
int cmp(const void* input1, const void* input2)
{
  // cast pointers to pointers to use for frobcmp()
  const char* a = *(const char**)input1;
  const char* b = *(const char**)input2;
  return frobcmp(a,b);
}

int main(void)
{
  char* word;   // pointer to a word array
  char** words; // array of pointers to words

  // allocate memory
  word = (char*) malloc(sizeof(char));
  int wordSize = 1;  // tracks size of word array
  int wordIndex = 0; // tracks current letter
  words = (char**) malloc(sizeof(char*));
  int wordsSize = 1;  // tracks size of words array
  int wordsIndex = 0; // tracks current word

  char current; // current char
  int end = 0;  // boolean for EOF
  
  // get character until EOF
  while(!end) {
    current = getchar();
    checkFileError();

    // if at end, add space to last word
    if(current == EOF) {
      end = 1;
      current = ' ';
    }

    // if word is too small, double its size
    if(wordSize <= wordIndex) {
      wordSize = wordSize * 2;
      word = (char*) realloc(word, sizeof(char) * wordSize);
      checkMemoryError(word);
    }

    // add current character to word
    word[wordIndex] = current;
    wordIndex = wordIndex + 1;

    // add word to words and start over
    if(current == ' ') {
      // if words is too small, double its size
      if(wordsSize <= wordsIndex) {
	wordsSize = wordsSize * 2;
	words = (char**) realloc(words, sizeof(char*) * wordsSize);
	checkMemoryError(words);
      }

      // add word to words
      words[wordsIndex] = word;
      wordsIndex = wordsIndex + 1;

      // reset for next word
      word = (char*) malloc(sizeof(char));
      checkMemoryError(word);
      wordSize = 1;
      wordIndex = 0;
    }
  }

  // sorts words
  qsort(words, wordsIndex, sizeof(char*), &cmp);

  // print sorted words
  int i;
  int j;
  for (i = 0; i < wordsIndex; i++) {
    for(j = 0;;j++) {
      putchar(words[i][j]);
      checkFileError();
      if(words[i][j] == ' ') {
	break;
      }
    }
  }

  // free memory
  free(word);
  for(i = 0; i < wordsIndex; i++) {
    free(words[i]);
  }

  free(words);
  exit(0);
}
