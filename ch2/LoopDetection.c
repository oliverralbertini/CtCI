/* 2.8 Loop Detection:
 * Given a circular linked list, implement an algorithm that returns the node
 * at the beginning of the loop.
 * DEFINITION
 * Circular linked list: A (corrupt) linked list in which a node's next pointer
 * points to an earlier node, so as to make a loop in the linked list.
 * EXAMPLE
 * Input:    A -> B -> C -> D -> E -> C [the same C as earlier]
 * Output:   C
 */

#include <stdio.h>
#include <stdlib.h>

struct node_s
{
   int val;
   struct node_s * next;
};

typedef struct node_s node_t;

node_t * allocateNode(void)
{
   node_t * new_node = NULL;

   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate space for node.\n");
      exit(1);
   }
   return new_node;
}

node_t * insert(node_t * list, int val)
{
   node_t * new_node = allocateNode();

   new_node->val = val;
   new_node->next = list;
   return new_node;
}

/* This will find the corrupt node before the slow
 * pointer leaves the loop of corruption */
node_t * corruptNode(node_t * list)
{
   node_t * fast = list, * slow = list;

   while (fast != NULL && fast->next != NULL) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) break;
   }

   // no corruption here
   if (fast == NULL || fast->next == NULL) return NULL;

   while (list != slow) {
      slow = slow->next;
      list = list->next;
   }
   return slow;
}

int main(int argc, char *argv[])
{
   node_t * first = NULL, * hold = NULL, * corrupt = NULL;

   first = insert(first, 10);
   hold = first;
   first = insert(first, 9);
   first = insert(first, 8);
   first = insert(first, 7);
   first = insert(first, 6);
   first = insert(first, 5);
   hold->next = first;
   first = insert(first, 4);
   first = insert(first, 3);
   first = insert(first, 2);
   first = insert(first, 1);

   if ((corrupt = corruptNode(first)) == NULL)
      printf("No corruption here.\n");
   else
      printf("%d ", corruptNode(first)->val);
   return 0;
}
