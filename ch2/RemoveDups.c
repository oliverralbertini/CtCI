/* 2.1 Remove Dups:
 * Write code to remove duplicates from an unsorted linked list.
 *
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed?
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HashTable.h"

struct node_s
{
   int val;
   struct node_s *next;
};

typedef struct node_s node_t;

node_t * allocateNode(void)
{
   node_t *new_node;
   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate memory for new node.\n");
      exit(1);
   }
   return new_node;
}

node_t * insert(node_t *list, int new)
{
   node_t *new_node = allocateNode();
   new_node->val = new;
   new_node->next = list;

   return new_node;
}

/* use a hash table */
node_t * removeDups(node_t *list)
{
   int size = 0;
   node_t *prev = NULL, *curr = NULL, *hold = NULL;
   for (curr = list; curr != NULL; curr = curr->next)
      size++;
   hashtable_t * ht = create(size);
   curr = list;
   while (curr != NULL)
      if (ht_get(ht, curr->val) == 1) {
         if (prev != NULL)
            prev->next = curr->next;
         else
            list = curr->next;
         hold = curr->next;
         free(curr);
         curr = hold;
      }
      else {
         ht_set(ht, curr->val, 1);
         prev = curr;
         curr = curr->next;
      }

   return list;
}

/* have to visit each node roughly once */
node_t *removeDupsSlow(node_t *list)
{
   node_t *front, *back, *hold = NULL, *prev = NULL;
   for (back = list; back != NULL && back->next != NULL; back = back->next) {
      front = back->next;
      prev = back;
      while (front != NULL)
         if (front->val == back->val) {
            prev->next = front->next;
            hold = front->next;
            free(front);
            front = hold;
         }
         else {
            prev = front;
            front = front->next;
         }
   }
   return list;
}

int main(int argc, char *argv[])
{
   int i, N = 1000;
   node_t *first = NULL, *p;
   srand(time(NULL));
   for (i = 0; i < N; ++i)
      first = insert(first, rand() % N);
   // for (p = first; p != NULL; p = p->next)
      // printf("%2d ", p->val);
   // printf("\n");
   first = removeDupsSlow(first);
   // first = removeDups(first);
   // for (p = first; p != NULL; p = p->next)
      // printf("%2d ", p->val);
   return 0;
}
