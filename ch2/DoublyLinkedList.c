/* Doubly-linked List:
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
   struct node *prev;
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
   new_node->prev = NULL;
   if (list != NULL)
      list->prev = new_node;

   return new_node;
}

struct node * appendBack(struct node *list, int new)
{
   struct node *new_node = allocateNode(), *p;
   new_node->value = new;
   new_node->next = NULL;
   for (p = list; p != NULL; p = p->next)
      if (p->next == NULL)
         break;
   if (p == NULL) {// special case of empty list
      list = new_node;
      list->prev = NULL;
   }
   else {
      p->next = new_node;
      new_node->prev = p;
   }

   return list;
}

// with this method, only insert if beforeThis is found
struct node * insertBefore(struct node *list, int beforeThis, int new)
{
   struct node *new_node = allocateNode(), *p;
   new_node->value = new;
   p = list;
   while (p != NULL && p->value != beforeThis) {
      if (p->next == NULL)
         break;
      p = p->next;
   }
   if (p->value == beforeThis) {
      new_node->next = p;
      new_node->prev = p->prev;
      if (p->prev == NULL)
         list = new_node;
      else
         p->prev->next = new_node;
      p->prev = new_node;
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
      new_node->prev = p;
      if (p->next != NULL)
         p->next->prev = new_node;
      p->next = new_node;
   }
   else
      free(new_node);

   return list;
}

struct node * delete(struct node *list, int deleteThis)
{
   struct node *p = list;
   while (p != NULL && p->value != deleteThis)
      p = p->next;
   if (p != NULL) {
      if (p->prev != NULL) {
         p->prev->next = p->next;
         printf("%d\n", p->prev->value);
      }
      else // special case of deleting the first element
         list = p->next;
      if (p->next != NULL)
         p->next->prev = p->prev;
   }
   free(p);

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
   // first = insertBefore(first, 2, 10);
   first = insertAfter(first, 2, 11);
   first = delete(first, 3);
   for (p = first; p != NULL; p = p->next)
      printf("%d ", p->value);
   // for (; p != NULL; p = p->prev)
      // printf("%d ", p->value);
   return 0;
}
