/*
 * Implement a simple hash table for integers.
 * See https://gist.github.com/tonious/1377667
 */

#include "HashTable.h"

hashtable_t *create(int size)
{
   if (size < 1)
      return NULL;
   int i;
   hashtable_t *hashtable = NULL;
   // allocate hashtable
   if (!(hashtable = malloc(sizeof(hashtable_t))))
      return NULL;
   // allocate the actual table
   if (!(hashtable->table = malloc(sizeof(entry_t *) * size)))
      return NULL;

   for (i = 0; i < size; i++)
      hashtable->table[i] = NULL;
   hashtable->size = size;

   return hashtable;
}

// find the hash
int hash(hashtable_t *hashtable, int key)
{
   return key % hashtable->size;
}

// create a key-value pair
entry_t *ht_newpair(int key, int val)
{
   entry_t *newpair;
   if (!(newpair = malloc(sizeof(entry_t))))
      return NULL;
   newpair->next = NULL;
   newpair->key = key;
   newpair->val = val;

   return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set(hashtable_t *hashtable, int key, int val)
{
   int bin = 0;
   // this will be our new one
   entry_t *newpair = NULL;
   // these are for traversing the list
   entry_t *next = NULL;
   entry_t *last = NULL;

   bin = hash(hashtable, key);

   next = hashtable->table[bin];
   while (next != NULL && key > next->key) {
      last = next;
      next = next->next;
   }

   if (next != NULL && key == next->key)
      next->val = val;
   else {
      newpair = ht_newpair(key, val);
      // we're at the start of the list
      if (last == NULL) {
         newpair->next = hashtable->table[bin];
         hashtable->table[bin] = newpair;
      }
      else if (next == NULL)
         last->next = newpair;
      else {
         newpair->next = next;
         last->next = newpair;
      }
   }
}

// find and retrieve an element from the hash table
int ht_get(hashtable_t *hashtable, int key)
{
   int bin = hash(hashtable, key);
   entry_t *finder = hashtable->table[bin];

   while (finder != NULL && finder->key != key)
      finder = finder->next;
   if (finder == NULL)
      return -1;
   else
      return finder->val;
}

// print table also evaluate C = (m/n-1)*(sum<x*x>/n - 1)
void print_ht(hashtable_t *hashtable)
{
   int i, n = 0, m = hashtable->size, count = 0, squares = 0;
   for (i = 0; i < m; i++) {
      entry_t *curr = hashtable->table[i];
      if (curr == NULL)
         printf("bin %d is empty.", i);
      while (curr != NULL) {
         printf("%d %d -- ", curr->key, curr->val);
         curr = curr->next;
         count++;
      }
      squares += count * count;
      n += count;
      printf("count = %d\n", count);
      count = 0;
   }
   double a = ((double) n) / hashtable->size;
   printf("m = %d n = %d\nC = %f\n", m, n, ((double) m / (n - 1.0)) * ((double) squares / n - 1.0));
}

/*
int main(int argc, char *argv[])
{

   int i, N = 200, M = 200;
   hashtable_t *ht = create(M);
   srand(time(NULL));
   for (i = 0; i < N; i++)
      ht_set(ht, rand(), rand());
   // for (i = 0; i < N; i++)
      // printf("%d ", ht_get(ht, i));
   printf("\n");
   print_ht(ht);
   return 0;
}
*/
