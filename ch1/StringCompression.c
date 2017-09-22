/* 1.6 String Compression:
 * Implement a method to perform basic string compression using the counts
 * of repeated characters. For example, the string aabcccccaaa would become
 * a2b1c5a3. If the "compressedString" string would not become smaller than the
 * original string, your method should return the original string. You can
 * assume the string has only uppercase and lowercase letters (a-z).
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// important for compressed string to keep track of its size
struct myString
{
   size_t len;
   char * str;
};

struct myString * resize(struct myString *myStrPtr, int factor)
{
   // printf("Updating length to size %d.\n", myStrPtr->len * factor);
   if (!(myStrPtr->str = realloc(myStrPtr->str, myStrPtr->len * factor + 1))) {
      printf("Couldn't get memory to compress string.\n");
      exit(1);
   }
   // printf("strlen = %d. Now size is %d.\n",
   // strlen(myStrPtr->str), myStrPtr->len * factor);
   myStrPtr->len *= factor;
   myStrPtr->str[myStrPtr->len] = '\0';
   return myStrPtr;
}

void insertNumber(struct myString * myStrPtr, char c, int count, int *i)
{
   int count_save = count, length = 1, j;
   while (count_save = count_save / 10)
      length++;
   if (myStrPtr->len - strlen(myStrPtr->str) < length + 1 )
      myStrPtr = resize(myStrPtr, 2);
   myStrPtr->str[(*i)++] = c;
   for (j = *i + length - 1; j >= *i; j--) {
      myStrPtr->str[j] = count % 10 + '0';
      count /= 10;
   }
   *i += length;
   myStrPtr->str[*i] = '\0';
}

char * compress(char * str, struct myString *myStrPtr)
{
   int strl = strlen(str), i = 0, charCount = 1;
   char *p;
   myStrPtr->len = 1;
   myStrPtr = resize(myStrPtr, 2);
   for (p = str + 1; p < str + strl + 1; p++) {
      if (*p == *(p - 1))
         charCount++;
      else {
         insertNumber(myStrPtr, *(p - 1), charCount, &i);
         charCount = 1;
      }
      if (i >= strl)
         return str;
   }
   return myStrPtr->str;
}

int main(int argc, char *argv[])
{
   int i;
   struct myString compressedString = { 1, NULL };
   for (i = 1; i < argc; i++) {
      printf("Here is '%s' compressedString: '%s'\n",
            argv[i], compress(argv[i], &compressedString));;
      free(compressedString.str);
   }

   return 0;
}
