#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include "tac.h"

void asmGenerate(TAC* first);

void asmAdd(TAC* tac, FILE* outputFile);
void asmSub(TAC* tac, FILE* outputFile);
void asmMul(TAC* tac, FILE* outputFile);
void asmDiv(TAC* tac, FILE* outputFile);
void asmMove(TAC* tac, FILE* outputFile);

void asmFunctionCall(TAC* tac, FILE* outputFile);
void asmJump(TAC* tac, FILE* outputFile);
void asmLabel(TAC* tac, FILE* outputFile);
void asmBeginFunction(TAC* tac, FILE* outputFile);
void asmRead(TAC* tac, FILE* outputFile);

void asmVardec(TAC* tac, FILE* outputFile);

void setOperators(TAC* tac, FILE* outputFile);


#endif
