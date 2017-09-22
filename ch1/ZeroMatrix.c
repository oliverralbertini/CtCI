/* 1.8 Zero Matrix:
 * Write an algorithm such that if an element in an MxN matrix is 0,
 * its entire row and column are set to 0.
 */

#include<stdio.h>
#include<stdlib.h>

struct zeroElements
{
   int *zeroRows;
   int *zeroCols;
};

struct Matrix
{
   int row;
   int col;
   int **m;
};

void printData(struct Matrix *m)
{
   int *i, j;
   for (j = 0; j < m->row; j++) {
      for (i = m->m[j]; i < m->m[j] + m->col; i++)
         printf("%2d", *i);
      printf("\n");
   }
   printf("\n");
}

void initializeData(struct Matrix *m)
{
   int *i, j;
   for (j = 0; j < m->row; j++)
      for (i = m->m[j]; i < m->m[j] + m->col; i++)
         *i = 1;
}

void clearCol(struct Matrix *m, int c)
{
   int **j, rows = m->row;
   for (j = &m->m[0]; j < &m->m[rows]; j++)
      (*j)[c] = 0;
}

void clearRow(struct Matrix *m, int r)
{
   int *i, cols = m->col;
   for (i = m->m[r]; i < m->m[r] + cols; i++)
      *i = 0;
}

void clearElement(struct Matrix *m, int r, int c)
{
   m->m[r][c] = 0;
}

void clearColRow(struct Matrix *m, int r, int c)
{
   int *i, cols = m->col, rows = m->row, **j;
   for (i = m->m[r]; i < m->m[r] + cols; i++)
      *i = 0;
   for (j = &m->m[0]; j < &m->m[rows]; j++)
      (*j)[c] = 0;
}

void findZeros(struct Matrix *m, struct zeroElements *zeros)
{
   int i, j;
   for (i = 0; i < m->row; i++)
      zeros->zeroRows[i] = 0;
   for (j = 0; j < m->col; j++)
      zeros->zeroCols[j] = 0;
   for (i = 0; i < m->row; i++)
      for (j = 0; j < m->col; j++)
         if (m->m[i][j] == 0) {
            zeros->zeroRows[i]++;
            zeros->zeroCols[j]++;
         }
}

void allocateZeroElements(struct Matrix *m, struct zeroElements *zeros)
{
   if (!(zeros->zeroRows = malloc(sizeof(int) * m->row)) ||
       !(zeros->zeroCols = malloc(sizeof(int) * m->col))) {
      printf("Couldn't allocate space for zeroElements array.\n");
      exit(1);
   }
}

void allocateMatrix(struct Matrix *m)
{
   if (!(m->m = malloc(sizeof(int *) * m->row))) {
      printf("Not enough memory for an array of pointers.\n");
      exit(1);
   }
   int i;
   for (i = 0; i < m->row; i++)
      if (!(m->m[i] = malloc(sizeof(int) * m->col))) {
         printf("Not enough memory for %dth array of integers.\n", i);
         exit(1);
      }
}

void freeZeroElements(struct zeroElements *zeros)
{
   int i;
   free(zeros->zeroRows);
   free(zeros->zeroCols);
}
void freeMatrix(struct Matrix *m)
{
   int i;
   for (i = 0; i < m->row; i++)
      free(m->m[i]);
   free(m->m);
}

int main (int argc, char * argv[])
{
   struct Matrix m = { atoi(argv[1]), atoi(argv[2]), NULL };
   allocateMatrix(&m);
   struct zeroElements zeros = { NULL, NULL };
   allocateZeroElements(&m, &zeros);
   initializeData(&m);
   printData(&m);
   clearElement(&m, 2, 2);
   clearElement(&m, 12, 12);
   clearElement(&m, 8, 8);
   findZeros(&m, &zeros);
   int i;
   for (i = 0; i < m.row; i++)
      if (zeros.zeroRows[i])
         clearRow(&m, i);
   for (i = 0; i < m.col; i++)
      if (zeros.zeroCols[i])
         clearCol(&m, i);
   printData(&m);
   freeMatrix(&m);
   freeZeroElements(&zeros);
   return 0;
}
