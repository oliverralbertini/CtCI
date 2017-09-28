/* 2.2 Return Kth to Last:
 * Implement an algorithm to find the kth to last element of a
 * singly-linked list.
 */

#include <stdio.h>
#include <stdlib.h>

struct node_s
{
   int val;
   struct node_s *next;
};

typedef struct node_s node_t;

node_t *allocateNode(void)
{
   node_t *list;
   if (!(list = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate enough for a node.\n");
      exit(1);
   }
   return list;
}

node_t *insert(node_t *list, int val)
{
   node_t *new_node = allocateNode();
   new_node->val = val;
   new_node->next = list;

   return new_node;
}

int findKthHelper(node_t *list, int k, int *answer)
{
   if (list == NULL)
      return 1;
   int distance = findKthHelper(list->next, k, answer);
   if (distance == k)
      *answer = list->val;
   return distance + 1;
}

int findKthToLast(node_t *list, int k)
{
   /* 'default' is the first element of list
    * in case the client enters k too big or 0
    */
   int answer = list->val;
   findKthHelper(list, k, &answer);
   return answer;
}

int findKthRunnerMethod(node_t *list, int k)
{
   node_t *runner = list;
   for (int count = 0; count < k && runner != NULL; count++)
      runner = runner->next;
   if (runner == NULL || runner == list)
      return list->val;
   while (runner != NULL) {
      runner = runner->next;
      list = list->next;
   }
   return list->val;
}

int main(int argc, char *argv[])
{
   int N = 20;
   node_t *first = NULL;
   for (int i = 0; i < N; i++)
      first = insert(first, i);
   for (node_t *curr = first; curr != NULL; curr = curr->next)
      printf("%d ", curr->val);
   printf("\n");
   for (int i = N; i > 0; i--)
      printf("%d ", findKthToLast(first, i));
   printf("\n");
   for (int i = N; i > 0; i--)
      printf("%d ", findKthRunnerMethod(first, i));

   return 0;
}
