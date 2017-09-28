#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<math.h>

#define N 30
#define PRIME 31
#define NOT_PRIME 32

int main(void)
{
   int random, i, hashP[PRIME] = { 0 }, hashNP[NOT_PRIME] = { 0 };
   double avgP = N / ((double) PRIME), avgNP = N / ((double) NOT_PRIME), sqrP = 0.0, sqrNP = 0.0;

   srand(time(NULL));
   for (i = 0; i < N; i++) {
      random = rand();
      hashP[random % PRIME]++;
      hashNP[random % NOT_PRIME]++;
   }
   for (i = 0; i < 31; i++) {
      sqrP += hashP[i] * hashP[i];
      sqrNP += hashNP[i] * hashNP[i];
      printf("%d: %d %d: %d\n", PRIME, hashP[i], NOT_PRIME, hashNP[i]);
   }
   sqrNP += hashNP[i] * hashNP[i];

   printf("\n");
   printf("%d: %f %d: %f\n", PRIME, sqrt(sqrP / ((double) PRIME) - avgP * avgP), NOT_PRIME, sqrt(sqrNP / ((double) NOT_PRIME) - avgNP * avgNP));

   return 0;
}
