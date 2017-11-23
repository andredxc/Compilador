#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

int _errorStatus;
AST_NODE* raiz;

int semanticFullCheck(AST_NODE* astree){

	raiz = astree;
    _errorStatus = 0;

    //fprintf(stderr, "%s \n", astree->symbol->symbol.text);

    semanticCheckDeclarations(astree);
    semanticCheckFunctionDeclarations(astree);
    semanticCheckAttributions(astree);
    semanticCheckFunctionCalls(raiz, astree);
    semanticCheckFunctionReturnTypes(astree);
    semanticCheckReads(astree);

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
        else if(node->type == AST_DEC_PARAM){
            //Declaração de variável como parâmetro de função
            node->symbol->symbol.nature = NATURE_VARIABLE;
            switch(node->son[0]->type){
                case AST_BYTE: node->symbol->symbol.dataType = DATATYPE_BYTE; break;
                case AST_SHORT: node->symbol->symbol.dataType = DATATYPE_SHORT; break;
                case AST_LONG: node->symbol->symbol.dataType = DATATYPE_LONG; break;
                case AST_FLOAT: node->symbol->symbol.dataType = DATATYPE_FLOAT; break;
                case AST_DOUBLE: node->symbol->symbol.dataType = DATATYPE_DOUBLE; break;
                default: fprintf(stderr, "Erro interno estranho em %s\n", __FUNCTION__);
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
        /*
        fprintf(stderr, "EXPRESSÃO ATRIBUIDA A [%s] É: ", node->symbol->symbol.text);
        switch (expDataType){
            case DATATYPE_SHORT:fprintf(stderr, "SHORT\n"); break;
            case DATATYPE_LONG:fprintf(stderr, "LONG\n"); break;
            case DATATYPE_FLOAT:fprintf(stderr, "FLOAT\n"); break;
            case DATATYPE_DOUBLE:fprintf(stderr, "DOUBLE\n"); break;
            case DATATYPE_BYTE:fprintf(stderr, "BYTE\n"); break;
            default: fprintf(stderr, "NÃO DEFINIDA\n");
        }
        */
    }
    else if(node->type == AST_ATTR_VEC){
        //Atribuição a vetores

        //Determina a validade do lado esquerdo
        arrayIndexDataType = semanticSetOperatorsResultType(node->son[0]);
        if(node->symbol->symbol.nature < 0){
            fprintf(stderr, "ERRO, o vetor [%s] não foi declarado\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(node->symbol->symbol.nature == NATURE_VARIABLE){
            fprintf(stderr, "ERRO, [%s] é uma variável, não pode ser usada como um vetor\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(node->symbol->symbol.nature == NATURE_FUNCTION){
            fprintf(stderr, "ERRO, [%s] é uma função, não pode ser usada como um vetor\n", node->symbol->symbol.text);
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
            else if(node->symbol->symbol.type == LIT_CHAR){
                fprintf(stderr, "ERRO, uso indevido do caractere [%s]\n", node->symbol->symbol.text);
                _errorStatus = 1;
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
            fprintf(stderr, "ERRO INTERNO EM %s, entrou com node->type: %d\n", __FUNCTION__, node->type);
        }
    }
}

void semanticCheckFunctionCalls(AST_NODE* raiz, AST_NODE* node){

    int i;

    if(!node){
        return;
    }

    if(node->type == AST_CALLFUNC){

        //Verifica se a função foi declarada como função
        if(node->symbol->symbol.nature != NATURE_FUNCTION){
            if(node->symbol->symbol.nature < 0){
                fprintf(stderr, "ERRO, [%s] não foi declarada\n", node->symbol->symbol.text);
            }
            else{
                fprintf(stderr, "ERRO, [%s] não é uma função\n", node->symbol->symbol.text);
            }
            _errorStatus = 1;
        }else{
			verifyParams(raiz, node);
		}
    }

    for(i = 0; i < MAX_SONS; i++){
        semanticCheckFunctionCalls(raiz, node->son[i]);
    }
}

/* Contabiliza o número de parâmetros passados/declarados de uma função. */
int countFuncNumParams(AST_NODE *node){
	if(!node){
		return 0;
	}else{
		return 1 + countFuncNumParams(node->son[1]);
	}
}

/* Verifica se o parâmetro tem o mesmo número de itens da declaração e se os tipos são compatíveis. */
void verifyParams(AST_NODE* raiz, AST_NODE* node){

	int numParam = 0;
	// caso a função tenha algum parâmetro, contar o numero de parametros e verificar os tipos
	int correct_n_par = node-> symbol->symbol.numParams;
	numParam = countFuncNumParams(node->son[0]);
	if(numParam != correct_n_par){
		fprintf(stderr, "Número inválido de parâmetros na chamada da função [%s]\n", node->symbol->symbol.text);
		_errorStatus = 1;
	}else{
		if(node->son[0]){
			verifyTypeFuncCallParams(raiz, node);
		}
	}
}

/* Verifica se os tipos dos parametros passados em uma FUNCAO são compativeis com a declaração. */
void verifyTypeFuncCallParams(AST_NODE* raiz, AST_NODE* function){

	AST_NODE* aux = raiz;
    int tipoDeclaradoFunc;
    int tipoPassadoParam;

	//Encontra a função declarada na árvore
	while(raiz->son[0]->symbol->symbol.text != function->symbol->symbol.text){
		raiz = raiz->son[1];
	}
	raiz = raiz->son[0]->son[1];

	function = function->son[0];
	while(function){

        tipoDeclaradoFunc = raiz->son[0]->son[0]->type;
        tipoPassadoParam = semanticSetOperatorsResultType(function->son[0]);
        /*Faz casamento de tipos dos parâmetros passados para a função com o que foi declarado */
        verificaCompatibilidade(tipoDeclaradoFunc, tipoPassadoParam);
        //fprintf(stderr, "raiz->text: <%s> raiz->dataType: <%d> \n", raiz->son[0]->symbol->symbol.text, raiz->son[0]->son[0]->type);
		function = function->son[1];
		raiz = raiz->son[1];
	}
}

void verificaCompatibilidade(int tipoDeclaradoFunc, int tipoPassadoParam){

    if (tipoPassadoParam == DATATYPE_BOOLEAN){
		fprintf(stderr, "ERRO: expressão booleana em parâmetro de função.\n");
		_errorStatus = 1;
	}

    int paramIsReal = 0; //parametro passado default: SIM é real
    int declFuncIsReal = 0; //parametro passado default: SIM é real
    /*inteiros compativeis: DATATYPE_SHORT=1 DATATYPE_LONG=2 DATATYPE_BYTE=5
      reais compativeis: DATATYPE_FLOAT=3 DATATYPE_DOUBLE=4  */

    // seta que o tipo passado por parâmetro é inteiro
    if(tipoPassadoParam == DATATYPE_SHORT || tipoPassadoParam == DATATYPE_LONG || tipoPassadoParam == DATATYPE_BYTE){
       paramIsReal = 1; //tipo passado NÃO é real, logo, é inteiro
    }

    if(tipoDeclaradoFunc == AST_SHORT || tipoDeclaradoFunc == AST_LONG || tipoDeclaradoFunc == AST_BYTE){
        declFuncIsReal = 1; //tipo declarado NÃO é real, logo, é inteiro
    }


    if(paramIsReal != declFuncIsReal){
		fprintf(stderr, "ERRO: tipo de parâmetro de função não compatível com o passado.\n");
        _errorStatus = 1;
    }
    
}

void semanticCheckFunctionReturnTypes(AST_NODE* node){

    int i;
    AST_NODE *nodeBuffer;

    if(!node){
        return;
    }

    if(node->type == AST_DEC_FUNC){
        //Verifica se o dataType do valor retornado corresponde ao da função
        //nodeBuffer recebe o commandBlock da função
        nodeBuffer = node->son[2];
        while(nodeBuffer){
            //Dentro do comandBlock
            if(nodeBuffer->son[0] && nodeBuffer->son[0]->type == AST_RETURN){
                if(semanticSetOperatorsResultType(nodeBuffer->son[0]->son[0]) == DATATYPE_BOOLEAN){
                    fprintf(stderr, "ERRO, return não compatível com o tipo da função [%s]\n", node->symbol->symbol.text);
                    _errorStatus = 1;
                }
                return;
            }
            else{
                nodeBuffer = nodeBuffer->son[1];
            }
        }
    }

    for(i = 0; i< MAX_SONS; i++){
        semanticCheckFunctionReturnTypes(node->son[i]);
    }
}

void semanticCheckReads(AST_NODE* node){

    int i;

    if(!node){
        return;
    }

    if(node->type == AST_READ){
        if(node->symbol->symbol.nature == NATURE_ARRAY){
            fprintf(stderr, "ERRO, o vetor [%s] não pode ser usado na instrução read\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(node->symbol->symbol.nature == NATURE_FUNCTION){
            fprintf(stderr, "ERRO, a função [%s] não pode ser usada na instrução read\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
        else if(node->symbol->symbol.nature != NATURE_VARIABLE){
            fprintf(stderr, "ERRO, [%s] não pode ser usada na instrução read\n", node->symbol->symbol.text);
            _errorStatus = 1;
        }
    }

    for(i = 0; i < MAX_SONS; i++){
        semanticCheckReads(node->son[i]);
    }
}
