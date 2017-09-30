/* 2.6 Palindrome:
 * Implement a function to check if a linked list is a palindrome.
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

node_t *allocateNode()
{
   node_t *new_node;
   if (!(new_node = malloc(sizeof(node_t)))) {
      printf("Couldn't allocate a node.\n");
      exit(1);
   }
   return new_node;
}

node_t *insert(node_t *list, int val)
{
   node_t *new_node = allocateNode();

   new_node->next = list;
   new_node->val = val;
   return new_node;
}

/* takes memory to hold backwards copy */
bool isPalindrome(node_t *list)
{
   node_t *p = list, *bw = NULL, *hold;
   int count = 0;

   if (list == NULL) return false; // empty list
   if (list->next == NULL) return true; // one item, it's a palidrome.
   while (p != NULL) {
      bw = insert(bw, p->val);
      p = p->next;
      count++;
   }
   count /= 2;
   while (count > 0) {
      if (list->val != bw->val) return false;
      hold = bw->next;
      free(bw);
      bw = hold;
      list = list->next;
      count--;
   }
   return true;
}

/* recursive method */
int listCount(node_t *list)
{
   int count = 0;
   while (list != NULL) { list = list->next; count++; }
   return count;
}

node_t *isPalindromeRecursiveHelper(node_t *list, node_t *mid, int stop, int i)
{
   if (stop == i) {
      if (list->val == mid->val)
         if (mid->next != NULL) return mid->next;
         else                   return list;
      return NULL;
   }
   mid = isPalindromeRecursiveHelper(list->next, mid, stop, ++i);
   if (mid == NULL || list->val != mid->val) return NULL;
   else if (mid->next != NULL)               return mid->next;
   return list;
}

bool isPalindromeRecursive(node_t *list)
{
   int count = listCount(list), start, stop;
   node_t *p = list;

   stop = count / 2 - 1;
   if ((count % 2) == 0) start = stop + 1;
   else                  start = stop + 2;

   while (start > 0) { p = p->next; start--; }
   if ((isPalindromeRecursiveHelper(list, p, stop, 0) == NULL))
      return false;
   return true;
}


int main(int argc, char *argv[])
{
   node_t *first = NULL;

   first = insert(first, 0);
   first = insert(first, 1);
   if (isPalindromeRecursive(first)) printf("It's a palindrome!\n");
   else                              printf("It's not a palindrome.\n");
   return 0;
}
