/* 2.7 Intersection:
 * Given two (singly) linked lists, determine if the two lists intersect.
 * Return the intersecting node. Note that the intersection is defined based
 * on reference, not value. That is, if the kth node of the first linked list
 * is the exact same node (by reference) as the jth node of the second
 * linked list, then they are intersecting.
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

   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate space for a node.\n");
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

/* if two linked lists intersect, then they share the last node, since
 * each node only has one 'next' node */
node_t * listsIntersection(node_t * l1, node_t * l2)
{
   node_t * p1 = l1, * p2 = l2, * Short, * Long;
   int c1 = 0, c2 = 0, diff;

   while (p1->next != NULL) { p1 = p1->next; c1++; }
   while (p2->next != NULL) { p2 = p2->next; c2++; }
   if (p1 != p2) return NULL;
   if (c1 > c2) { Long = l1, Short = l2; diff = c1 - c2; }
   else         { Long = l2, Short = l1; diff = c2 - c1; }
   for (int i = 0; i < diff; i++)
      Long = Long->next;
   while (Long != NULL && Short != NULL) {
      if (Long == Short)
         return Long;
      Long = Long->next;
      Short = Short->next;
   }
}

/* recursive method, will search 'from the back' */
node_t * listsIntersectionRecursiveHelper(node_t * l1, node_t * l2)
{
   node_t * intersection = NULL;

   if (l1 == NULL) return NULL;
   intersection = listsIntersectionRecursiveHelper(l1->next, l2->next);
   if (l1 == l2) return l1;
   return intersection;
}

node_t * listsIntersectionRecursive(node_t * l1, node_t *l2)
{
   node_t * p1 = l1, * p2 = l2, * Short, * Long;
   int c1 = 0, c2 = 0, diff;

   while (p1->next != NULL) { p1 = p1->next; c1++; }
   while (p2->next != NULL) { p2 = p2->next; c2++; }
   if (p1 != p2) return NULL;
   if (c1 > c2) { Long = l1, Short = l2; diff = c1 - c2; }
   else         { Long = l2, Short = l1; diff = c2 - c1; }
   for (int i = 0; i < diff; i++)
      Long = Long->next;
   return listsIntersectionRecursiveHelper(Long, Short);
}

void printList(node_t *list)
{
   if (list == NULL) { printf("list is null\n"); return; }
   while (list != NULL) {
      printf("%d ", list->val);
      list = list->next;
   }
   printf("\n");
}

int main(int argc, char *argv[])
{
   node_t * first = NULL, * other_list = NULL;

   first = insert(first, 7);
   first = insert(first, 6);
   first = insert(first, 5);
   // other_list = insert(other_list, 8);
   other_list = first;
   other_list = insert(other_list, 88);
   other_list = insert(other_list, 89);
   first = insert(first, 4);
   first = insert(first, 3);

   printList(first);
   printList(other_list);

   printList(listsIntersectionRecursive(first, other_list));
   printList(listsIntersection(first, other_list));
   return 0;
}
