/* 1.3 URLify:
 * Write a method to replace all spaces in a string with '%20'.
 * You may assume that the string has sufficient space at the end to hold
 * the additional characters, and that you are given the "true" length of
 * the string. (Note: If implementing in Java, please use a character array
 * so that you can perform this operation in place.)
 *
 * EXAMPLE:
 * Input:      "Mr John Smith    ", 13
 * Output:     "Mr%20John%20Smith"
 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void replaceSpaces(char * str, int trueLength)
{
   char *p = str;
   int spaceCount = 0;
   for (p = str + trueLength - 1; *p == ' '; p--)
      spaceCount++;
   for ( ; spaceCount > 0; p--)
      if (*p != ' ')
         *(p + spaceCount) = *p;
      else {
         *(p + spaceCount) = '0';
         *(p + spaceCount - 1) = '2';
         *(p + spaceCount - 2) = '%';
         spaceCount -= 2;
      }
}

int main(int argc, char *argv[])
{
   printf("'%s' -> ", argv[1]);
   replaceSpaces(argv[1], strlen(argv[1]));
   printf("'%s'\n", argv[1]);
   return 0;
}
