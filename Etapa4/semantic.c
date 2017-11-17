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

                //Verifica se o número de elementos é um inteiro
                if(node->son[0]->symbol->symbol.type == LIT_INTEGER){
                    arraySize = atoi(node->son[0]->symbol->symbol.text);
                    if(arraySize == 0){
                        fprintf(stderr, "ERRO na linha, vetor declarado com tamanho 0\n");
                        _errorStatus = 1;
                    }
                    else{
                        //fprintf(stderr, "ARRAYSIZE: %d\n", arraySize);
                        //Verifica o número de valores dados para o vetor
                        astBuffer = node->son[0]->son[0];
                        for(i = 0; i < arraySize; i++){
                            if(!astBuffer){
                                fprintf(stderr, "ERRO na linha, número incorreto de argumentos para o vetor\n");
                                _errorStatus = 1;
                            }
                            else{
                                //fprintf(stderr, "INDICE %d, VALOR %s\n", i, astBuffer->symbol->symbol.text);
                                astBuffer = astBuffer->son[0];
                            }
                        }
                    }
                }
                else{
                    fprintf(stderr, "ERRO na linha %d, número de elementos do vetor deve ser inteiro\n", 0);
                }
            }

            else{
                fprintf(stderr, "ERRO na linha %d, tipo incorreto na variável %s\n", 0, node->symbol->symbol.text);
                _errorStatus = 1;
            }
        }

        for(i=0; i < MAX_SONS; i++){
            semanticCheckDeclarations(node->son[i]);
        }
    }
}
