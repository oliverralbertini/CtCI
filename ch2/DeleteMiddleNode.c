/* 2.3 Delete Middle Node:
 * Implement an algorithm to delete a node in the middle of a singly-linked
 * list, given only access to that node.
 *
 * EXAMPLE
 * Input: the node c from the linked list a->b->c->d->e
 * Result: nothing is returned, but the new linked list looks like a->b->d->e
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
      printf("Couldn't allocate node storage.\n");
      exit(1);
   }
   return new_node;
}

node_t *insert(node_t *list, int val)
{
   node_t *new_node = allocateNode();

   new_node->val = val;
   new_node->next = list;
   return new_node;
}

bool deleteMiddleNode(node_t *m)
{
   node_t *tmp = m;

   if (m == NULL) return false;
   if (m->next == NULL) return false;
   tmp = m->next;
   m->val = m->next->val;
   m->next = m->next->next;
   free(tmp);
   return true;
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
   int N = 24, i;
   node_t *first = NULL, *p;

   for (int i = 0; i < N; i++)
      first = insert(first, i);
   printList(first);
   for (p = first, i = 0; i < N - N / 2; p = p->next, i++)
      ;
   deleteMiddleNode(p);
   printList(first);
   return 0;
}
