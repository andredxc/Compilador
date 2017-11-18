#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

int _errorStatus;

int semanticFullCheck(AST_NODE* astree){

    _errorStatus = 0;

    semanticCheckDeclarations(astree);
    semanticCheckFunctionDeclarations(astree);
    semanticCheckFunctionCalls(astree);
    checkAstNodeDataType(astree);

}

void semanticCheckDeclarations(AST_NODE* node){

    int i;
    int arraySize;
    AST_NODE* astBuffer;

    if(node){

        if(node->type == AST_DEC_VAR_GLOB){

            if(node->symbol->symbol.dataType >= 0){
                fprintf(stderr, "ERRO, variável %s já foi declarada\n", node->symbol->symbol.text);
                _errorStatus = 1;
            }

            //Declaração de variável global
            if(node->son[0]->type == AST_DEC_VAR_SHORT && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_SHORT;
                node->symbol->symbol.nature = NATURE_VARIABLE;
            }
            else if(node->son[0]->type == AST_DEC_VAR_LONG && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_LONG;
                node->symbol->symbol.nature = NATURE_VARIABLE;
            }
            else if(node->son[0]->type == AST_DEC_VAR_BYTE && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL || node->son[0]->symbol->symbol.type == LIT_CHAR)){
                node->symbol->symbol.dataType = DATATYPE_BYTE;
                node->symbol->symbol.nature = NATURE_VARIABLE;
            }
            else if(node->son[0]->type == AST_DEC_VAR_FLOAT && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_FLOAT;
                node->symbol->symbol.nature = NATURE_VARIABLE;
            }
            else if(node->son[0]->type == AST_DEC_VAR_DOUBLE && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                node->symbol->symbol.nature = NATURE_VARIABLE;
            }

            //Declaração de vetor global
            else if(node->son[0]->type == AST_DEC_VEC_SHORT || node->son[0]->type == AST_DEC_VEC_LONG ||
                node->son[0]->type == AST_DEC_VEC_FLOAT || node->son[0]->type == AST_DEC_VEC_DOUBLE ||
                node->son[0]->type == AST_DEC_VEC_BYTE){
                //Verificações gerais para todos os dataTypes de array

                //Verifica se o número de elementos é um inteiro
                if(node->son[0]->symbol->symbol.type == LIT_INTEGER){
                    arraySize = atoi(node->son[0]->symbol->symbol.text);
                    if(arraySize == 0){
                        fprintf(stderr, "ERRO, vetor declarado com tamanho 0\n");
                        _errorStatus = 1;
                    }
                    else if(node->son[0]->son[0]){
                        //Verifica o número de valores dados para o vetor
                        //fprintf(stderr, "ARRAYSIZE: %d\n", arraySize);
                        astBuffer = node->son[0]->son[0];
                        for(i = 0; i < arraySize; i++){
                            if(!astBuffer){
                                fprintf(stderr, "ERRO, número incorreto de valores de inicialização para o vetor\n");
                                _errorStatus = 1;
                                break;
                            }
                            else{
                                //fprintf(stderr, "INDICE %d, VALOR %s\n", i, astBuffer->symbol->symbol.text);
                                astBuffer = astBuffer->son[0];
                            }
                        }
                    }
                }
                else{
                    fprintf(stderr, "ERRO %d, número de elementos do vetor deve ser inteiro\n", 0);
                }

                if(node->son[0]->type == AST_DEC_VEC_SHORT){
                    node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                }
                else if(node->son[0]->type == AST_DEC_VEC_LONG){
                    node->symbol->symbol.dataType = DATATYPE_LONG;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                }
                else if(node->son[0]->type == AST_DEC_VEC_FLOAT){
                    node->symbol->symbol.dataType = DATATYPE_FLOAT;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                }
                else if(node->son[0]->type == AST_DEC_VEC_DOUBLE){
                    node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                }
                else if(node->son[0]->type == AST_DEC_VEC_BYTE){
                    node->symbol->symbol.dataType = DATATYPE_BYTE;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                }
                else{
                    fprintf(stderr, "Erro interno em semanticCheckDeclarations()\n");
                    _errorStatus = 1;
                }
            }
            else{
                fprintf(stderr, "ERRO %d, tipo incorreto na variável %s\n", 0, node->symbol->symbol.text);
                _errorStatus = 1;
            }
        }

        for(i=0; i < MAX_SONS; i++){
            semanticCheckDeclarations(node->son[i]);
        }
    }
}

void semanticCheckFunctionDeclarations(AST_NODE* node){

    int i;

    if(node){

        if(node->type == AST_DEC_FUNC){

            if(node->symbol->symbol.dataType >= 0){
                //Função já declarada
                fprintf(stderr, "ERRO, função %s já foi declarada\n", node->symbol->symbol.text);
                _errorStatus = 1;
            }
            else{
                //Salvando tipo da função (tipo do retorno)
                switch(node->son[0]->type){
                    case AST_SHORT:
                        node->symbol->symbol.dataType = DATATYPE_SHORT;
                        node->symbol->symbol.nature = NATURE_FUNCTION;
                        break;
                    case AST_LONG:
                        node->symbol->symbol.dataType = DATATYPE_LONG;
                        node->symbol->symbol.nature = NATURE_FUNCTION;
                        break;
                    case AST_FLOAT:
                        node->symbol->symbol.dataType = DATATYPE_FLOAT;
                        node->symbol->symbol.nature = NATURE_FUNCTION;
                        break;
                    case AST_DOUBLE:
                        node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                        node->symbol->symbol.nature = NATURE_FUNCTION;
                        break;
                    case AST_BYTE:
                        node->symbol->symbol.dataType = DATATYPE_BYTE;
                        node->symbol->symbol.nature = NATURE_FUNCTION;
                        break;
                    default:
                        fprintf(stderr, "Erro interno em semanticCheckFunctionDeclarations()\n");
                        _errorStatus = 1;
                }
				// contabiliza o número de parâmetros quando a função é declarada
				node->symbol->symbol.numParams = countFuncNumParams(node)-1;
            }
        }

        for(i=0; i < MAX_SONS; i++){
            semanticCheckFunctionDeclarations(node->son[i]);
        }
    }
}

/* NÃO ESTA PRONTA*/
void semanticSetOperatorsResultType(AST_NODE* node){

    fprintf(stderr, "EU NÃO ESTOU PRONTA, NÃO ME CHAME\n");

    int i;

    // AST_ADD
    // AST_MUL
    // AST_DIV
    // AST_SUB
    // AST_LESS
    // AST_GREATER
    // AST_LE
    // AST_GE
    // AST_EQ
    // AST_NE
    // AST_AND
    // AST_OR
    // AST_NOT

    if(node){

        if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV ||
            node->type == AST_LESS || node->type == AST_GREATER || node->type == AST_LE || node->type == AST_GE ||
            node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR ||
            node->type == AST_OR){
            //Definições gerais para todos os operadores
            if(node->symbol->symbol.dataType >= 0){
                fprintf(stderr, "ERRO, tipo resultante dos operadores já foi definido\n");
                return;
            }

            if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV){
                //Operadores aritméticos

                if(node->son[0]->symbol->symbol.nature == NATURE_VARIABLE && node->son[1]->symbol->symbol.nature == NATURE_VARIABLE){
                    //Ambos os operandos são variáveis
                    if(node->son[0]->symbol->symbol.dataType == node->son[1]->symbol->symbol.dataType){
                        //Os operandos têm os mesmo dataType
                        switch(node->son[0]->symbol->symbol.dataType){
                            case DATATYPE_SHORT: node->symbol->symbol.dataType = DATATYPE_SHORT;
                            case DATATYPE_LONG: node->symbol->symbol.dataType = DATATYPE_LONG;
                            case DATATYPE_FLOAT: node->symbol->symbol.dataType = DATATYPE_FLOAT;
                            case DATATYPE_DOUBLE: node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                            case DATATYPE_BYTE: node->symbol->symbol.dataType = DATATYPE_BYTE;
                            default: fprintf(stderr, "Erro interno em %s\n", __FUNCTION__);
                        }
                    }
                    else if((node->son[0]->symbol->symbol.dataType == DATATYPE_FLOAT || node->son[0]->symbol->symbol.dataType == DATATYPE_DOUBLE) &&
                        (node->son[1]->symbol->symbol.dataType == DATATYPE_SHORT || node->son[1]->symbol->symbol.dataType == DATATYPE_LONG ||
                        node->son[1]->symbol->symbol.dataType == DATATYPE_BYTE)){
                        //O operando da esquerda é real enquanto o da direita é inteiro

                    }
                    else if((node->son[1]->symbol->symbol.dataType == DATATYPE_FLOAT || node->son[1]->symbol->symbol.dataType == DATATYPE_DOUBLE) &&
                        (node->son[0]->symbol->symbol.dataType == DATATYPE_SHORT || node->son[0]->symbol->symbol.dataType == DATATYPE_LONG ||
                        node->son[0]->symbol->symbol.dataType == DATATYPE_BYTE)){
                        //O operando da direita é real enquanto o da esquerda é inteiro

                    }
                }
            }
        }

        for(i=0; i < MAX_SONS; i++){
            semanticSetOperatorsResultType(node->son[i]);
        }
    }
}

void semanticCheckFunctionCalls(AST_NODE* node){

    int i;

    if(!node){
        return;
    }

    if(node->type == AST_CALLFUNC){

        fprintf(stderr, "Verificando coisas de funções\n");
        //Verifica se a função foi declarada como função
        if(node->symbol->symbol.nature != NATURE_FUNCTION){

            if(node->symbol->symbol.nature < 0){
                fprintf(stderr, "ERRO, %s não foi declarada\n", node->symbol->symbol.text);
            }
            else{
                fprintf(stderr, "ERRO, %s não é uma função\n", node->symbol->symbol.text);
            }
            _errorStatus = 1;
        }
    }

    for(i = 0; i < MAX_SONS; i++){
        semanticCheckFunctionCalls(node->son[i]);
    }
}

int countFuncNumParams(AST_NODE *node){
	if(!node){ // if NULL = end of list
		return 0;
	}else{
		return 1 + countFuncNumParams(node->son[1]);
	}
}

/* Verifica os tipos dos nodos e trata */
void checkAstNodeDataType(AST_NODE* node){

	if(node == NULL){
		return;
	}

	int i;
	for(i=0; i<MAX_SONS; i++){
		checkAstNodeDataType(node->son[i]);
	}

	switch(node->type){
		case AST_CALLFUNC: verifyParams(node); break;
		default: break;
	}

}

/* Verifica se o parâmetro tem o mesmo número de itens da declaração e se os tipos são compatíveis. */
void verifyParams(AST_NODE* node){

	int numParam = 0;
	if(node->son[0]){
		verifyTypeFuncCallParams(node->son[0]);
		numParam = countFuncNumParams(node->son[0]);
	}

	HASH_NODE* hash = hashFind(node->symbol->symbol.text);
	int correct_n_par = hash->symbol.numParams;
	if(numParam != correct_n_par){
		fprintf(stderr, "Número invalido de parâmetros na chamada da função [%s]\n", node->symbol->symbol.text);
	}
}

/* Verifica se os tipos dos parametros passados em uma FUNCAO são compativeis com a declaração. */
int verifyTypeFuncCallParams(AST_NODE* node){
	if(!node){
		return 1;
	}
	//TODO: verificar se uma variavel na chamada da função existe?



}
