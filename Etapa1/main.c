#include <stdio.h>

extern FILE* yyin;
extern int yylex();
extern int isRunning();

int main(){

	int tok;

	yyin = fopen("teste.ling", "r");

	while(isRunning()){

		tok = yylex();
		fprintf(stderr, "tok = %d\n", tok);
	}

	return 1;
}
