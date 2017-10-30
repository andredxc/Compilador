#ifndef ASTREE_H
#define ASTREE_H

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL              0
#define AST_ADD                 1
#define AST_MUL                 2
#define AST_DIV                 3
#define AST_SUB                 4

#define AST_LESS                5
#define AST_GREATER             6
#define AST_LE                  7
#define AST_GE                  8
#define AST_EQ                  9
#define AST_NE                  10
#define AST_AND                 11
#define AST_OR                  12
#define AST_NOT                 16

#define AST_BYTE		        18
#define AST_SHORT               19
#define AST_LONG		        20
#define AST_FLOAT		        21
#define AST_DOUBLE		        22

#define AST_READ                17
#define AST_PRINT               47
#define AST_RETURN              53
#define AST_PRINT_ARG           48
#define AST_IF                  49
#define AST_IF_ELSE             50
#define AST_WHILE               51

#define AST_ARRAY               14
#define AST_DEC_VEC_SEQ_LIT     15
#define AST_CJTODEC_ELEM 		23

#define AST_DEC_VAR_GLOB 		24
#define AST_DEC_VEC_SEQ  		25
#define AST_DEC_VEC      		26
#define AST_DEC_VAR_INFO 		27
#define AST_DEC_FUNC			28
#define AST_DEC_PARAM			29
#define AST_DEC_PARAM_VEC		30
#define AST_COMMAND_BLOCK	    31
#define AST_VEC_COMMAND_BLOCK	32
#define AST_DEC_VAR_BYTE        33
#define AST_DEC_VAR_SHORT       34
#define AST_DEC_VAR_LONG        35
#define AST_DEC_VAR_FLOAT       36
#define AST_DEC_VAR_DOUBLE      37
#define AST_DEC_VEC_SHORT       38
#define AST_DEC_VEC_LONG        39
#define AST_DEC_VEC_FLOAT       40
#define AST_DEC_VEC_DOUBLE      41
#define AST_DEC_VEC_BYTE        42
#define AST_DEC_VEC_BYTE_STRING 43

#define AST_CALLFUNC            44
#define AST_FUNC_ARG_LIST       52
#define AST_ATTR                45
#define AST_ATTR_VEC            46



typedef struct ast_node{
    int type;
    struct ast_node* son[MAX_SONS];
    HASH_NODE* symbol;
}AST_NODE;

AST_NODE* astCreate(int type, HASH_NODE* node, AST_NODE* son0, AST_NODE* son1, AST_NODE* son2, AST_NODE* son3);
void astPrint(AST_NODE* node, int level);
void astreeProgram(AST_NODE* node, FILE* output);

#endif
