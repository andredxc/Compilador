/*
* André D. Carneiro e Victória Simonetti
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"
#include "semantic.h"
#include "tac.h"

extern FILE* yyin;
extern int yylex();
extern int isRunning();
extern int initMe();

void main(int argc, char **argv  ){

	int token;

	if(argc < 2){
	    fprintf(stderr, "Uso: ./executavel <arquivo>\n");
	    exit(1);
	}
	yyin = fopen(argv[1], "r");
	if(!yyin){
	    fprintf(stderr, "Erro abrindo arquivo de entrada\n");
	    exit(1);
	}
    initMe();
    yyparse();

	//hashPrint();
    astPrint(ast, 0);

    if(semanticFullCheck(ast) != 0){
        //Erro semântico
        fprintf(stderr, "Erro semântico\n");
        exit(4);
    }

    tacPrintBack(tacGenerate(ast));

    fprintf(stderr, "Concluído com sucesso\n");
	exit(0);
}
