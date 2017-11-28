#ifndef TAC_H
#define TAC_H

#include <stdio.h>

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL 1

typedef struct tac{

    int type;
    HASH_NODE* res;
    HASH_NODE* op1;
    HASH_NODE* op2;
    HASH_NODE* op3;
    struct tac* prev;
    struct tac* next;
}TAC;

TAC* tacGenerate(AST_NODE* node);
TAC* tacCreate(int type, HASH_NODE* op1, HASH_NODE* op2, HASH_NODE* op3, HASH_NODE* res);
TAC* tacJoin(TAC* list1, TAC* list2);
void tacPrintBack(TAC* last);
void tacPrintSingle(TAC* tac);
const char* tacGetTypeName(int type);

#endif
