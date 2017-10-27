#include "astree.h"

AST_NODE* astCreate(int type, HASH_NODE* symbol, AST_NODE* son0, AST_NODE* son1, AST_NODE* son2, AST_NODE* son3){

    AST_NODE* newNode;

    newNode = (AST_NODE*) calloc(1, sizeof(AST_NODE));

    newNode->type = type;
    newNode->symbol = symbol;
    newNode->son[0] = son0;
    newNode->son[1] = son1;
    newNode->son[2] = son2;
    newNode->son[3] = son3;

    return newNode;
}


void astPrint(AST_NODE* node, int level){

    int i;

    if(node){
        //Adiciona identação
        for(i=0; i < level; i++){
            fprintf(stderr, "  ");
        }
        //Faz
        switch (node->type) {
            case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL\n"); break;
            case AST_ADD: fprintf(stderr, "AST_ADD\n"); break;
            case AST_SUB: fprintf(stderr, "AST_SUB\n"); break;
            case AST_MUL: fprintf(stderr, "AST_MUL\n"); break;
            case AST_DIV: fprintf(stderr, "AST_DIV\n"); break;
            case AST_LESS : fprintf(stderr, "AST_LESS\n"); break;
            case AST_GREATER : fprintf(stderr, "AST_GREATER\n"); break;
            case AST_LE : fprintf(stderr, "AST_LE\n"); break;
            case AST_GE : fprintf(stderr, "AST_GE\n"); break;
            case AST_EQ : fprintf(stderr, "AST_EQ\n"); break;
            case AST_NE : fprintf(stderr, "AST_NE\n"); break;
            case AST_AND : fprintf(stderr, "AST_AND\n"); break;
            case AST_OR : fprintf(stderr, "AST_OR\n"); break;
            case AST_IDENTIFIER  : fprintf(stderr, "AST_IDENTIFIER\n"); break;
            case AST_ARRAY       : fprintf(stderr, "AST_ARRAY\n"); break;
            case AST_LITINT      : fprintf(stderr, "AST_LITINT\n"); break;
            case AST_LITREAL     : fprintf(stderr, "AST_LITREAL\n"); break;
            case AST_LITCHAR     : fprintf(stderr, "AST_LITCHAR\n"); break;
            case AST_CALLFUNC    : fprintf(stderr, "AST_CALLFUNC\n"); break;
            case AST_NOT         : fprintf(stderr, "AST_NOT\n"); break;
            case AST_READ        : fprintf(stderr, "AST_READ\n"); break;
            default: break;
        }
        //Faz print dos filhos
        for(i=0; i < MAX_SONS; i++){
            astPrint(node->son[i], level+1);
        }
    }
}
