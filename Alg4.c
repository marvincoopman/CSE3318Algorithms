// Reads a string for a serialized RB tree, deserializes it,
// performs some insertions, then serializes the revised tree.

/*
Marvin Coopman
1001781933
Lab 4
due 11/30/2021

Create a cost Matrix and order preserving huffman code using dynamic programming

How to run code:
gcc -std=c99 -o Alg4 Alg4.c RB.c RB.h
./Alg.4 < test.dat

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RB.h"

int main()
{
int inputBytes;
char *inputString,*outputString;
char formatString[100];
int insertKeys,i,key;


scanf("%d",&inputBytes);
inputString=(char*) malloc(inputBytes);
if (!inputString) {
  printf("malloc failed %d\n",__LINE__);
  exit(0);
  }
sprintf(formatString,"%%%ds",inputBytes);
scanf(formatString,inputString);
STinit();
STdeserialize(inputString);
free(inputString);
STprintTree();

scanf("%d",&insertKeys);
for (i=0;i<insertKeys;i++) {
  scanf("%d",&key);
  STinsert(key);
  }
  printf("test");
STprintTree();
outputString=STserialize();
printf("%lu %s\n",strlen(outputString)+1,outputString);
free(outputString);
}
