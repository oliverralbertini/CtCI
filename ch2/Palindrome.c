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
   node_t *fast = list, *bw = NULL, *hold;
   int count = 0;

   if (list == NULL) return false; // empty list
   if (list->next == NULL) return true; // one item, it's a trivial palindrome
   /* move fast twice as fast as list. when fast reaches the end,
    * list will be at the middle */
   while (fast != NULL && fast->next != NULL) {
      bw = insert(bw, list->val);
      list = list->next;
      fast = fast->next->next;
      count++;
   }
   // odd case
   if (fast != NULL) list = list->next;
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

   while (list != NULL && list->next != NULL) {
      list = list->next->next;
      count++;
   }
   /* even case */
   if (list == NULL)
      return count * 2;
   /* odd case */
   return count * 2 + 1;
}

/* instead of class with bool/node, return NULL if not palindrome
 * otherwise return a valid node */
node_t *isPalindromeRecursiveHelper(node_t *list, int length)
{
   node_t *compare;

   if (length <= 1) {
      if (length == 1) return list->next;
      return list;
   }
   compare = isPalindromeRecursiveHelper(list->next, length - 2);
   if (compare == NULL || list->val != compare->val)
      return NULL;
   else if (compare->next != NULL)
      return compare->next;
   /* if it's a palindrome, make sure to not return NULL */
   return list;
}

bool isPalindromeRecursive(node_t *list)
{
   int length = listCount(list);

   if ((isPalindromeRecursiveHelper(list, length) == NULL))
      return false;
   return true;
}

void printList(node_t *list)
{
   while (list != NULL) { printf("%d ", list->val); list = list->next; }
   printf("\n");
}

int main(int argc, char *argv[])
{
   node_t *first = NULL;

   first = insert(first, 0);
   first = insert(first, 1);
   first = insert(first, 1);
   first = insert(first, 0);

   printList(first);

   if (isPalindrome(first)) printf("It's a palindrome!\n");
   else                     printf("It's not a palindrome.\n");

   if (isPalindromeRecursive(first)) printf("It's a palindrome!\n");
   else                              printf("It's not a palindrome.\n");
   return 0;
}
