
#include <ctype.h>
#include "asm.h"

int _printNumber = 0;

void asmGenerate(TAC* first){

	FILE* outputFile;
	TAC* tac;

	outputFile = fopen("output.s", "w");

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
			case TAC_ENDFUNC: asmEndFunction(tac, outputFile); break;
			case TAC_PARAM: break;
			case TAC_CALL: asmFunctionCall(tac, outputFile); break;
			case TAC_ARG: /*ignore*/ break;
			case TAC_VEC_WRITE: break;
		}
	}
    fclose(outputFile);
}

void asmAdd(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "## TAC_ADD\n");

    setOperators(tac, outputFile);
    fprintf(outputFile, "\taddl\t%%edx, %%eax\n\tmovl\t%%eax, %s(%%rip)", tac->res->symbol.text);
}

void asmSub(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "## TAC_SUB\n");

    setOperators(tac, outputFile);
    fprintf(outputFile, "\tsubl\t%%edx, %%eax\n\tmovl\t%%eax, %s(%%rip)", tac->res->symbol.text);
}

void asmMul(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "## TAC_MUL\n");

    setOperators(tac, outputFile);
    fprintf(outputFile, "\tsubl\t%%edx, %%eax\n\tmovl\t%%eax, %s(%%rip)", tac->res->symbol.text);
}

void asmDiv(TAC* tac, FILE* outputFile){

	fprintf(outputFile, "## TAC_DIV\n");

    fprintf(outputFile, "\tmovl\t%s(%%rip), %%eax\n\tmovl\t%s(%%rip), %%ecx\n\tcltd\n\tidivl\t%%ecx\n\tmovl\t%%eax, %s(%%rip)", tac->op1->symbol.text, tac->op2->symbol.text, tac->res->symbol.text);
}

/**/
void asmJump(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "## TAC_JUMP\n");
    fprintf(outputFile, "\tjmp .%s\n", tac->res->symbol.text);
}

/**/
void asmFunctionCall(TAC* tac, FILE* outputFile){

    TAC* paramTemp = tac;

    fprintf(outputFile, "## TAC_CALL\n");

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

	fprintf(outputFile, "## TAC_MOVE\n");

	if(isdigit(tac->op1->symbol.text[0])){
		//Valor imediato
		fprintf(outputFile, "\tmovl\t$%s, %s(%%rip)\n", tac->op1->symbol.text, tac->res->symbol.text);
	}
	else{
		fprintf(outputFile, "\tmovl\t%s(%%rip), %%eax\n\tmovl\t%%eax, %s(%%rip)\n", tac->op1->symbol.text, tac->res->symbol.text);
	}
}

void asmLabel(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "## TAC_LABEL\n");
    fprintf(outputFile, ".%s:\n", tac->res->symbol.text);
}

/**/
void asmRead(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "##TAC_READ\n");
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

	static int beginFunctionCount = 0;
    fprintf(outputFile, "## TAC_BEGINFUNC\n");
    fprintf(outputFile, "\t.globl\t%s\n\t.type\t%s, @function\n%s:\n.LFB%d:\n\t.cfi_startproc\n\tpushq\t%%rbp\n\t.cfi_def_cfa_offset\t16\n\t.cfi_offset\t6, -16\n\tmovq\t%%rsp, %%rbp\n\t.cfi_def_cfa_register\t6\n", tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, beginFunctionCount);
    beginFunctionCount++;
}

void asmEndFunction(TAC* tac, FILE* outputFile){

	static int endFunctionCount = 0;

	fprintf(outputFile, "## TAC_ENDFUNC\n");
	fprintf(outputFile, "\tnop\n\tpopq\t%%rbp\n\t.cfi_def_cfa 7, 8\n\tret\n\t.cfi_endproc\n.LFE%d:\n\t.size\t%s, %s\n", endFunctionCount, tac->res->symbol.text, tac->res->symbol.text);
	endFunctionCount++;
}

void asmVardec(TAC* tac, FILE* outputFile){

    fprintf(outputFile, "## TAC_VARDEC\n");

    if(tac->op1->symbol.type == SYMBOL_LIT_REAL){
        //Número real
        fprintf(outputFile, "\t.globl\t%s\n\t.align\t4\n\t.type\t%s, @object\n\t.size\t%s, 4\n%s:\n\t.long\t1066192077\n", tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text);
    }
    else if(tac->op1->symbol.type == SYMBOL_LIT_CHAR){
        //Char
        char charValue[5];
        if(tac->op1->symbol.text[0] == '\''){
			// Se a variável foi inicializada com um caractere
			snprintf(charValue, sizeof(charValue), "%d", tac->op1->symbol.text[1]);
		}
		else{
			// Inicializada com um número
			snprintf(charValue, sizeof(charValue), "%s", tac->op1->symbol.text);
		}
        fprintf(outputFile, "\t.globl\t%s\n\t.type\t%s, @object\n\t.size\t%s, 1\n%s:\n\t.byte\t%s\n", tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, charValue);
    }
    else{
        //Inteiro
        fprintf(outputFile, "\t.globl	%s\n\t.align\t4\n\t.type\t%s, @object\n\t.size\t%s, 4\n%s:\n\t.long\t%s\n", tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, tac->res->symbol.text, tac->op1->symbol.text);
    }
}

void setOperators(TAC* tac, FILE* outputFile){

  	// Coloca op1 em edx e o op2 em eax
	if(isdigit(tac->op1->symbol.text[0])){
        // Imediato
		fprintf(outputFile, "\tmovl\t$%s, %%edx\n", tac->op1->symbol.text);
	}else{
		fprintf(outputFile, "\tmovl\t%s(%%rip), %%edx\n", tac->op1->symbol.text);
  	}

	if(isdigit(tac->op2->symbol.text[0])){
        // Imediato
		fprintf(outputFile, "\tmovl\t$%s, %%eax\n", tac->op2->symbol.text);
	}
	else{
		fprintf(outputFile, "\tmovl\t%s(%%rip), %%eax\n", tac->op2->symbol.text);
	}
}
