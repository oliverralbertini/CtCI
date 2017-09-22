/* 1.9 String Rotation:
 * Assume you have a method isSubstring which checks if one word is
 * a substring of another. Given two strings, s1 and s2, write code to check
 * if s2 is a rotation of s1 using only one call to isSubstring
 * (e.g. "waterbottle" is a rotation of "erbottlewat").
 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

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
int main(int argc, char *argv[])
{
   printf("%d\n", isStringRotation("waterbottle", "erbottlewat"));
   return 0;
}
