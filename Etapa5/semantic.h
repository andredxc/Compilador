#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "astree.h"

int semanticFullCheck(AST_NODE* astree);
void semanticCheckDeclarations(AST_NODE* astree);
void semanticCheckFunctionDeclarations(AST_NODE* node);
void semanticCheckAttributions(AST_NODE* node);
int semanticSetOperatorsResultType(AST_NODE* node);
void semanticCheckFunctionCalls(AST_NODE* raiz, AST_NODE* node);
void verifyParams(AST_NODE* raiz, AST_NODE* node);
int countFuncNumParams(AST_NODE *node);
void verifyTypeFuncCallParams(AST_NODE* raiz, AST_NODE* function);
void semanticCheckFunctionReturnTypes(AST_NODE* node);
void semanticCheckReads(AST_NODE* node);
void verificaCompatibilidade(int tipoDeclaradoFunc, int tipoPassadoParam);

#endif
