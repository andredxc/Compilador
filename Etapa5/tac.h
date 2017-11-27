#ifndef TAC_H
#define TAC_H

#include <stdio.h>

#include "hash.h"
#include "astree.h"

typedef struct tac{

    int type;
    HASH_NODE* res;
    HASH_NODE* op1;
    HASH_NODE* op2;
    HASH_NODE* op3;
    struct tac* prev;
    struct tac* next;
}TAC;

TAC* tacCreate(int type, TAC* op1, TAC* op2, TAC* op3, TAC* res);
TAC* tacGenerate(AST_NODE* node);
TAC* tacJoin(TAC* list1, TAC* list2);
void tacPrintBack(TAC* last);
void tacPrintSingle(TAC* tac);

#endif
