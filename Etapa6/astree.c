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
            case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
            case AST_ADD: fprintf(stderr, "AST_ADD"); break;
            case AST_SUB: fprintf(stderr, "AST_SUB"); break;
            case AST_MUL: fprintf(stderr, "AST_MUL"); break;
            case AST_DIV: fprintf(stderr, "AST_DIV"); break;
            case AST_LESS : fprintf(stderr, "AST_LESS"); break;
            case AST_GREATER : fprintf(stderr, "AST_GREATER"); break;
            case AST_LE : fprintf(stderr, "AST_LE"); break;
            case AST_GE : fprintf(stderr, "AST_GE"); break;
            case AST_EQ : fprintf(stderr, "AST_EQ"); break;
            case AST_NE : fprintf(stderr, "AST_NE"); break;
            case AST_AND : fprintf(stderr, "AST_AND"); break;
            case AST_OR : fprintf(stderr, "AST_OR"); break;
            case AST_ARRAY       : fprintf(stderr, "AST_ARRAY"); break;
            case AST_NOT         : fprintf(stderr, "AST_NOT"); break;
            case AST_READ        : fprintf(stderr, "AST_READ"); break;
            case AST_BYTE        : fprintf(stderr, "AST_BYTE"); break;
            case AST_SHORT       : fprintf(stderr, "AST_SHORT"); break;
            case AST_LONG        : fprintf(stderr, "AST_LONG"); break;
            case AST_FLOAT       : fprintf(stderr, "AST_FLOAT"); break;
            case AST_DOUBLE      : fprintf(stderr, "AST_DOUBLE"); break;
			case AST_CJTODEC_ELEM  : fprintf(stderr, "AST_CJTODEC_ELEM"); break;
			case AST_DEC_VAR_GLOB  : fprintf(stderr, "AST_DEC_VAR_GLOB"); break;
			case AST_DEC_VEC_SEQ   : fprintf(stderr, "AST_DEC_VEC_SEQ"); break;
			case AST_DEC_VEC       : fprintf(stderr, "AST_DEC_VEC"); break;
			case AST_DEC_FUNC  : fprintf(stderr, "AST_DEC_FUNC"); break;
			case AST_DEC_PARAM  : fprintf(stderr, "AST_DEC_PARAM"); break;
			case AST_DEC_PARAM_VEC : fprintf(stderr, "AST_DEC_PARAM_VEC"); break;
			case AST_COMMAND_BLOCK  : fprintf(stderr, "AST_COMMAND_BLOCK"); break;
			case AST_VEC_COMMAND_BLOCK  : fprintf(stderr, "AST_VEC_COMMAND_BLOCK"); break;
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

            default: break;
        }
        if(node->symbol){
            fprintf(stderr, " - %s\n", node->symbol->symbol.text);
        }
        else{
            fprintf(stderr, "\n");
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
			fprintf(output, "+");
			astreeProgram(node->son[1],output);
			break;
		case AST_SUB:
			astreeProgram(node->son[0],output);
			fprintf(output, "-");
			astreeProgram(node->son[1],output);
			break;
		case AST_MUL:
			astreeProgram(node->son[0],output);
			fprintf(output, "*");
			astreeProgram(node->son[1],output);
			break;
		case AST_DIV:
			astreeProgram(node->son[0],output);
			fprintf(output, "/");
			astreeProgram(node->son[1],output);
			break;
		case AST_LESS:
			astreeProgram(node->son[0],output);
			fprintf(output, "<");
			astreeProgram(node->son[1],output);
			break;
		case AST_GREATER:
			astreeProgram(node->son[0],output);
			fprintf(output, ">");
			astreeProgram(node->son[1],output);
			break;
		case AST_LE:
			astreeProgram(node->son[0],output);
			fprintf(output, "<=");
			astreeProgram(node->son[1],output);
			break;
		case AST_GE:
			astreeProgram(node->son[0],output);
			fprintf(output, ">=");
			astreeProgram(node->son[1],output);
			break;
		case AST_EQ:
			astreeProgram(node->son[0],output);
			fprintf(output, "==");
			astreeProgram(node->son[1],output);
			break;
		case AST_NE:
			astreeProgram(node->son[0],output);
			fprintf(output, "!=");
			astreeProgram(node->son[1],output);
			break;
		case AST_AND:
			astreeProgram(node->son[0],output);
			fprintf(output, "&&");
			astreeProgram(node->son[1],output);
			break;
		case AST_OR:
			astreeProgram(node->son[0],output);
			fprintf(output, "||");
			astreeProgram(node->son[1],output);
			break;
		case AST_ARRAY:
			fprintf(output, "%s [",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			fprintf(output, "]");
			break;
		case AST_NOT:
            fprintf(output, "!(");
			astreeProgram(node->son[0],output);
            fprintf(output, ")");
			astreeProgram(node->son[1],output);
			break;
		case AST_READ:
			fprintf(output, "read > %s ",node->symbol->symbol.text);
			break;
		case AST_BYTE:
			fprintf(output, "byte");
			break;
		case AST_SHORT:
			fprintf(output, "short");
			break;
		case AST_LONG:
			fprintf(output, "long");
			break;
		case AST_FLOAT:
			fprintf(output, "float");
			break;
		case AST_DOUBLE:
			fprintf(output, "double");
			break;
        case AST_CJTODEC_ELEM:
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break;
		case AST_DEC_VAR_GLOB:
			fprintf(output, "%s : ",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			fprintf(output, ";\n");
			break;
		case AST_DEC_VEC_SEQ:
			astreeProgram(node->son[0],output);
			fprintf(output, " [ %s ] ",node->symbol->symbol.text);
			astreeProgram(node->son[1],output);
			break;
		case AST_DEC_VEC:
			fprintf(output, " %s ",node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;
		case AST_DEC_FUNC:
			fprintf(output, "(");
			astreeProgram(node->son[0],output);
			fprintf(output, ") ");
			fprintf(output, "%s",node->symbol->symbol.text);
			fprintf(output, "(");
			astreeProgram(node->son[1],output);
			fprintf(output, ")");
			astreeProgram(node->son[2],output);
			break;

		case AST_DEC_PARAM:
			fprintf(output, "%s: ", node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_DEC_PARAM_VEC:
			astreeProgram(node->son[0],output);
            if(node->son[1]){
                fprintf(output, ", ");
            }
			astreeProgram(node->son[1],output);
			break;

		case AST_COMMAND_BLOCK:
			fprintf(output, "{\n");
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			fprintf(output, "}");
			break;

		case AST_VEC_COMMAND_BLOCK :
			fprintf(output, ";\n");
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break;

		case AST_DEC_VAR_BYTE:
			fprintf(output, "byte = %s",  node->symbol->symbol.text);
			break;

		case AST_DEC_VAR_SHORT:
			fprintf(output, "short = %s",  node->symbol->symbol.text);
			break;

		case AST_DEC_VAR_LONG:
			fprintf(output, "long = %s",  node->symbol->symbol.text);
			break;

		case AST_DEC_VAR_FLOAT:
			fprintf(output, "float = %s",  node->symbol->symbol.text);
			break;

		case AST_DEC_VAR_DOUBLE:
			fprintf(output, "double = %s",  node->symbol->symbol.text);
			break;

		case AST_DEC_VEC_SHORT:
			fprintf(output, "short [%s]",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_DEC_VEC_LONG:
			fprintf(output, "long [%s]",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_DEC_VEC_FLOAT:
			fprintf(output, "float [%s]",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_DEC_VEC_DOUBLE:
			fprintf(output, "double [%s]",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_DEC_VEC_BYTE:
			fprintf(output, "byte [%s]",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_CALLFUNC:
			fprintf(output, "%s (",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			fprintf(output, ")");
			break;

		case AST_ATTR:
			fprintf(output, "%s = ",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			break;

		case AST_ATTR_VEC:
			fprintf(output, "%s [ ",  node->symbol->symbol.text);
			astreeProgram(node->son[0],output);
			fprintf(output, " ] = ");
			astreeProgram(node->son[1],output);
			break;

		case AST_PRINT:
			fprintf(output, "print ");
			astreeProgram(node->son[0],output);
			break;

		case AST_PRINT_ARG:
			if(node->son[0]){
				astreeProgram(node->son[0],output);
                fprintf(output, ", ");
				astreeProgram(node->son[1],output);
			}else{
				fprintf(output, "%s",  node->symbol->symbol.text);
                if(node->son[1]){
                    fprintf(output, ", ");
                }
                else{
                    fprintf(output, " ");
                }
				astreeProgram(node->son[1],output);
			}
			break;

		case AST_PRINT_ARG2:
			if(node->son[0]){
				fprintf(output, ", ");
				astreeProgram(node->son[0],output);
				astreeProgram(node->son[1],output);
			}else{
				fprintf(output, ", %s ",  node->symbol->symbol.text);
				astreeProgram(node->son[1],output);
			}
			break;


		case AST_RETURN:
			fprintf(output, "return (");
			astreeProgram(node->son[0],output);
            fprintf(output, ")");
			break;

		case AST_IF:
			fprintf(output, "if ( ");
			astreeProgram(node->son[0],output);
			fprintf(output, ") then ");
			astreeProgram(node->son[1],output);
			break;

		case AST_IF_ELSE:
			fprintf(output, "if ( ");
			astreeProgram(node->son[0],output);
			fprintf(output, ") then ");
			astreeProgram(node->son[1],output);
			fprintf(output, " else ");
			astreeProgram(node->son[2],output);
			break;

		case AST_WHILE:
			fprintf(output, "while ( ");
			astreeProgram(node->son[0],output);
			fprintf(output, ")");
			astreeProgram(node->son[1],output);

			break;

		case AST_FUNC_ARG_LIST:
            if(node->son[0]){
                astreeProgram(node->son[0],output);
                if(node->son[1]){
                    fprintf(output, ", ");
                }
                astreeProgram(node->son[1],output);
                break;
            }

        case AST_EXPRESSION:
            fprintf(output, "( ");
			astreeProgram(node->son[0],output);
			fprintf(output, ") ");
			break;


	}
}

void astPrintNode(AST_NODE* node){

    fprintf(stderr, "node->type: %s\n", astNodeType(node->type));
    if(node->son[0])
        fprintf(stderr, "node->son[0]: %s\n", astNodeType(node->son[0]->type));
    if(node->son[1])
        fprintf(stderr, "node->son[1]: %s\n", astNodeType(node->son[1]->type));
    if(node->son[2])
        fprintf(stderr, "node->son[2]: %s\n", astNodeType(node->son[2]->type));
}

const char* astNodeType(int type){

    switch (type) {
        case AST_SYMBOL: return "AST_SYMBOL";
        case AST_ADD: return "AST_ADD";
        case AST_SUB: return "AST_SUB";
        case AST_MUL: return "AST_MUL";
        case AST_DIV: return "AST_DIV";
        case AST_LESS: return "AST_LESS";
        case AST_GREATER: return "AST_GREATER";
        case AST_LE: return "AST_LE";
        case AST_GE: return "AST_GE";
        case AST_EQ: return "AST_EQ";
        case AST_NE: return "AST_NE";
        case AST_AND: return "AST_AND";
        case AST_OR: return "AST_OR";
        case AST_ARRAY: return "AST_ARRAY";
        case AST_NOT: return "AST_NOT";
        case AST_READ: return "AST_READ";
        case AST_BYTE: return "AST_BYTE";
        case AST_SHORT: return "AST_SHORT";
        case AST_LONG: return "AST_LONG";
        case AST_FLOAT: return "AST_FLOAT";
        case AST_DOUBLE: return "AST_DOUBLE";
		case AST_CJTODEC_ELEM: return "AST_CJTODEC_ELEM";
		case AST_DEC_VAR_GLOB: return "AST_DEC_VAR_GLOB";
		case AST_DEC_VEC_SEQ: return "AST_DEC_VEC_SEQ";
		case AST_DEC_VEC: return "AST_DEC_VEC";
		case AST_DEC_FUNC: return "AST_DEC_FUNC";
		case AST_DEC_PARAM: return "AST_DEC_PARAM";
		case AST_DEC_PARAM_VEC: return "AST_DEC_PARAM_VEC";
		case AST_COMMAND_BLOCK: return "AST_COMMAND_BLOCK";
		case AST_VEC_COMMAND_BLOCK: return "AST_VEC_COMMAND_BLOCK";
        case AST_DEC_VAR_BYTE: return "AST_DEC_VAR_BYTE";
        case AST_DEC_VAR_SHORT: return "AST_DEC_VAR_SHORT";
        case AST_DEC_VAR_LONG: return "AST_DEC_VAR_LONG";
        case AST_DEC_VAR_FLOAT: return "AST_DEC_VAR_FLOAT";
        case AST_DEC_VAR_DOUBLE: return "AST_DEC_VAR_DOUBLE";
        case AST_DEC_VEC_SHORT: return "AST_DEC_VEC_SHORT";
        case AST_DEC_VEC_LONG: return "AST_DEC_VEC_LONG";
        case AST_DEC_VEC_FLOAT: return "AST_DEC_VEC_FLOAT";
        case AST_DEC_VEC_DOUBLE: return "AST_DEC_VEC_DOUBLE";
        case AST_DEC_VEC_BYTE: return "AST_DEC_VEC_BYTE";
        case AST_CALLFUNC: return "AST_CALLFUNC";
        case AST_ATTR: return "AST_ATTR";
        case AST_ATTR_VEC: return "AST_ATTR_VEC";
        case AST_PRINT: return "AST_PRINT";
        case AST_PRINT_ARG: return "AST_PRINT_ARG";
		case AST_PRINT_ARG2: return "AST_PRINT_ARG2";
        case AST_IF: return "AST_IF";
        case AST_IF_ELSE: return "AST_IF_ELSE";
        case AST_WHILE: return "AST_WHILE";
        case AST_FUNC_ARG_LIST: return "AST_FUNC_ARG_LIST";
        case AST_RETURN: return "AST_RETURN";
        case AST_EXPRESSION: return "AST_EXPRESSION";
        default: return "UNKNOWN";
    }
}
