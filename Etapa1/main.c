#include <stdio.h>

#include "tokens.h"

extern FILE* yyin;
extern int yylex();
extern int isRunning();

int main(){

	int token;

	yyin = fopen("teste.ling", "r");

	while(isRunning()){

		token = yylex();
		switch (token) {

			case KW_BYTE:
				fprintf(stderr, "KW_BYTE\n");
				break;
			case KW_SHORT:
				fprintf(stderr, "KW_SHORT\n");
				break;
			case KW_LONG:
				fprintf(stderr, "KW_LONG\n");
				break;
			case KW_FLOAT:
				fprintf(stderr, "KW_FLOAT\n");
				break;
			case KW_DOUBLE:
				fprintf(stderr, "KW_DOUBLE\n");
				break;
			case KW_WHEN:
				fprintf(stderr, "KW_WHEN\n");
				break;
			case KW_THEN:
				fprintf(stderr, "KW_THEN\n");
				break;
			case KW_ELSE:
				fprintf(stderr, "KW_ELSE\n");
				break;
			case KW_WHILE:
				fprintf(stderr, "KW_WHILE\n");
				break;
			case KW_FOR:
				fprintf(stderr, "KW_FOR\n");
				break;
			case KW_READ:
				fprintf(stderr, "KW_READ\n");
				break;
			case KW_RETURN:
				fprintf(stderr, "KW_RETURN\n");
				break;
			case KW_PRINT :
				fprintf(stderr, "KW_PRINT\n");
				break;
			case OPERATOR_LE  :
				fprintf(stderr, "OPERATOR_LE\n");
				break;
			case OPERATOR_GE  :
				fprintf(stderr, "OPERATOR_GE\n");
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "OPERATOR_EQ\n");
				break;
			case OPERATOR_NE:
				fprintf(stderr, "OPERATOR_NE\n");
				break;
			case OPERATOR_AND:
				fprintf(stderr, "OPERATOR_AND\n");
				break;
			case OPERATOR_OR:
				fprintf(stderr, "OPERATOR_OR\n");
				break;
			case TK_IDENTIFIER:
				fprintf(stderr, "TK_IDENTIFIER\n");
				break;
			case LIT_INTEGER:
				fprintf(stderr, "LIT_INTEGER\n");
				break;
			case LIT_REAL:
				fprintf(stderr, "LIT_REAL\n");
				break;
			case LIT_CHAR:
				fprintf(stderr, "LIT_CHAR\n");
				break;
			case LIT_STRING:
				fprintf(stderr, "LIT_STRING\n");
				break;
			default:
				fprintf(stderr, "OPERATOR\n");
		}
		//fprintf(stderr, "tok = %d\n", token);
	}

	return 1;
}
