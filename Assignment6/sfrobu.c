//
//  sfrob.c
//  Created by Bryan Ho on 10/28/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int comparison = 0;

char decode(char a) {
  return (char)(a^42);
}

int frobcmp(const void *a, const void *b) {
  comparison++;
  char *wordA = *(char**)a; //Retrieve first word from arguments
  char *wordB = *(char**)b; //Retrieve second word from arguments

  int iter = 0; //Same iterator position through both words

  //Iterate through characters between words
  while (wordA[iter] != ' ' && wordB[iter] != ' ') {
    if (decode(wordA[iter]) < decode(wordB[iter])) return -1; //A < B
    else if (decode(wordA[iter]) > decode(wordB[iter])) return 1; //A > B
    iter++;
  }

  if (wordA[iter] == wordB[iter]) return 0; //A == B
  if (decode(wordA[iter]) == ' ') return -1; //A less characters than B
  else return 1;
}

//Checks for proper allocation of memory given *char
void checkAlloc(char *in) {
  if (in == NULL) { //Will be null of unable to allocate memory
    fprintf(stderr, "Error allocating memory"); //Error to stderr
    exit(1); //Exit code 1 from assignment specification
  }
}

int main(void) {

  int size = 1000; //Initial size I chose
  char *val = malloc(sizeof(char) * size); //Allocate with initial size
  checkAlloc(val); //Check for successful allocation


  char *input;
  struct stat file;
  fstat(0, &file);
  int fSize = file.st_size;

  if (S_ISREG(file.st_mode)) input = (char*) malloc(sizeof(char*) * fSize);
  else input = (char*) malloc(sizeof(char*) * size);
  if (input == NULL) checkAlloc(input);

  int count = 0; //Counts number of characters in input
  int numWords = 0; //Counts number of words (separated by ' ')
  char c; //Get first character from input

  while (read(0, &c, 1) > 0) { //Continue until reach EOF
    if (count == size) { //Reached allocated size
      size *= 2; //Double size
      val = realloc(val, sizeof(char) * size); //Reallocated with double space
      checkAlloc(val); //Check for successful re-allocation
    }
    val[count++] = c; //Read in character
    if (c == ' ') numWords++; //Increase word count if space in between
    // c = getchar(); //Gets next character before next iteration
  }

  val[count++] = ' '; //Append space for consistency
  numWords++; //Increment numWords

  char **words = malloc(sizeof(char*) * numWords); //Allocate memory

  if (words == NULL) { //Will be null of unable to allocate memory
    fprintf(stderr, "Error allocating memory"); //Error to stderr
    exit(1); //Exit code 1 from assignment specification
  }

  int wordsCount = 0; //Counts words
  words[wordsCount] = val; //words[0] -> val[0]

  int i;
  for (i = 0; i < count; i++) //Iterates through all characters
    if (val[i] == ' ') words[++wordsCount] = &val[i+1]; //val[i] -> new word

  qsort(words, wordsCount, sizeof(char*), frobcmp);

  for (i = 0; i < wordsCount; i++) { //Loops through words
    int j;
    for (j = 0; words[i][j] != ' '; j++) //Loops through characters
      write(1, &words[i][j], 1); //Prints characters
    write(1, " ", 1); //Prints space between words
  }

  putchar('\n'); //Insert line break at end
  fprintf(stderr, "Comparisons: %d\n", comparison);

  return 0;
}
