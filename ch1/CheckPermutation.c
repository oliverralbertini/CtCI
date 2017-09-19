/* 1.2 Check Permutation:
 * Given two strings, write a method to decide if one is a permutation of
 * the other.
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define CHAR 128

int main(int argc, char *argv[])
{
   char *str;
   int i, a[CHAR] = { 0 };
   if (strlen(argv[1]) != strlen(argv[2])) {
      printf("`%s' is not a permutation of `%s'!\n", argv[1], argv[2]);
      return 0;
   }
   for (str = argv[1]; *str != '\0'; str++)
      a[*str]++;
   for (str = argv[2]; *str != '\0'; str++) {
      a[*str]--;
      // str2 must have something that str1 doesn't have if str1 and str2
      // are not permutations of eachother
      if (a[*str] < 0) {
         printf("`%s' is not a permutation of `%s'!\n", argv[1], argv[2]);
         return 0;
      }
   }
   printf("`%s' is a permutation of `%s'!\n", argv[1], argv[2]);
   return 0;
}
