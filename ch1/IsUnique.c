/* 1.1
 * Is Unique: Implement an algorithm to determine if a string has all unique
 * characters. What if you cannot use additional data structures?
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define CHARS 128

static int check_str(char *str) {
   int N, a[CHARS] = { 0 };
   N = strlen(str);
   for (; *str != '\0'; str++)
      if (a[(int) *str]++ > 0)
         return 1;
   return 0;
}

int main(int argc, char *argv[])
{
   int i;
   for (i = 1; i < argc; i++)
      if (check_str(argv[i]))
         printf("%s is not unique.\n", argv[i]);
      else
         printf("%s is unique.\n", argv[i]);
   return 0;
}
