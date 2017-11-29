#include "tac.h"


TAC* tacGenerate(AST_NODE* node){

    int i = 0;
    TAC* code[MAX_SONS];
    TAC* result = 0;

    if (!node){
        return 0;
    }

    //Processa os nodos folha em primeiro lugar
    for(i=0; i<MAX_SONS; ++i){
        code[i] = tacGenerate(node->son[i]);
    }

    switch (node->type){

        case AST_SYMBOL:
            result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0, 0); break;

        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_LESS:
        case AST_GREATER:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_NE:
        case AST_AND:
        case AST_OR:
        case AST_NOT:
            result = tacOp(node, code[0], code[1]); break;

        case AST_ARRAY:
            result = tacVectorAccess(node, code[0]); break;

        case AST_EXPRESSION:
            result = code[0]; break;

        case AST_ATTR:
            result = tacVarAttribution(node, code[0]);
            // tacPrintBack(result);
            break;

        case AST_IF:
            result = tacIf(code[0], code[1]);
            // tacPrintBack(result);
            break;

        case AST_IF_ELSE:
            result = tacIfElse(code[0], code[1], code[2]);
            tacPrintBack(result);
            break;

        case AST_COMMAND_BLOCK:
            result = tacJoin(code[1], code[0]);
            break;

        default:
            return 0;

        /*
        case AST_READ: fprintf(stderr, "AST_READ\n"); break;
        case AST_CJTODEC_ELEM: fprintf(stderr, "AST_CJTODEC_ELEM\n"); break;
        case AST_DEC_VAR_GLOB: fprintf(stderr, "AST_DEC_VAR_GLOB\n"); break;
        case AST_DEC_VEC_SEQ: fprintf(stderr, "AST_DEC_VEC_SEQ\n"); break;
        case AST_DEC_VEC: fprintf(stderr, "AST_DEC_VEC\n"); break;
        case AST_DEC_FUNC: fprintf(stderr, "AST_DEC_FUNC\n"); break;
        case AST_DEC_PARAM: fprintf(stderr, "AST_DEC_PARAM\n"); break;
        case AST_DEC_PARAM_VEC: fprintf(stderr, "AST_DEC_PARAM_VEC\n"); break;
        case AST_COMMAND_BLOCK: fprintf(stderr, "AST_COMMAND_BLOCK\n"); break;
        case AST_VEC_COMMAND_BLOCK: fprintf(stderr, "AST_VEC_COMMAND_BLOCK\n"); break;
        case AST_DEC_VAR_BYTE: fprintf(stderr, "AST_DEC_VAR_BYTE\n"); break;
        case AST_DEC_VAR_SHORT: fprintf(stderr, "AST_DEC_VAR_SHORT\n"); break;
        case AST_DEC_VAR_LONG: fprintf(stderr, "AST_DEC_VAR_LONG\n"); break;
        case AST_DEC_VAR_FLOAT: fprintf(stderr, "AST_DEC_VAR_FLOAT\n"); break;
        case AST_DEC_VAR_DOUBLE: fprintf(stderr, "AST_DEC_VAR_DOUBLE\n"); break;
        case AST_DEC_VEC_SHORT: fprintf(stderr, "AST_DEC_VEC_SHORT\n"); break;
        case AST_DEC_VEC_LONG: fprintf(stderr, "AST_DEC_VEC_LONG\n"); break;
        case AST_DEC_VEC_FLOAT: fprintf(stderr, "AST_DEC_VEC_FLOAT\n"); break;
        case AST_DEC_VEC_DOUBLE: fprintf(stderr, "AST_DEC_VEC_DOUBLE\n"); break;
        case AST_DEC_VEC_BYTE: fprintf(stderr, "AST_DEC_VEC_BYTE\n"); break;
        case AST_CALLFUNC: fprintf(stderr, "AST_CALLFUNC\n"); break;
        case AST_ATTR_VEC: fprintf(stderr, "AST_ATTR_VEC\n"); break;
        case AST_PRINT: fprintf(stderr, "AST_PRINT\n"); break;
        case AST_PRINT_ARG: fprintf(stderr, "AST_PRINT_ARG\n"); break;
        case AST_PRINT_ARG2: fprintf(stderr, "AST_PRINT_ARG2\n"); break;
        case AST_IF: fprintf(stderr, "AST_IF\n"); break;
        case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE\n"); break;
        case AST_WHILE: fprintf(stderr, "AST_WHILE\n"); break;
        case AST_FUNC_ARG_LIST: fprintf(stderr, "AST_FUNC_ARG_LIST\n"); break;
        case AST_RETURN: fprintf(stderr, "AST_RETURN\n"); break;
        */
    }
    return result;
}

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2, HASH_NODE* op3){

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
    fprintf(stderr, "tacPrintBack--------Start\n");
    while(nodeBuffer){

        tacPrintSingle(nodeBuffer);
        nodeBuffer = nodeBuffer->prev;
    }
    fprintf(stderr, "tacPrintBack--------End\n");
}

void tacPrintSingle(TAC* node){

    if(!node){
        return;
    }

    fprintf(stderr, "node->type: %s", tacGetTypeName(node->type));
    if(node->res)
        fprintf(stderr, " | RES: %s", node->res->symbol.text);
    if(node->op1)
        fprintf(stderr, " | OP1: %s", node->op1->symbol.text);
    if(node->op2)
        fprintf(stderr, " | OP2: %s", node->op2->symbol.text);
    if(node->op3)
        fprintf(stderr, " | OP3: %s", node->op3->symbol.text);
    if(node->next)
        fprintf(stderr, " | next: %p", node->next);
    if(node->prev)
        fprintf(stderr, " | prev: %p", node->prev);

    fprintf(stderr, "\n");
}

const char* tacGetTypeName(int type){

    switch (type) {
        case TAC_SYMBOL: return "TAC_SYMBOL";
        case TAC_ADD: return "TAC_ADD";
        case TAC_SUB: return "TAC_SUB";
        case TAC_MUL: return "TAC_MUL";
        case TAC_DIV: return "TAC_DIV";
        case TAC_LESS: return "TAC_LESS";
        case TAC_GREATER: return "TAC_GREATER";
        case TAC_LE: return "TAC_LE";
        case TAC_GE: return "TAC_GE";
        case TAC_EQ: return "TAC_EQ";
        case TAC_NE: return "TAC_NE";
        case TAC_AND: return "TAC_AND";
        case TAC_OR: return "TAC_OR";
        case TAC_NOT: return "TAC_NOT";
        case TAC_VEC_ACCESS: return "TAC_VEC_ACCESS";
        case TAC_MOVE: return "TAC_MOVE";
        case TAC_IFZ: return "TAC_IFZ";
        case TAC_LABEL: return "TAC_LABEL";
        case TAC_JMP: return "TAC_JMP";
    }
}

HASH_NODE* makeTemporary(){

    static int count = 0;
    char* tempName = (char*) malloc(9*sizeof(char));

    snprintf(tempName, sizeof(tempName), "_temp%d", count);
    count++;

    return hashInsert(SYMBOL_TK_IDENTIFIER, tempName);
}

HASH_NODE* makeLabel(){

    static int count = 0;
    char* tempName = (char*) malloc(10*sizeof(char));

    snprintf(tempName, sizeof(tempName), "_label%d", count);
    count++;

    return hashInsert(SYMBOL_TK_IDENTIFIER, tempName);
}

TAC* tacOp(AST_NODE* node, TAC* code0, TAC* code1){

    HASH_NODE* temp;
    TAC* tac;
    int opType = 0;

    switch (node->type) {
        case AST_ADD: opType = TAC_ADD; break;
        case AST_SUB: opType = TAC_SUB; break;
        case AST_MUL: opType = TAC_MUL; break;
        case AST_DIV: opType = TAC_DIV; break;
        case AST_LESS: opType = TAC_LESS; break;
        case AST_GREATER: opType = TAC_GREATER; break;
        case AST_LE: opType = TAC_LE; break;
        case AST_GE: opType = TAC_GE; break;
        case AST_EQ: opType = TAC_EQ; break;
        case AST_NE: opType = TAC_NE; break;
        case AST_AND: opType = TAC_AND; break;
        case AST_OR: opType = TAC_OR; break;
        case AST_NOT: opType = TAC_NOT; break;
        default: fprintf(stderr, "ERRO interno em tacOp\n");
    }

    temp = makeTemporary();
    tac = tacCreate(opType, temp, code0?code0->res:0, code1?code1->res:0, 0);
    // tacPrintSingle(code0);
    // tacPrintSingle(code1);
    return tacJoin(tacJoin(code0, code1), tac);
}

TAC* tacVectorAccess(AST_NODE* node, TAC* code0){

    HASH_NODE* temp;
    TAC* tac;

    temp = makeTemporary();
    tac = tacCreate(TAC_VEC_ACCESS, temp, node->symbol, code0->res, 0);
    return tacJoin(code0, tac);
}

TAC* tacVarAttribution(AST_NODE* node, TAC* code0){

    TAC* tac;

    tac = tacCreate(TAC_MOVE, node->symbol, code0->res, 0, 0);
    return tacJoin(code0, tac);
}

TAC* tacIf(TAC* code0, TAC* code1){

    HASH_NODE* label;
    TAC *tacIfz, *tacLabel;

    label = makeLabel();
    tacIfz = tacCreate(TAC_IFZ, label, code0->res, 0, 0);
    tacLabel = tacCreate(TAC_LABEL, label, 0, 0, 0);
    return tacJoin(code0, tacJoin(tacIfz, tacJoin(code1, tacLabel)));
}

TAC* tacIfElse(TAC* code0, TAC* code1, TAC* code2){

    HASH_NODE *elseLabel, *endLabel;
    TAC *tacIfz, *tacElseLabel, *tacJump, *tacEndLabel;

    elseLabel = makeLabel();
    endLabel = makeLabel();

    tacIfz = tacCreate(TAC_IFZ, elseLabel, code0->res, 0, 0);
    tacElseLabel = tacCreate(TAC_LABEL, elseLabel, 0, 0, 0);
    tacJump = tacCreate(TAC_JMP, endLabel, 0, 0, 0);
    tacEndLabel = tacCreate(TAC_LABEL, endLabel, 0, 0, 0);

    return tacJoin(code0, tacJoin(tacIfz, tacJoin(code1, tacJoin(tacJump,
        tacJoin(tacElseLabel, tacJoin(code2, tacEndLabel))))));

    // tacEndLabel
    // code2
    // tacElseLabel
    // tacJump -> endLabel
    // code1
    // tacIfz -> elseLabel
    // code0
}
