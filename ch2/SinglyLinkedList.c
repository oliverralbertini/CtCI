/* Singly-linked List:
 *
 * Has a method to insert a node at the front and one to append to back.
 * Also to insert before or after a specific value in the list, and delete.
 *
 */


#include<stdio.h>
#include<stdlib.h>

struct node
{
   int value;
   struct node *next;
};

struct node * allocateNode(void)
{
   struct node *new_node;
   if (!(new_node = malloc(sizeof(struct node)))) {
      printf("Couldn't allocate memory for new node.\n");
      exit(1);
   }
   return new_node;
}

struct node * insertFront(struct node *list, int new)
{
   struct node *new_node = allocateNode();
   new_node->value = new;
   new_node->next = list;

   return new_node;
}

struct node * appendBack(struct node *list, int new)
{
   struct node *new_node = allocateNode(), *p, *q;
   new_node->value = new;
   new_node->next = NULL;
   for (q = list, p = NULL; q != NULL; p = q, q = q->next)
      ;
   if (p == NULL) // special case of empty list
      list = new_node;
   else
      p->next = new_node;

   return list;
}

// with this method, only insert if beforeThis is found
struct node * insertBefore(struct node *list, int beforeThis, int new)
{
   struct node *new_node = allocateNode(), *p, *q;
   new_node->value = new;
   p = NULL, q = list;
   while (q != NULL && q->value != beforeThis)
      p = q, q = q->next;
   if (q != NULL) {
      new_node->next = q;
      if (p == NULL)
         list = new_node;
      else
         p->next = new_node;
   }
   else
      free(new_node);

   return list;
}

// with this method, only insert if afterThis is found
struct node * insertAfter(struct node *list, int afterThis, int new)
{
   struct node *new_node = allocateNode(), *p;
   new_node->value = new;
   p = list;
   while (p != NULL && p->value != afterThis)
      p = p->next;
   if (p != NULL) {
         new_node->next = p->next;
         p->next = new_node;
   }
   else
      free(new_node);

   return list;
}

struct node * delete(struct node *list, int deleteThis)
{
   struct node *q = list, *p = NULL;
   while (q != NULL && q->value != deleteThis)
      p = q, q = q->next;
   if (q != NULL)
      if (p != NULL)
         p->next = q->next;
      else //special case of deleting the first element
         list = q->next;
   free(q);

   return list;
}

int main(int argc, char *argv[])
{
   int i;
   struct node *first = NULL, *p;
   for (i = 0; i < 4; ++i) {
      // first = insertFront(first, i);
      first = appendBack(first, i);
   }
   first = insertBefore(first, 2, 10);
   first = insertAfter(first, 0, 11);
   first = delete(first, 41);
   for (p = first; p != NULL; p = p->next)
      printf("%d ", p->value);
   return 0;
}
