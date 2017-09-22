/* 1.9 String Rotation:
 * Assume you have a method isSubstring which checks if one word is
 * a substring of another. Given two strings, s1 and s2, write code to check
 * if s2 is a rotation of s1 using only one call to isSubstring
 * (e.g. "waterbottle" is a rotation of "erbottlewat").
 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

// check if s1 is part of s2
bool isSubstring(char *s1, char *s2)
{
   if (strlen(s1) > strlen(s2))
      return false;
   char *p, *q;
   for ( ; *s2 != '\0'; s2++)
      if (*s1 == *s2)
         for (p = s1, q = s2; *p == *q && *q != '\0'; p++, q++)
            if (*(p + 1) == '\0')
               return true;
   return false;
}

bool isStringRotation(char *s1, char *s2)
{
   if (strlen(s1) != strlen(s2))
      return false;
   char *p, *q, *s2_hold = s2;
   for ( ; *s2 != '\0'; s2++)
      if (*s2 == *s1)
         // q will reach the end first
         for (p = s1, q = s2; *p == *q; p++, q++)
            if (*(q + 1) == '\0')
               return isSubstring(p + 1, s2_hold);
   return false;
}

bool isStringRotationEasy(char *s1, char *s2)
{
   if (strlen(s1) != strlen(s2))
      return false;
   char *s1s1 = malloc(2 * strlen(s1) + 1);
   int i;
   for (i = 0; i < 2 * strlen(s1); ++i)
      s1s1[i] = s1[i % strlen(s1)];
   s1s1[i] = '\0';

   return isSubstring(s2, s1s1);
}

int main(int argc, char *argv[])
{
   if (isStringRotationEasy(argv[1], argv[2]))
      printf("%s is a rotation of %s.\n", argv[1], argv[2]);
   else
      printf("%s is not a rotation of %s.\n", argv[1], argv[2]);
   return 0;
}
