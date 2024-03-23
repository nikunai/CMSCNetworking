#include "helperFunctions.h"

/* Name: concatenateString */
/* Param: cstring, cstring */
/* Desc: takes two cstrings and appends the second onto the first */
void concatenateString(char* inputA, char* inputB){
  int i;
  int j = strlen(inputA);
  for(i = 0; inputB[i] != 0 && inputB[i] != 10; i++){
    inputA[i + j] = inputB[i];
  }
}

/* Name: convert */
/* Param: a md5 hash as a uint8_t */
/* Desc: This covnerts a uint8_T to a cstring */
char* convert(uint8_t *a)
{
  char* buffer2 =  malloc(9);
  buffer2[8] = 0;
  int i;

  if (!buffer2)
    return NULL;

  for (i = 0; i <= 7; i++)
    buffer2[7 - i] = (((*a) >> i) & (0x01)) + '0';
  
  puts(buffer2);
  
  return buffer2;
}
