#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

  //tr will take 3 arguments with the ./tr.out as the first argument
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of arguments entered\n");
    exit(1);
  }

  //./tr.out is argv[0]
  char *string1 = argv[1];
  char *string2 = argv[2];

  //length of string1 and string2 not equivalent
  if (strlen(string1) != strlen(string2)) {
    fprintf(stderr, "Arguments' lengths do not match\n");
    exit(1);
  }

  //values of string1 and string2 are equivlent
  if (strcmp(string1, string2) == 0) {
    fprintf(stderr, "Arguments are equivalent\n");
    exit(1);
  }

  int i, j;

  //checks through first argument searching for duplicates
  for (i = 0; i < strlen(string1); i++)
    for (j = i + 1; j < strlen(string1); j++) {
      if (string1[i] == string1[j]) {
        fprintf(stderr, "First argument cannot have a duplicate\n");
        exit(1);
      }
    }

  int bool = 0;
  char c[1]; //gets first character
  while (read(0, c, 1) > 0) { //continues until reach end of file
    bool = 0;
    for (i = 0; i < strlen(string1); i++) {
      if (c[0] == string1[i]) { //checks if current char is in string1
        write(1, &string2[i], 1); //if in string1, print corresponding string2 value
        bool = 1;
        break; //no need to stay in for loop
      }
    }
    if (bool == 0) write(1, &c, 1);
  }
  return 0;
}
