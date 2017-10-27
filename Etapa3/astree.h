#ifndef ASTREE_H
#define ASTREE_H

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL      0
#define AST_ADD         1
#define AST_MUL         2
#define AST_DIV         3
#define AST_SUB         4
#define AST_LESS        5
#define AST_GREATER     6
#define AST_LE          7
#define AST_GE          8
#define AST_EQ          9
#define AST_NE          10
#define AST_AND         11
#define AST_OR          12
#define AST_IDENTIFIER  13
#define AST_ARRAY       14
#define AST_LITINT      15
#define AST_LITREAL     16
#define AST_LITCHAR     17
#define AST_CALLFUNC    18
#define AST_NOT         19
#define AST_READ        20

typedef struct ast_node{
    int type;
    struct ast_node* son[MAX_SONS];
    HASH_NODE* symbol;
}AST_NODE;

AST_NODE* astCreate(int type, HASH_NODE* node, AST_NODE* son0, AST_NODE* son1, AST_NODE* son2, AST_NODE* son3);
void astPrint(AST_NODE* node, int level);

#endif
