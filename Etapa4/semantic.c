#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

int _errorStatus;

int semanticFullCheck(AST_NODE* astree){

    _errorStatus = 0;

    semanticCheckDeclarations(astree);
}

void semanticCheckDeclarations(AST_NODE* node){

    int i;
    int arraySize;
    AST_NODE* astBuffer;

    if(node){

        if(node->type == AST_DEC_VAR_GLOB){

            if(node->symbol->symbol.isDeclared != 0){
                fprintf(stderr, "ERRO, variável %s já foi declarada\n", node->symbol->symbol.text);
                _errorStatus = 1;
            }

            //Declaração de variável global
            if(node->son[0]->type == AST_DEC_VAR_SHORT && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_SHORT;
                node->symbol->symbol.nature = NATURE_VARIABLE;
                node->symbol->symbol.isDeclared = 1;
            }
            else if(node->son[0]->type == AST_DEC_VAR_LONG && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_LONG;
                node->symbol->symbol.nature = NATURE_VARIABLE;
                node->symbol->symbol.isDeclared = 1;
            }
            else if(node->son[0]->type == AST_DEC_VAR_BYTE && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL || node->son[0]->symbol->symbol.type == LIT_CHAR)){
                node->symbol->symbol.dataType = DATATYPE_BYTE;
                node->symbol->symbol.nature = NATURE_VARIABLE;
                node->symbol->symbol.isDeclared = 1;
            }
            else if(node->son[0]->type == AST_DEC_VAR_FLOAT && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_FLOAT;
                node->symbol->symbol.nature = NATURE_VARIABLE;
                node->symbol->symbol.isDeclared = 1;
            }
            else if(node->son[0]->type == AST_DEC_VAR_DOUBLE && (node->son[0]->symbol->symbol.type == LIT_INTEGER || node->son[0]->symbol->symbol.type == LIT_REAL)){
                node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                node->symbol->symbol.nature = NATURE_VARIABLE;
                node->symbol->symbol.isDeclared = 1;
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
                    node->symbol->symbol.isDeclared = 1;
                }
                else if(node->son[0]->type == AST_DEC_VEC_LONG){
                    node->symbol->symbol.dataType = DATATYPE_LONG;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                    node->symbol->symbol.isDeclared = 1;
                }
                else if(node->son[0]->type == AST_DEC_VEC_FLOAT){
                    node->symbol->symbol.dataType = DATATYPE_FLOAT;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                    node->symbol->symbol.isDeclared = 1;
                }
                else if(node->son[0]->type == AST_DEC_VEC_DOUBLE){
                    node->symbol->symbol.dataType = DATATYPE_DOUBLE;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                    node->symbol->symbol.isDeclared = 1;
                }
                else if(node->son[0]->type == AST_DEC_VEC_BYTE){
                    node->symbol->symbol.dataType = DATATYPE_BYTE;
                    node->symbol->symbol.nature = NATURE_ARRAY;
                    node->symbol->symbol.isDeclared = 1;
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
