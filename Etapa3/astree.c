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
            case AST_ARRAY       : fprintf(stderr, "AST_ARRAY\n"); break;
            case AST_NOT         : fprintf(stderr, "AST_NOT\n"); break;
            case AST_READ        : fprintf(stderr, "AST_READ\n"); break;
            case AST_BYTE        : fprintf(stderr, "AST_BYTE\n"); break;
            case AST_SHORT       : fprintf(stderr, "AST_SHORT\n"); break;
            case AST_LONG        : fprintf(stderr, "AST_LONG\n"); break;
            case AST_FLOAT       : fprintf(stderr, "AST_FLOAT\n"); break;
            case AST_DOUBLE      : fprintf(stderr, "AST_DOUBLE\n"); break;
			case AST_CJTODEC_ELEM  : fprintd(stderr, "AST_CJTODEC_ELEM\n"); break;
			case AST_DEC_VAR_GLOB  : fprintd(stderr, "AST_DEC_VAR_GLOB\n"); break;
			case AST_DEC_VEC_SEQ   : fprintd(stderr, "AST_DEC_VEC_SEQ\n"); break;
			case AST_DEC_VEC       : fprintd(stderr, "AST_DEC_VEC\n"); break;
			case AST_DEC_VAR_INFO  : fprintd(stderr, "AST_DEC_VAR_INFO\n"); break;
			case AST_DEC_FUNC  : fprintd(stderr, "AST_DEC_FUNC\n"); break;
			case AST_DEC_PARAM  : fprintd(stderr, "AST_DEC_PARAM\n"); break;
			case AST_DEC_PARAM_VEC : fprintd(stderr, "AST_DEC_PARAM_VEC\n"); break;
			case AST_DEC_COMMAND_BLOCK  : fprintd(stderr, "AST_DEC_COMMAND_BLOCK\n"); break;
			case AST_VEC_COMMAND_BLOCK  : fprintd(stderr, "AST_VEC_COMMAND_BLOCK\n"); break;
			case AST_DEC_VEC_SEQ_LIT  : fprintd(stderr, "AST_DEC_VEC_SEQ_LIT\n"); break;


            default: break;
        }
        //Faz print dos filhos
        for(i=0; i < MAX_SONS; i++){
            astPrint(node->son[i], level+1);
        }
    }
}

void astreeProgram(AST_NODE* node, FILE* output){

	if(!node){
		return;
	}
	switch(node->type){
		case AST_SYMBOL: fprintf(output, "%s",node->symbol->symbol.text); break;

		case AST_ADD:
			astreeProgram(node->son[0],output);
			//printf("+");
			fprintf(output, "+");
			astreeProgram(node->son[1],output);
			break;
		case AST_SUB:
			astreeProgram(node->son[0],output);
			//printf("-");
			fprintf(output, "-");
			astreeProgram(node->son[1],output);
			break;
		case AST_MUL:
			astreeProgram(node->son[0],output);
			//printf("*");
			fprintf(output, "*");
			astreeProgram(node->son[1],output);
			break;
		case AST_DIV:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "/");
			astreeProgram(node->son[1],output);
			break;
		case AST_LESS:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "<");
			astreeProgram(node->son[1],output);
			break;
		case AST_GREATER:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, ">");
			astreeProgram(node->son[1],output);
			break;
		case AST_LE:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "<=");
			astreeProgram(node->son[1],output);
			break;
		case AST_GE:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, ">=");
			astreeProgram(node->son[1],output);
			break;
		case AST_EQ:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "==");
			astreeProgram(node->son[1],output);
			break;
		case AST_NE:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "!=");
			astreeProgram(node->son[1],output);
			break;
		case AST_AND:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "&&");
			astreeProgram(node->son[1],output);
			break;
		case AST_OR:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "||");
			astreeProgram(node->son[1],output);
			break;
		case AST_ARRAY:
			//printf("%s[",node->son[0]->symbol->symbol);
			fprintf(output, "%s [",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			//printf("]");
			fprintf(output, "]");
			break;
		case AST_NOT:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "!");
			astreeProgram(node->son[1],output);
			break;
		case AST_READ:
			//printf("read %s",node->symbol->symbol->text);
			fprintf(output, "read %s > ",node->symbol->symbol.text);
			break;
		case AST_BYTE:
			//printf("byte");
			fprintf(output, "byte");
			break;
		case AST_SHORT:
			//printf("short");
			fprintf(output, "short");
			break;
		case AST_LONG:
			//printf("long");
			fprintf(output, "long");
			break;
		case AST_FLOAT:		
			//printf("float");
			fprintf(output, "float");
			break;
		case AST_DOUBLE:
			//printf("double");
			fprintf(output, "double");
			break;
        case AST_CJTODEC_ELEM:
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break;
		case AST_DEC_VAR_GLOB:
			fprintf(output, "%s : ",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			fprintf(output, ";");
			break;
		case AST_DEC_VEC_SEQ:
			astreeProgram(node->son[0],output);
			fprintf(output, " [ %s ] ",node->symbol->symbol.text);
			astreeProgram(node->son[1],output);
			break;
		
		/*
		TODO: NAO SEI RESOLVER ISSO, TENTEI ADD UM NOVO TIPO MAS N CONSIGO PEGAR O LITERAL DO LIT_STRING, PQ O TIPO NOS JA COLOCAMOS COMO LIT_INTEGER
		| KW_SHORT '[' LIT_INTEGER ']' LIT_STRING				{$$ = astCreate(AST_DEC_VEC_SEQ_LIT,$3,$1,$5,0,0);} 
		TALVES TENHAMOS QUE CRIAR UM: 
		value:
		lit_string  {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);} 
		case AST_DEC_VEC_LIT:
				astreeProgram(node->son[0],output);
				fprintf(output, " [ %s ] ",node->symbol->symbol.text);
				astreeProgram(node->son[1],output);
				break;
		*/ 
		case AST_DEC_VEC:
			fprintf(output, "%s",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;  
		case AST_DEC_VAR_INFO:
			astreeProgram(node->son[0],output);
			fprintf(output, "= %s", node->symbol->symbol.text);
			break;  

		case AST_DEC_FUNC:
			fprintf(output, "(");
			astreeProgram(node->son[0],output);
			fprintf(output, ")");
			fprintf(output, "%s",node->symbol->symbol.text);
			fprintf(output, "(");
			astreeProgram(node->son[1],output);
			fprintf(output, ")");
			astreeProgram(node->son[2],output);
			break;  

		case AST_DEC_PARAM:
			fprintf(output, "%s :", node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;  

		case AST_DEC_PARAM_VEC:
			fprintf(output, ",");
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break; 

		case AST_DEC_COMMAND_BLOCK:
			fprintf(output, "{");
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			fprintf(output, "}");
			break;  

		case AST_VEC_COMMAND_BLOCK :
			fprintf(output, ";");
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break; 

	}
}






















