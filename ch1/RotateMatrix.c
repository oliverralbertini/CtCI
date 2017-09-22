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
   uint8_t tmp;
   tmp = p->p0;
   p->p0 = p->p2;
   p->p2 = p->p3;
   p->p3 = p->p1;
   p->p1 = tmp;
}

struct index
{
   int i;
   int j;
};

// rotate the whole matrix
void rotateMatrix(struct pixel (*M)[N])
{
   int i, j;
   struct pixel tmp;

   for (i = 0; i < N / 2; i++)
      for (j = i; j < N - i - 1; j++) {
         struct index t = {         i,         j };
         struct index l = { N - j - 1,         i };
         struct index b = { N - i - 1, N - j - 1 };
         struct index r = {         j, N - i - 1 };
         rotatePixel(&M[t.i][t.j]);
         rotatePixel(&M[l.i][l.j]);
         rotatePixel(&M[b.i][b.j]);
         rotatePixel(&M[r.i][r.j]);
         tmp = M[t.i][t.j];
         M[t.i][t.j] = M[l.i][l.j];
         M[l.i][l.j] = M[b.i][b.j];
         M[b.i][b.j] = M[r.i][r.j];
         M[r.i][r.j] = tmp;
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
   rotateMatrix(M);
   printMatrix(M);

   return 0;
}
