/* “The median of an array is the value in the middle if the array was sorted;
 * if the array has an odd number of items n, the median is the (n+1)/2’th
 * largest item in the array (which is also the (n+1)/2’th smallest item in
 * the array), and if the array has an even number of items n, the median is
 * the arithmetic average of the n/2’th smallest item in the array and the
 * n/2’th largest item in the array. For instance, the median of the array
 * [2,4,5,7,3,6,1] is 4 and the median of the array [5,2,1,6,3,4] is 3.5.
 *
 * Your task is to write a program that takes an array of 8-bit integers
 * (possibly but not necessarily in sort) and finds the median value in
 * the array; you should find an algorithm that takes linear time and
 * constant space.”
 */

#include<stdio.h>
#include<math.h>
#include<limits.h>
#define BITS 8

void swap(__uint8_t *a, int i, int j)
{
   int hld = a[i];
   a[i] = a[j];
   a[j] = hld;
}

void radix_sort(__uint8_t *a, int bit, int start, int end)
{
   if (bit < 0) return;
   int s = start, e = end;
   while (s != e)
      if (a[s] & (1 << bit))
         swap(a, s, --e);
      else
         s++;
   bit--;
   radix_sort(a, bit, start, e);
   radix_sort(a, bit, s, end);
}

int main(int argc, char *argv[])
{
   int i, N = argc - 1;
   __uint8_t a[N];
   for (i = 1; i <= N; i++)
      sscanf(argv[i], "%d", &a[i - 1]);

   // unsigned 8 bit integers only
   printf("Your not necessarily sorted array:\n");
   for (i = 0; i < N; i++)
      printf("%d ", a[i]);
   printf("\n\n");

   radix_sort(a, BITS - 1, 0, N);

   printf("Your array, now sorted:\n");
   for (i = 0; i < N; i++)
      printf("%d ", a[i]);
   printf("\n\n");
   printf("Median value:\n");
   if (N % 2 == 1)
      printf("%d", a[N / 2]);
   else
      printf("%f", (a[N / 2 - 1] + a[N / 2]) / 2.0);

   return 0;
}
