#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATATYPE_SHORT      1
#define DATATYPE_LONG       2
#define DATATYPE_FLOAT      3
#define DATATYPE_DOUBLE     4
#define DATATYPE_BYTE       5

#define NATURE_VARIABLE     1
#define NATURE_ARRAY        2
#define NATURE_FUNCTION     3

#define SYMBOL_LIT_INTEGER      1
#define SYMBOL_LIT_REAL         2
#define SYMBOL_LIT_CHAR         3
#define SYMBOL_LIT_STRING       4
#define SYMBOL_TK_IDENTIFIER    5
#define HASH_SIZE 997

typedef struct symbol{
    int type;
    int nature;
    int dataType;
	char *text;
}SYMBOL;

typedef struct hash_struct{
	struct symbol symbol;
	struct hash_struct *next;
}HASH_NODE;

HASH_NODE* _hashTable[HASH_SIZE];
void hashInit();
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text);
void hashPrint();
HASH_NODE* hashFind(char* text);

#endif
