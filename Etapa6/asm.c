
#include <ctype.h>
#include "asm.h"

int _printNumber = 0;

void asmGenerate(TAC* first){

	FILE* outputFile;
	TAC* tac;

	outputFile = fopen("output.asm", "w");

	if(!outputFile){
		fprintf(stderr, "Erro abrindo arquivo de saída\n");
		return;
	}

	for(tac = first; tac; tac = tac->next){

		switch(tac->type){

			case TAC_SYMBOL: break;
			case TAC_ADD: asmAdd(tac, outputFile); break;
			case TAC_SUB: asmSub(tac, outputFile); break;
			case TAC_MUL: asmMul(tac, outputFile); break;
			case TAC_DIV: asmDiv(tac, outputFile); break;
			case TAC_LESS: break;
			case TAC_GREATER: break;
			case TAC_LE: break;
			case TAC_GE: break;
			case TAC_EQ: break;
			case TAC_NE: break;
			case TAC_AND: break;
			case TAC_OR: break;
			case TAC_NOT: break;
			case TAC_VEC_READ: break;
			case TAC_MOVE: asmMove(tac, outputFile); break;
			case TAC_IFZ: break;
			case TAC_LABEL: asmLabel(tac, outputFile); break;
			case TAC_JMP: asmJump(tac, outputFile); break;
			case TAC_RETURN: break;
			case TAC_VARDEC: asmVardec(tac, outputFile); break;
			case TAC_VECDEC: break;
			case TAC_READ: asmRead(tac, outputFile); break;
			case TAC_PRINT: break;
			case TAC_PRINT_ARG: break;
			case TAC_BEGINFUNC: asmBeginFunction(tac, outputFile); break;
			case TAC_ENDFUNC: break;
			case TAC_PARAM: break;
			case TAC_CALL: asmFunctionCall(tac, outputFile); break;
			case TAC_ARG: /*ignore*/ break;
			case TAC_VEC_WRITE: break;
		}
	}
    fclose(outputFile);
}

void asmAdd(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "\n## TAC_ADD\n");

	setOperators(tac, outputFile);
	if(tac->op1 && tac->op2 && tac->res){
		fprintf(outputFile, "\taddl	%%edx, %%eax\n\tmovl %%eax, %s(%%rip)\n", tac->res->symbol.text);
	}else{
		fprintf(stderr, "Erro interno em asmAdd");
	}
}

void asmSub(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "\n## TAC_SUB\n");
	setOperators(tac, outputFile);
	if(tac->op1 && tac->op2 && tac->res){
		fprintf(outputFile, "\tsubl	%%eax, %%edx\n\tmovl %%edx, %%eax\n\tmovl %%eax, %s(%%rip)\n", tac->res->symbol.text);
	}
	else{
		fprintf(stderr, "Erro interno em asmSub");
	}
}

void asmMul(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "\n## TAC_MUL\n");
	setOperators(tac, outputFile);
	if(tac->op1 && tac->op2 && tac->res){
		fprintf(outputFile, "\timull %%edx, %%eax\n\tmovl %%eax, %s(%%rip)\n", tac->res->symbol.text);
	}
	else{
		fprintf(stderr, "Erro interno em asmMul");
	}
}

void asmDiv(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "\n## TAC_DIV\n");
	if(tac->op1 && tac->op2 && tac->res){
		if(isdigit(tac->op1->symbol.text[0]) && isdigit(tac->op2->symbol.text[0])){
			// Dois valores imediatos
		}
	}
	else{
		fprintf(stderr, "Erro interno em asmMul");
	}
}

void asmJump(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "\n## TAC_JUMP\n");
    fprintf(outputFile, "\tjmp .%s\n", tac->res->symbol.text);
}

void asmFunctionCall(TAC* tac, FILE* outputFile){

    TAC* paramTemp = tac;

    fprintf(outputFile, "\n## TAC_CALL\n");

    paramTemp = tac->prev;
    while(paramTemp->type == TAC_ARG || paramTemp->type == TAC_SYMBOL){
        // Coloca todos os parâmetros no arquivo
        if(paramTemp->type == TAC_ARG){
            if(isdigit(paramTemp->res->symbol.text[0])){
                // Valor imediato
                fprintf(outputFile, "\tmovl $%s, %%eax\n\tmovl %%eax, %s(%%rip)\n", paramTemp->res->symbol.text, tac->op1->symbol.text);
            }
            else{
                // Variável
                fprintf(outputFile, "\tmovl %s(%%rip), %%eax\n\tmovl %%eax, %s(%%rip)\n", paramTemp->res->symbol.text, tac->op1->symbol.text);
            }
        }
        paramTemp = paramTemp->prev;
    }

    fprintf(outputFile, "\tmovl $0, %%eax\n\tcall %s\n\tmovl %%eax, %s(%%rip)\n", tac->op1->symbol.text, tac->res->symbol.text);
}

void asmMove(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "\n## TAC_MOVE\n");

	if(isdigit(tac->op1->symbol.text[0])){
		//Valor imediato
		fprintf(outputFile, "\tmovl	$%s, %s(%%rip)\n", tac->op1->symbol.text, tac->res->symbol.text);
	}
	else{
		fprintf(outputFile, "\tmovl	%s(%%rip), %%eax\n\tmovl %%eax, %s(%%rip)\n", tac->op1->symbol.text, tac->res->symbol.text);
	}
}

void asmLabel(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "\n## TAC_LABEL\n");
    fprintf(outputFile, ".%s:\n", tac->res->symbol.text);
}

void asmRead(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "\n##TAC_READ\n");
    if(tac->res->symbol.dataType == DATATYPE_FLOAT || tac->res->symbol.dataType == DATATYPE_DOUBLE){
        fprintf(outputFile,".LC%d:\n\t.string \"%%f\"\n", _printNumber);
    }
    else{
        fprintf(outputFile,".LC%d:\n\t.string \"%%d\"\n", _printNumber);
    }
    fprintf(outputFile,"\tmovl $%s, %%esi\n\tmovl $.LC%d, %%edi\n\tmovl $0, %%eax\n\tcall __isoc99_scanf\n", tac->res->symbol.text, _printNumber);
    _printNumber++;
}

void asmBeginFunction(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "\n## TAC_BEGINFUNC\n");
    fprintf(outputFile, "\t.globl %s\n\t.type %s, @function\n%s:\n\tpushq %%rbp\n\tmovq	%%rsp, %%rbp\n",tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text);
}

void asmVardec(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "\n## TAC_VARDEC\n");

    if(tac->op1->symbol.type == SYMBOL_LIT_REAL){
        //Número real
        fprintf(outputFile, "\t.globl %s\n\t.type %s, @object\n\t.size %s, 4\n%s:\n\t.long 111111\n", tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text);
    }
    else if(tac->op1->symbol.type == SYMBOL_LIT_CHAR){
        //Char
        char charValue[5];
        sprintf(charValue , "%d", tac->op1->symbol.text[1]);
        fprintf(outputFile, "\t.globl %s\n\t.type %s, @object\n\t.size %s, 1\n%s:\n\t.byte %s\n",  tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text, charValue);
    }
    else{
        //Inteiro
        fprintf(outputFile, "\t.globl %s\n\t.type %s, @object\n\t.size %s, 4\n%s:\n\t.long %s\n", tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text,tac->res->symbol.text, tac->op1->symbol.text);
    }
}

void setOperators(TAC* tac, FILE* outputFile){

  	// Coloca op1 em edx e o op2 em eax
	if(isdigit(tac->op1->symbol.text[0])){
		fprintf(outputFile, "\tmovl $%s, %%edx\n", tac->op1->symbol.text);
	}else{
		fprintf(outputFile, "\tmovl	%s(%%rip), %%edx\n", tac->op1->symbol.text);
  	}

	if(isdigit(tac->op2->symbol.text[0])){
		fprintf(outputFile, "\tmovl	$%s, %%eax\n", tac->op2->symbol.text);
	}
	else{
		fprintf(outputFile, "\tmovl	%s(%%rip), %%eax\n", tac->op2->symbol.text);
	}
}
