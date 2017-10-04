/* 3.1 Three in One:
 * Describe how you could use a single array to implement three stacks.
 */

/* To store two stacks in an array, I would just grow from each edge.
 * For three stacks, this would require shifting around, otherwise, rigid
 * boundaries for the stacks. The most flexible would be to push onto a stack
 * as needed, and keep track of starting point and length for each stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_SIZE 4

struct multiStack_s
{
   int * data; // array holding all data in the stacks
   int N; // length of the data array
   int numStack; // number of stacks in data array
   int * lengths; // array holding the lengths of each stack
};

typedef struct multiStack_s multiStack_t;

multiStack_t * allocateMultiStack(int numStack)
{
   multiStack_t * ms = malloc(sizeof(multiStack_t));

   ms->N = DEFAULT_SIZE * numStack;
   ms->numStack = numStack;
   ms->data = malloc(sizeof(int) * ms->N);
   ms->lengths = malloc(sizeof(int) * ms->numStack);
   for (int i = 0; i < numStack; i++) ms->lengths[i] = 0;

   return ms;
}

int lengthThroughHere(multiStack_t * ms, int stack)
{
   int totalLength = 0;

   for (int i = 0; i < stack + 1; i++)
      totalLength += ms->lengths[i];
   return totalLength;
}

void growMultiStack(multiStack_t * ms)
{
   int * p = ms->data;

   ms->data = malloc(sizeof(int) * ms->N * 2);
   for (int i = 0; i < ms->N; i++)
      ms->data[i] = p[i];
   free(p);
   ms->N *= 2;
}

void push(multiStack_t * ms, int stack, int val)
{
   int toPush = lengthThroughHere(ms, stack),
       end = lengthThroughHere(ms, ms->numStack);

   if (end == ms->N)
      growMultiStack(ms);

   for (int i = end - 2; i > toPush; i--)
      ms->data[i + 1] = ms->data[i];
   ms->data[toPush] = val;
   ms->lengths[stack]++;
}

int pop(multiStack_t * ms, int stack)
{
   int toPop = lengthThroughHere(ms, stack) - 1, popped = ms->data[toPop],
       end = lengthThroughHere(ms, ms->numStack);

   for (int i = toPop; i < end; i++)
      ms->data[i] = ms->data[i + 1];
   ms->lengths[stack]--;

   return popped;
}

bool isEmpty(multiStack_t * ms, int stack)
{
   return ms->lengths[stack] == 0;
}

int peek(multiStack_t * ms, int stack)
{
   if (ms->lengths[stack] == 0) printf("Stack # %d is empty.\n", stack + 1);
   return ms->data[lengthThroughHere(ms, stack) - 1];
}

void printMultiStack(multiStack_t * ms)
{
   for (int i = 0; i < ms->N; i++)
      printf("%d ", ms->data[i]);
   printf("\n");
}
int main(int argc, char *argv[])
{
   multiStack_t * ms = allocateMultiStack(3);

   push(ms, 0, 1);
   push(ms, 0, 2);
   push(ms, 0, 3);
   push(ms, 0, 4);
   push(ms, 1, 1);
   push(ms, 1, 2);
   push(ms, 1, 3);
   push(ms, 1, 4);
   push(ms, 2, 1);
   push(ms, 2, 2);
   push(ms, 2, 3);
   push(ms, 2, 4);
   push(ms, 2, 5);
   printMultiStack(ms);
   printf("%d\n", peek(ms, 2));
   printMultiStack(ms);
   return 0;
}
