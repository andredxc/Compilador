#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

int _errorStatus;

int semanticFullCheck(AST_NODE* astree){

    _errorStatus = 0;

    semanticCheckDeclarations(astree);
    semanticCheckFunctionDeclarations(astree);
    semanticCheckAttributions(astree);
    semanticCheckFunctionCalls(astree);
    checkAstNodeDataType(astree);

    return _errorStatus;
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
                    node->symbol->symbol.dataType = DATATYPE_SHORT;
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

void semanticCheckAttributions(AST_NODE* node){

    int i, expDataType, arrayIndexDataType;

    if(!node){
        return;
    }

    if(node->type == AST_ATTR){
        //Atribuição a variáveis

        //Determina a validade do lado esquerdo
        if(node->symbol->symbol.nature != NATURE_VARIABLE){
            if(node->symbol->symbol.nature == NATURE_FUNCTION){
                fprintf(stderr, "ERRO, a função [%s] não pode ser usada como variável\n", node->symbol->symbol.text);
            }
            else if(node->symbol->symbol.nature == NATURE_ARRAY){
                fprintf(stderr, "ERRO, o vetor [%s] não pode ser usado sem indexação\n", node->symbol->symbol.text);
            }
            else{
                fprintf(stderr, "ERRO, a variável [%s] não foi declarada\n", node->symbol->symbol.text);
            }
            _errorStatus = 1;
        }
        //Determina a validade do lado direito
        expDataType = semanticSetOperatorsResultType(node->son[0]);
        if(expDataType == DATATYPE_BOOLEAN){
            fprintf(stderr, "ERRO, expressão atribuída à [%s] não pode ter tipo booleano\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        fprintf(stderr, "EXPRESSÃO ATRIBUIDA A [%s] É: ", node->symbol->symbol.text);
        switch (expDataType){
            case DATATYPE_SHORT:fprintf(stderr, "SHORT\n"); break;
            case DATATYPE_LONG:fprintf(stderr, "LONG\n"); break;
            case DATATYPE_FLOAT:fprintf(stderr, "FLOAT\n"); break;
            case DATATYPE_DOUBLE:fprintf(stderr, "DOUBLE\n"); break;
            case DATATYPE_BYTE:fprintf(stderr, "BYTE\n"); break;
            default: fprintf(stderr, "NÃO DEFINIDA\n");
        }
    }
    else if(node->type == AST_ATTR_VEC){
        //Atribuição a vetores

        //Determina a validade do lado esquerdo
        arrayIndexDataType = semanticSetOperatorsResultType(node->son[0]);
        if(node->symbol->symbol.nature < 0){
            fprintf(stderr, "ERRO, o vetor [%s] não foi declarado\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(arrayIndexDataType != DATATYPE_BYTE && arrayIndexDataType != DATATYPE_SHORT && arrayIndexDataType != DATATYPE_LONG){
            //Indice inválido
            fprintf(stderr, "ERRO, acesso ao vetor [%s] possui índice não inteiro\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }

        //Determina a validade do lado direito
        expDataType = semanticSetOperatorsResultType(node->son[1]);
        if(expDataType == DATATYPE_BOOLEAN){
            fprintf(stderr, "ERRO, expressão atribuída à [%s] não pode ter tipo booleano\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
    }

    for(i=0; i < MAX_SONS; i++){
        semanticCheckAttributions(node->son[i]);
    }
}

int semanticSetOperatorsResultType(AST_NODE* node){

    int i, arrayIndexDataType;

    if(!node){
        return -1;
    }

    int son0Type, son1Type;

    if(node->symbol && node->type == AST_SYMBOL){
        //O nodo é um símbolo
        if(node->symbol->symbol.nature == NATURE_ARRAY){
            fprintf(stderr, "ERRO, uso indevido do vetor [%s]\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(node->symbol->symbol.nature == NATURE_FUNCTION){
            fprintf(stderr, "ERRO, uso indevido da função [%s]\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        if(node->symbol->symbol.dataType >= 0){
            //Seu tipo já foi definido
            return node->symbol->symbol.dataType;
        }
        else{
            if(node->symbol->symbol.type == LIT_INTEGER){
                return DATATYPE_BYTE;
            }
            else if(node->symbol->symbol.type == LIT_REAL){
                return DATATYPE_FLOAT;
            }
            else{
                fprintf(stderr, "ERRO, a variável [%s] não foi declarada\n", node->symbol->symbol.text);
                _errorStatus = 1;
                return DATATYPE_BYTE;
            }
        }
    }
    else if(node->symbol && node->type == AST_ARRAY){
        //O nodo é um acesso a vetor
        if(node->symbol->symbol.nature == NATURE_ARRAY){
            //Variável declarada como array
            arrayIndexDataType = semanticSetOperatorsResultType(node->son[0]);
            if(arrayIndexDataType != DATATYPE_BYTE && arrayIndexDataType != DATATYPE_SHORT && arrayIndexDataType != DATATYPE_LONG){
                //Indice inválido
                fprintf(stderr, "ERRO, acesso ao vetor [%s] possui índice não inteiro\n", node->symbol->symbol.text);
                _errorStatus = 1;
            }
        }
        else{
            fprintf(stderr, "ERRO, o vetor [%s] não foi declarado\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        return node->symbol->symbol.dataType;
    }
    else if(node->symbol && node->type == AST_CALLFUNC){
        if(node->symbol->symbol.nature == NATURE_FUNCTION){
            //Verificar parâmetros???
        }
        else{
            fprintf(stderr, "ERRO, função [%s] não foi declarada\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        return node->symbol->symbol.dataType;
    }
    else{
        //Encontrar o tipo do nodo a partir de seus filhos
        if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV){
            //Expressões aritméticas
            son0Type = semanticSetOperatorsResultType(node->son[0]);
            son1Type = semanticSetOperatorsResultType(node->son[1]);

            if(son0Type == son1Type){
                //Lado esquerdo e direito são iguais
                if(son0Type == DATATYPE_SHORT){
                    //Ambos são short
                    return DATATYPE_SHORT;
                }
                else if(son0Type == DATATYPE_LONG){
                    //Ambos são long
                    return DATATYPE_LONG;
                }
                else if(son0Type == DATATYPE_FLOAT){
                    //Ambos são float
                    return DATATYPE_FLOAT;
                }
                else if(son0Type == DATATYPE_DOUBLE){
                    //Ambos são double
                    return DATATYPE_DOUBLE;
                }
                else if(son0Type == DATATYPE_BYTE){
                    //Ambos são byte
                    return DATATYPE_BYTE;
                }
                else{
                    fprintf(stderr, "Erro interno em %s\n", __FUNCTION__);
                    _errorStatus = 1;
                }
            }
            else if(son0Type == DATATYPE_FLOAT && son1Type == DATATYPE_DOUBLE){
                //Lado esquerdo é float e lado direito é double
                return DATATYPE_DOUBLE;
            }
            else if(son1Type == DATATYPE_FLOAT && son0Type == DATATYPE_DOUBLE){
                //Lado esquerdo é double e lado direito é float
                return DATATYPE_DOUBLE;
            }
            else if(son0Type == DATATYPE_FLOAT &&
                (son1Type == DATATYPE_SHORT || son1Type == DATATYPE_LONG ||
                son1Type == DATATYPE_BYTE)){
                //Lado esquerdo é float e lado direito é inteiro
                return DATATYPE_FLOAT;
            }
            else if(son1Type == DATATYPE_FLOAT &&
                (son0Type == DATATYPE_SHORT || son0Type == DATATYPE_LONG ||
                son0Type == DATATYPE_BYTE)){
                //Lado esquerdo é inteiro e lado direito é float
                return DATATYPE_FLOAT;
            }
            else if(son0Type == DATATYPE_DOUBLE &&
                (son1Type == DATATYPE_SHORT || son1Type == DATATYPE_LONG ||
                son1Type == DATATYPE_BYTE)){
                //Lado esquerdo é double e lado direito é inteiro
                return DATATYPE_DOUBLE;
            }
            else if(son1Type == DATATYPE_DOUBLE &&
                (son0Type == DATATYPE_SHORT || son0Type == DATATYPE_LONG ||
                son0Type == DATATYPE_BYTE)){
                //Lado esquerdo é inteiro e lado direito é double
                return DATATYPE_DOUBLE;
            }
            else if(son0Type == DATATYPE_LONG && son1Type == DATATYPE_SHORT){
                //Lado esquerdo é long e lado direito é short
                return DATATYPE_LONG;
            }
            else if(son1Type == DATATYPE_LONG && son0Type == DATATYPE_SHORT){
                //Lado direito é long e lado esquerdo é short
                return DATATYPE_LONG;
            }
            else if(son0Type == DATATYPE_SHORT && son1Type == DATATYPE_BYTE){
                //Lado esquerdo é short e lado direito é byte
                return DATATYPE_SHORT;
            }
            else if(son1Type == DATATYPE_SHORT && son0Type == DATATYPE_BYTE){
                //Lado esquerdo é byte e lado direito é short
                return DATATYPE_SHORT;
            }
            else if(son0Type == DATATYPE_LONG && son1Type == DATATYPE_BYTE){
                //Lado esquerdo é long e lado direito é byte
                return DATATYPE_LONG;
            }
            else if(son1Type == DATATYPE_LONG && son0Type == DATATYPE_BYTE){
                //Lado esquerdo é byte e lado direito é long
                return DATATYPE_LONG;
            }
            else{
                fprintf(stderr, "ERRO, expressão relaciona tipos incompatíveis\n");
                _errorStatus = 1;
                return -1;
            }
        }
        else if(node->type == AST_LESS || node->type == AST_GREATER || node->type == AST_LE || node->type == AST_GE ||
            node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR ||
            node->type == AST_NOT){
            //Expressões lógicas
            return DATATYPE_BOOLEAN;
        }
        else if(node->type == AST_EXPRESSION){
            return semanticSetOperatorsResultType(node->son[0]);
        }
        else{
            fprintf(stderr, "ERRO INTERNO EM %s\n", __FUNCTION__);
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
