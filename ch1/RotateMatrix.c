/* 1.7 Rotate Matrix:
 * Given an image represented by an NxN matrix, where each pixel in the
 * image is 4 bytes, write a method to rotate the image by 90 degrees.
 * Can you do this in place?
 */

#include<stdio.h>
#include<stdint.h>
// only works for even N
#define N 4

struct pixel
{
   uint8_t p0;
   uint8_t p1;
   uint8_t p2;
   uint8_t p3;
};

// rotate pixels 90 degrees clockwise
void rotatePixel(struct pixel *p)
{
   uint8_t tmp0, tmp1, tmp3;
   tmp0 = p->p0;
   p->p0 = p->p2;
   tmp1 = p->p1;
   p->p1 = tmp0;
   tmp3 = p->p3;
   p->p3 = tmp1;
   p->p2 = tmp3;
}

// rotate the whole matrix
void rotateMatrix(struct pixel (*M)[N])
{
   int i, j; //, N = sizeof(M) / sizeof(M[0][0]);
   // printf("This is N*N: %d\n", N);
   struct pixel tmp0, tmp1, tmp3;

   for (i = 0; i < N / 2; i++)
      for (j = i; j < N - i - 1; j++) {
         // in clockwise order
         rotatePixel(&M[i][j]);
         rotatePixel(&M[j][N - i - 1]);
         rotatePixel(&M[N - i - 1][N - j - 1]);
         rotatePixel(&M[N - j - 1][i]);
         tmp0 = M[i][j];
         M[i][j] = M[N - j - 1][i];
         tmp1 = M[j][N - i - 1];
         M[j][N - i - 1] = tmp0;
         tmp3 = M[N - i - 1][N - j - 1];
         M[N - i - 1][N - j - 1] = tmp1;
         M[N - j - 1][i] = tmp3;
      }
}

void printPixelRow(struct pixel *p)
{
   int i;
   for (i = 0; i < N; i++)
      printf("| %2d %2d ", p[i].p0, p[i].p1);
   printf("|\n");
   for (i = 0; i < N; i++)
      printf("| %2d %2d ", p[i].p2, p[i].p3);
   printf("|\n");
   for (i = 0; i < N; i++)
      printf("________");
   printf("_\n");
}

void printMatrix(struct pixel (*M)[N])
{
   int i, j;
   // print by row
   for (i = 0; i < N; i++)
      printf("________");
   printf("_\n");
   for (i = 0; i < N; i++)
      printPixelRow(M[i]);
}

int main(void)
{
   struct pixel M[N][N] = {
               {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}, {12,13,14,15}},
               {{16,17,18,19}, {20,21,22,23}, {24,25,26,27}, {28,29,30,31}},
               {{32,33,34,35}, {36,37,38,39}, {40,41,42,43}, {44,45,46,47}},
               {{48,49,50,51}, {52,53,54,55}, {56,57,58,59}, {60,61,62,63}} };
   // N = 2
   // struct pixel M[N][N] = { {{0,1,2,3}, {4,5,6,7}},
                            // {{8,9,10,11}, {12,13,14,15}} };
   // N = 3
   // struct pixel M[N][N] = { {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}},
                            // {{12,13,14,15}, {16,17,18,19}, {20,21,22,23}},
                            // {{24,25,26,27}, {28,29,30,31}, {32,33,34,35}} };
   printMatrix(M);
   printf("\n");
   rotateMatrix(M);
   printMatrix(M);

   return 0;
}
