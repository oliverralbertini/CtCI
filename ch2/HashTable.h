#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct entry_s
{
   int key;
   int val;
   struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s
{
   int size;
   struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;

hashtable_t *create(int size);

int hash(hashtable_t *hashtable, int key);

entry_t *ht_newpair(int key, int val);

void ht_set(hashtable_t *hashtable, int key, int val);

int ht_get(hashtable_t *hashtable, int key);

void print_ht(hashtable_t *hashtable);
