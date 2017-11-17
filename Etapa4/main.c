/*
* André D. Carneiro e Victória Simonetti
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"
#include "semantic.h"

extern FILE* yyin;
extern int yylex();
extern int isRunning();
extern int initMe();

void main(int argc, char **argv  ){

	int token;

	if(argc < 3){
	    fprintf(stderr, "Uso: ./etapa3 <arquivo> <saida>\n");
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

	//hashPrint();
	FILE* output = fopen(argv[2], "w+");

	if(output == NULL){
		fprintf(stderr, "%s", "Can't open output file. \n");
        fclose(output);
		exit(1);
	}

	astreeProgram(ast,output);
    if(semanticFullCheck(ast) != 0){
        //Erro semântico
        fclose(output);
        exit(4);
    }
	fclose(output);
	exit(0);
}
