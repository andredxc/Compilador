#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "astree.h"

int semanticFullCheck(AST_NODE* astree);
void semanticCheckDeclarations(AST_NODE* astree);
void semanticCheckFunctionDeclarations(AST_NODE* node);

#endif
