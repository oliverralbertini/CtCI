/* 2.4 Partition:
 * Write code to partition a linked list around a value x, such that all
 * nodes less than x come before all nodes greater than or equal to x.
 * If x is contained within the list, the values of x only need to be after
 * the elements less than x (see below).
 *
 * EXAMPLE
 * Input:   3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
 * Output:  3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
 */

#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <time.h> /* for seeding pseudorandom number generator */

struct node_s
{
   int val;
   struct node_s *next;
};

typedef struct node_s node_t;

node_t *allocateNode(void)
{
   node_t *new_node;

   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate node.\n");
      exit(1);
   }
}

node_t *insert(node_t *list, int val)
{
   node_t *new_node = allocateNode();

   new_node->val = val;
   new_node->next = list;
   return new_node;
}

/* return the node after the one we are deleting */
node_t *delete(node_t *curr, node_t *prev)
{
   if (curr == NULL) return NULL;
   /* we are deleting first one */
   if (prev == NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
      return curr;
   }
   /* we are deleting somewhere in the list */
   prev->next = curr->next;
   free(curr);
   return prev->next;
}

node_t *mvFront(node_t *curr, node_t *prev, node_t *list)
{
   list = insert(list, curr->val);
   delete(curr, prev);
   return list;
}

node_t *partition(node_t *list, int part)
{
   node_t *prev = list, *curr = list->next, *tmp = NULL;

   if (list == NULL) return NULL;
   while (curr != NULL) {
      if (curr->val < part) {
         tmp = curr->next;
         list = mvFront(curr, prev, list);
         curr = tmp;
      }
      else {
         prev = curr;
         curr = curr->next;
      }
   }
   return list;
}

void printList(node_t *list)
{
   while (list != NULL) {
      printf("%2d ", list->val);
      list = list->next;
   }
   printf("\n");
}

int main(int argc, char *argv[])
{
   node_t *first;
   int N = 32, part = N / 2;

   srand(time(NULL));
   for (int i = 0; i < N; i++)
      first = insert(first, rand() % N);
   printList(first);
   printf("Partition: %d\n", part);
   first = partition(first, part);
   printList(first);
   return 0;
}
