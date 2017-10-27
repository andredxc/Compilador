/*
* André D. Carneiro e Victória Simonetti
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

extern FILE* yyin;
extern int yylex();
extern int isRunning();
extern int initMe();

void main(int argc, char **argv  ){

	int token;

	if(argc < 2){
	    fprintf(stderr, "Uso: ./etapa2 <arquivo>\n");
	    exit(1);
	}
	yyin = fopen(argv[1], "r");
	if(!yyin){
	    fprintf(stderr, "Erro abrindo arquivo\n");
	    exit(1);
	}
    initMe();
    yyparse();
    fprintf(stderr, "Concluído com sucesso\n");
    fprintf(stderr, "------------------hashPrint()------------------\n");
    hashPrint();
	exit(0);
}
