/* 2.5 Sum Lists:
 * You have two numbers represented by a linked list, where each node
 * contains a single digit. The digits are stored in reverse order, such
 * that the 1's digit is at the head of the list. Write a function that
 * adds the two numbers and returns the sum as a linked list.
 *
 * EXAMPLE
 *
 * Input:  (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295.
 * Output:  2 -> 1 -> 9. That is, 912.
 *
 * FOLLOW UP
 *
 * Suppose the digits are stored in forward order. Repeat the above
 * problem.
 *
 * EXAMPLE
 *
 * Input:  (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
 * Output:  9 -> 1 -> 2. That is, 912.
 */

#include <stdio.h>
#include <stdlib.h>

struct node_s
{
   int val;
   struct node_s *next;
};

typedef struct node_s node_t;

node_t * allocateNode()
{
   node_t *new_node = NULL;

   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate space for node.\n");
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

/* this method gives you a pointer to the new node */
node_t *append(node_t *list, int val)
{
   node_t *new_node = allocateNode();

   new_node->val = val;
   new_node->next = NULL;

   if (list == NULL)
      return new_node;
   list->next = new_node;
   return new_node;
}

node_t *addLists(node_t *list1, node_t *list2)
{
   node_t *sum = NULL, *answer = NULL;
   int tens;

   sum = append(sum, 0);
   answer = sum;
   while (list1 != NULL || list2 != NULL) {
      int s = sum->val;
      if (list1 != NULL) s += list1->val, list1 = list1->next;
      if (list2 != NULL) s += list2->val, list2 = list2->next;
      sum->val = s % 10;
      tens = s / 10;
      if (list1 != NULL || list2 != NULL || tens > 0)
         sum = append(sum, tens);
   }
   return answer;
}

/* Recursive way */
node_t *sumListsHelper(node_t *list1, node_t *list2, node_t *sum, int s)
{
   if (list1 == NULL && list2 == NULL) return NULL;
   if (list1 != NULL) s += list1->val, list1 = list1->next;
   if (list2 != NULL) s += list2->val, list2 = list2->next;
   sum = append(sum, s % 10);
   sumListsHelper(list1, list2, sum, s / 10);
   return sum;
}

node_t *sumLists(node_t *list1, node_t *list2)
{
   node_t *sum = NULL;

   sum = sumListsHelper(list1, list2, sum, 0);
   return sum;
}

/* for 1's place at the end of list */
node_t *sumListsBackwardsHelper(node_t *list1, node_t *list2)
{
   node_t *sum = NULL;
   int s;

   if (list1->next == NULL && list2->next == NULL) {
      sum = insert(NULL, (list1->val + list2->val) % 10);
      return insert(sum, (list1->val + list2->val) / 10);
   }
   sum = sumListsBackwardsHelper(list1->next, list2->next);
   s = sum->val + list1->val + list2->val;
   sum->val = s % 10;
   return insert(sum, s / 10);
}

node_t *sumListsBackwards(node_t *list1, node_t *list2)
{
   node_t *hold1 = list1, *hold2 = list2, *shortlist, *longlist, *hold, *sum;

   while (list1 != NULL && list2 != NULL)
      list1 = list1->next, list2 = list2->next;
   if (list1 == NULL && list2 == NULL)
      sum = sumListsBackwardsHelper(hold1, hold2);
   else {
      if (list1 != NULL) longlist = list1, hold = hold1, shortlist = hold2;
      else longlist = list2, hold = hold2, shortlist = hold1;
      while (longlist != NULL)
         shortlist = insert(shortlist, 0), longlist = longlist->next;
      sum = sumListsBackwardsHelper(shortlist, hold);
   }
   if (sum->val > 0) return sum;
   return sum->next;
}

void printList(node_t *list)
{
   while (list != NULL) {
      printf("%d ", list->val);
      list = list->next;
   }
   printf("\n");
}

int main(int argc, char *argv[])
{
   node_t *list1 = NULL, *list2 = NULL, *sum = NULL;

   list1 = insert(list1, 7);
   list1 = insert(list1, 1);
   list1 = insert(list1, 6);

   list2 = insert(list2, 5);
   list2 = insert(list2, 9);
   list2 = insert(list2, 2);

   printList(list1);
   printList(list2);
   // sum = addLists(list1, list2);
   // sum = sumLists(list1, list2);
   sum = sumListsBackwards(list1, list2);
   printList(sum);

   return 0;
}
