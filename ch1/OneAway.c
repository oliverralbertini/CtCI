/* 1.5 One Away:
 * There are three types of edits that can be performed on strings:
 * insert a character, remove a character, or replace a character.
 * Given two strings, write a function to check if they are one edit
 * (or zero edits) away.
 *
 * EXAMPLE
 * pale,  ple  -> true
 * pales, pale -> true
 * pale,  bale -> true
 * pale,  bake -> false
 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

bool compareStrings(char *str1, char *str2)
{
   int strl1 = strlen(str1), strl2 = strlen(str2), edits = 0;

   // p is pointing to longer string
   char *p = str1, *q = str2;
   if (strl1 < strl2) {
      p = str2;
      q = str1;
   }
   // also works like this
   // for ( ; *p != '\0'; p++, q++) {
   for ( ; *p != '\0' && *q != '\0'; p++, q++) {
      if (*p != *q) {
         edits++;
         if (strl1 != strl2)
            q--;
      }
      if (edits > 1)
         return false;
   }
   return true;

}

bool compareLengths(char *str1, char *str2)
{
   int strl1 = strlen(str1), strl2 = strlen(str2);
   if (abs(strl1 - strl2) > 1)
      return false;
   return true;
}

int main(int argc, char *argv[])
{
   if (!compareLengths(argv[1], argv[2])) {
      printf("False\n");
      return 0;
   }
   if (!compareStrings(argv[1], argv[2]))
      printf("False\n");
   else
      printf("True\n");
   return 0;
}

