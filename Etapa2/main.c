/*
* André D. Carneiro e Victória Simonetti
*/

#include <stdio.h>
#include "y.tab.h"

extern FILE* yyin;
extern int yylex();
extern int isRunning();
extern int hashPrint();
extern int initMe();

int main(int argc, char **argv  ){

	int token;

	if(argc < 2){
	    fprintf(stderr, "Uso: ./etapa2 <arquivo>\n");
	    return 1;
	}
	yyin = fopen(argv[1], "r");
	if(!yyin){
	    fprintf(stderr, "Erro abrindo arquivo\n");
	    return 1;
	}
    initMe();

    if(yyparse()){
        //Ocorreu algum erro sintático
        return 3;
    }
    else{
        fprintf(stderr, "Concluído com sucesso\n");
    }
    fprintf(stderr, "------------------hashPrint()------------------\n");
    hashPrint();
	return 0;
}
