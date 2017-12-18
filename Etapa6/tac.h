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
#define TAC_VEC_READ  15
#define TAC_MOVE        16
#define TAC_IFZ         17
#define TAC_LABEL       18
#define TAC_JMP         19
#define TAC_RETURN      20
#define TAC_VARDEC      21
#define TAC_VECDEC      22
#define TAC_READ        23
#define TAC_PRINT       24
#define TAC_PRINT_ARG   25
#define TAC_BEGINFUNC   26
#define TAC_ENDFUNC     27
#define TAC_PARAM       28
#define TAC_CALL        29
#define TAC_ARG         30
#define TAC_VEC_WRITE   31

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
void tacPrintForward(TAC* first);
TAC* tacReverse(TAC* last);
void tacPrintSingle(TAC* tac);
const char* tacGetTypeName(int type);

HASH_NODE* makeTemporary();
HASH_NODE* makeLabel();

TAC* tacOp(AST_NODE* node, TAC* code0, TAC* code1);
TAC* tacVectorRead(AST_NODE* node, TAC* code0);
TAC* tacVarAttribution(AST_NODE* node, TAC* code0);
TAC* tacVecAttribution(AST_NODE* node, TAC* code0, TAC* code1);
TAC* tacIf(TAC* code0, TAC* code1);
TAC* tacIfElse(TAC* code0, TAC* code1, TAC* code2);
TAC* tacWhile(TAC* code0, TAC* code1);
TAC* tacVarDeclaration(AST_NODE* node, TAC* code0);
TAC* makeRead(HASH_NODE* identifier);
TAC* makePrint(AST_NODE* print, TAC* code);
TAC* tacPrintArg(AST_NODE* node, TAC* code0, TAC* code1);
TAC* tacFuncDec(AST_NODE* node, TAC* code0, TAC* code1, TAC* code2);
TAC* tacFuncParam(AST_NODE* node);
TAC* tacFuncParamVec(TAC* code0, TAC* code1);
TAC* tacFuncCall(AST_NODE* node, TAC* code0);
TAC* tacFuncArgs(TAC* son0, TAC* son1);

#endif
