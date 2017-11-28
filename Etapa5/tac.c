#include "tac.h"


TAC* tacGenerate(AST_NODE* node){

    switch (node->type) {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break;
        case AST_MUL: fprintf(stderr, "AST_MUL"); break;
        case AST_DIV: fprintf(stderr, "AST_DIV"); break;
        case AST_LESS: fprintf(stderr, "AST_LESS"); break;
        case AST_GREATER: fprintf(stderr, "AST_GREATER"); break;
        case AST_LE: fprintf(stderr, "AST_LE"); break;
        case AST_GE: fprintf(stderr, "AST_GE"); break;
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_NE: fprintf(stderr, "AST_NE"); break;
        case AST_AND: fprintf(stderr, "AST_AND"); break;
        case AST_OR: fprintf(stderr, "AST_OR"); break;
        case AST_ARRAY: fprintf(stderr, "AST_ARRAY"); break;
        case AST_NOT: fprintf(stderr, "AST_NOT"); break;
        case AST_READ: fprintf(stderr, "AST_READ"); break;
        case AST_BYTE: fprintf(stderr, "AST_BYTE"); break;
        case AST_SHORT: fprintf(stderr, "AST_SHORT"); break;
        case AST_LONG: fprintf(stderr, "AST_LONG"); break;
        case AST_FLOAT: fprintf(stderr, "AST_FLOAT"); break;
        case AST_DOUBLE: fprintf(stderr, "AST_DOUBLE"); break;
        case AST_CJTODEC_ELEM: fprintf(stderr, "AST_CJTODEC_ELEM"); break;
        case AST_DEC_VAR_GLOB: fprintf(stderr, "AST_DEC_VAR_GLOB"); break;
        case AST_DEC_VEC_SEQ: fprintf(stderr, "AST_DEC_VEC_SEQ"); break;
        case AST_DEC_VEC: fprintf(stderr, "AST_DEC_VEC"); break;
        case AST_DEC_FUNC: fprintf(stderr, "AST_DEC_FUNC"); break;
        case AST_DEC_PARAM: fprintf(stderr, "AST_DEC_PARAM"); break;
        case AST_DEC_PARAM_VEC: fprintf(stderr, "AST_DEC_PARAM_VEC"); break;
        case AST_COMMAND_BLOCK: fprintf(stderr, "AST_COMMAND_BLOCK"); break;
        case AST_VEC_COMMAND_BLOCK: fprintf(stderr, "AST_VEC_COMMAND_BLOCK"); break;
        case AST_DEC_VAR_BYTE: fprintf(stderr, "AST_DEC_VAR_BYTE"); break;
        case AST_DEC_VAR_SHORT: fprintf(stderr, "AST_DEC_VAR_SHORT"); break;
        case AST_DEC_VAR_LONG: fprintf(stderr, "AST_DEC_VAR_LONG"); break;
        case AST_DEC_VAR_FLOAT: fprintf(stderr, "AST_DEC_VAR_FLOAT"); break;
        case AST_DEC_VAR_DOUBLE: fprintf(stderr, "AST_DEC_VAR_DOUBLE"); break;
        case AST_DEC_VEC_SHORT: fprintf(stderr, "AST_DEC_VEC_SHORT"); break;
        case AST_DEC_VEC_LONG: fprintf(stderr, "AST_DEC_VEC_LONG"); break;
        case AST_DEC_VEC_FLOAT: fprintf(stderr, "AST_DEC_VEC_FLOAT"); break;
        case AST_DEC_VEC_DOUBLE: fprintf(stderr, "AST_DEC_VEC_DOUBLE"); break;
        case AST_DEC_VEC_BYTE: fprintf(stderr, "AST_DEC_VEC_BYTE"); break;
        case AST_CALLFUNC: fprintf(stderr, "AST_CALLFUNC"); break;
        case AST_ATTR: fprintf(stderr, "AST_ATTR"); break;
        case AST_ATTR_VEC: fprintf(stderr, "AST_ATTR_VEC"); break;
        case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
        case AST_PRINT_ARG: fprintf(stderr, "AST_PRINT_ARG"); break;
        case AST_PRINT_ARG2: fprintf(stderr, "AST_PRINT_ARG2"); break;
        case AST_IF: fprintf(stderr, "AST_IF"); break;
        case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE"); break;
        case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
        case AST_FUNC_ARG_LIST: fprintf(stderr, "AST_FUNC_ARG_LIST"); break;
        case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
        case AST_EXPRESSION: fprintf(stderr, "AST_EXPRESSION"); break;
    }
}

TAC* tacCreate(int type, HASH_NODE* op1, HASH_NODE* op2, HASH_NODE* op3, HASH_NODE* res){

    TAC* newNode;

    newNode= (TAC*)calloc(1, sizeof(TAC));

    newNode->type = type;
    newNode->op1 = op1;
    newNode->op2 = op2;
    newNode->op3 = op3;
    newNode->res = res;
    newNode->next = 0;
    newNode->prev = 0;

    return newNode;
}

TAC* tacJoin(TAC* list1, TAC* list2){

    TAC* tac = list2;

    if(!list1){
        return list2;
    }
    if(!list2){
        return list1;
    }

    //Encontra o primeiro nodo de list2
    while(tac->prev){
        tac = tac->prev;
    }

    tac->prev = list1;
    list1->next - tac;
    return list2;
}

void tacPrintBack(TAC* node){

    TAC* nodeBuffer;

    nodeBuffer = node;

    while(nodeBuffer){

        tacPrintSingle(nodeBuffer);
        nodeBuffer = nodeBuffer->next;
    }
}

void tacPrintSingle(TAC* node){

    fprintf(stderr, "node->type: %s\n", tacGetTypeName(node->type));
    if(node->res)
        fprintf(stderr, "node->res: %p\n", node->res);
    if(node->op1)
        fprintf(stderr, "node->op1: %p\n", node->op1);
    if(node->op2)
        fprintf(stderr, "node->op2: %p\n", node->op2);
    if(node->op3)
        fprintf(stderr, "node->op3: %p\n", node->op3);
    if(node->next)
        fprintf(stderr, "node->next: %p\n", node->next);
    if(node->prev)
        fprintf(stderr, "node->prev: %p\n", node->prev);
}

const char* tacGetTypeName(int type){

    switch (type) {
        case TAC_SYMBOL: return "1";
    }
}
