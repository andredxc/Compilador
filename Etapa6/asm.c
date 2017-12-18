#include "asm.h"


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
			case TAC_MOVE: break;
			case TAC_IFZ: break;
			case TAC_LABEL: break;
			case TAC_JMP: break;
			case TAC_RETURN: break;
			case TAC_VARDEC: break;
			case TAC_VECDEC: break;
			case TAC_READ: break;
			case TAC_PRINT: break;
			case TAC_PRINT_ARG: break;
			case TAC_BEGINFUNC: break;
			case TAC_ENDFUNC: break;
			case TAC_PARAM: break;
			case TAC_CALL: break;
			case TAC_ARG: break;
			case TAC_VEC_WRITE: break;
		}
	}
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

void setOperators(TAC* tac, FILE* outputFile){

  	// Coloca op1 em edx e o op2 em eax
	if(isdigit(tac->op1->symbol.text[0])){
		fprintf(outputFile, "\tmovl	$%s, %%edx\n", tac->op1->symbol.text);
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
