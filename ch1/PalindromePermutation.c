/* 1.4 Palindrome Permutation:
 *
 * Given a string, write a function to check if it is a permutation of a
 * palindrome. A palindrome is a word or phrase that is the same forwards
 * and backwards. A permutation is a rearrangement of letters. The
 * palindrome does not need to be limited to just dictionary words.
 *
 * EXAMPLE
 * Input:    Tact Coa
 * Output:   True (permutations: "taco cat", "atco cta", etc.)
 *
 * So ignore spaces and caps?
 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int charToInt(char c)
{
   if (c >= 'A' && c <= 'Z')
      return c - 'A';
   if (c >= 'a' && c <= 'z')
      return c - 'a';
   return -1;
}

bool isPalindromePermutation(char *str)
{
   char *p;
   int i, a[26] = { 0 }, odd_count = 0;
   for (p = str; *p != '\0'; p++) {
      i = charToInt(*p);
      if (i > 0) {
         a[i]++;
         if (a[i] % 2 == 1)
            odd_count++;
         else
            odd_count--;
      }
   }
   return odd_count <= 1;
}

int main(int argc, char *argv[])
{
   char **p;
   for (p = &argv[1]; p < &argv[1] + argc - 1; p++)
      if (isPalindromePermutation(*p))
         printf("%s is a palindrome permutation.\n", *p);
      else
         printf("%s is not a palindrome permutation.\n", *p);
   return 0;
}
