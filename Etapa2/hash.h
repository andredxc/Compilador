#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_TK_IDENTIFIER 5
#define HASH_SIZE 997

struct symbol{
    int type;
	char *text;
};

struct hash_struct{
	struct symbol symbol;
	struct hash_struct *next;
};

typedef struct hash_struct HASH_NODE;
typedef struct symbol SYMBOL;

HASH_NODE *_hashTable[HASH_SIZE];
void hashInit();
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint();
HASH_NODE* hashFind(char* text);
