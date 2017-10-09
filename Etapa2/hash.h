#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_SIZE 997

typedef struct symbol{
    int type;
	char *text;
} SYMBOL;

typedef struct hash_struct{
	struct symbol symbol;
	struct hash_struct *next;
} HASH_NODE;

HASH_NODE *_hashTable[HASH_SIZE];
void hashInit();
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint();
HASH_NODE* hashFind(char* text);
