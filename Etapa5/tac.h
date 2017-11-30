#ifndef TAC_H
#define TAC_H

#include <stdio.h>

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL      1
#define TAC_ADD         2
#define TAC_SUB         3
#define TAC_MUL         4
#define TAC_DIV         5
#define TAC_LESS        6
#define TAC_GREATER     7
#define TAC_LE          8
#define TAC_GE          9
#define TAC_EQ          10
#define TAC_NE          11
#define TAC_AND         12
#define TAC_OR          13
#define TAC_NOT         14
#define TAC_VEC_ACCESS  15
#define TAC_MOVE        16
#define TAC_IFZ         17
#define TAC_LABEL       18
#define TAC_JMP         19
#define TAC_RETURN      20
#define TAC_VARDEC      21
#define TAC_VECDEC      22
#define TAC_READ        23


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
TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2, HASH_NODE* op3);
TAC* tacJoin(TAC* list1, TAC* list2);
void tacPrintBack(TAC* last);
void tacPrintSingle(TAC* tac);
const char* tacGetTypeName(int type);

HASH_NODE* makeTemporary();
HASH_NODE* makeLabel();

TAC* tacOp(AST_NODE* node, TAC* code0, TAC* code1);
TAC* tacVectorAccess(AST_NODE* node, TAC* code0);
TAC* tacVarAttribution(AST_NODE* node, TAC* code0);
TAC* tacVecAttribution(AST_NODE* node, TAC* code0, TAC* code1);
TAC* tacIf(TAC* code0, TAC* code1);
TAC* tacIfElse(TAC* code0, TAC* code1, TAC* code2);
TAC* tacWhile(TAC* code0, TAC* code1);
TAC* tacVarDeclaration(AST_NODE* node, TAC* code0);
TAC* makeRead(HASH_NODE* identifier);

#endif
