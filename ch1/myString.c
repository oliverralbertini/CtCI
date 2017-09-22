#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct myString
{
   size_t len;
   char * str;
};

void allocateString(struct myString *my_str_ptr, int size)
{
   // let's allocate some space here
   my_str_ptr->len = size;
   my_str_ptr->str = malloc(size + 1);
   if (my_str_ptr->str == NULL)
      exit(1);
   char *p;
   for (p = my_str_ptr->str; p < my_str_ptr->str + size; p++)
      *p = p - my_str_ptr->str + '0';
}

int main(void)
{
   struct myString myStr;
   allocateString(&myStr, 4);
   printf("Here's your string:%s\n", myStr.str);

   return 0;
}
