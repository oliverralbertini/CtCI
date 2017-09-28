SRCS=ReturnKthtoLast.c DeleteMiddleNode.c
most: $(SRCS:.c=)
LIB=lib

RemoveDups: RemoveDups.o libHashTable.a
	gcc RemoveDups.o -o RemoveDups -L. -lHashTable

RemoveDups.o: RemoveDups.c HashTable.h
	gcc -c RemoveDups.c -I.

libHashTable.a: HashTable.o
	ar -cvq libHashTable.a HashTable.o

HashTable.o: HashTable.h HashTable.c
	gcc -c HashTable.c -I.

run_CheckPermutation: CheckPermutation
	./CheckPermutation "qwertyuiop" "poiuytrewq"
.PHONY: all
