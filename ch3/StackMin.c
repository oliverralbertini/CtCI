/* 3.2 Stack Min:
 * How would you design a stack which, in addition to push and pop, has a
 * function, min, which returns the minimum displacement?
 * Push, pop and min should all operate in O(1) time.
 */

/* Basically to keep constant push, pop and min, we need some extra storage.
 * This code uses a second stack to keep track of the min 'along the way'.
 * At any given time, popping from this stack gives the min.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_s
{
   int val;
   struct node_s * next;
};

typedef struct node_s node_t;

node_t * allocateNode(void)
{
   node_t * new_node = NULL;

   if(!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate node.\n");
      exit(1);
   }
   return new_node;
}

struct stack_s
{
   int size;
   node_t * stack;
   node_t * min_stack;
};

typedef struct stack_s stack_t;

stack_t * allocateStack(void)
{
   stack_t * new_stack = NULL;

   if(!(new_stack = malloc(sizeof(stack_t)))) {
      printf("Couldn't allocate stack.\n");
      exit(1);
   }
   new_stack->size = 0;
   new_stack->stack = NULL;
   new_stack->min_stack = NULL;
   return new_stack;
}

bool isEmpty(stack_t * s)
{  return s->size == 0;  }

int peek(stack_t *s)
{
   if (isEmpty(s)) {
      printf("Can't peek at an empty stack.\n");
      exit(1);
   }
   return s->stack->val;
}
node_t * delete(node_t * list)
{
   node_t * p = list;

   if (list == NULL) return NULL;
   list = list->next;
   free(p);
   return list;
}

int pop(stack_t *s)
{
   int popped;
   node_t * p = NULL;

   if (isEmpty(s)) {
      printf("Can't peek at an empty stack.\n");
      exit(1);
   }
   popped = s->stack->val;
   s->stack = delete(s->stack);
   s->min_stack = delete(s->min_stack);
   s->size--;

   return popped;
}

node_t * insert(node_t * list, int val)
{
   node_t * new_node = allocateNode();

   new_node->next = list;
   new_node->val = val;
   return new_node;
}

void push(stack_t *s, int val)
{
   if (s->min_stack == NULL || val < s->min_stack->val)
         s->min_stack = insert(s->min_stack, val);
   else
      s->min_stack = insert(s->min_stack, s->min_stack->val);
   s->stack = insert(s->stack, val);
   s->size++;
}

int min(stack_t * s)
{
   if (s->min_stack == NULL) {
      printf("There is no min for an empty stack.\n");
      exit(1);
   }
   return s->min_stack->val;
}
void printStack(stack_t *s)
{
   node_t * p = s->stack;

   while (p != NULL) { printf("%d ", p->val); p = p->next; }
   printf("\n");
   printf("size of stack is %d and min value in stack is %d\n",
         s->size, min(s));
}

int main(int argc, char * argv[])
{
   stack_t * s = allocateStack();

   push(s, 2);
   push(s, 1);
   push(s, 0);
   push(s, -10);
   printf("Peeking at stack: %d\n", peek(s));
   printStack(s);

   return 0;
}
