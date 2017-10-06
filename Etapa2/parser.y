
%{
    #include <stdio.h>

    int yyerror(char* arg);
%}

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND 
%token OPERATOR_OR
%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

%%

program: decList
	;
	
decList: dec decList
	|
	;
	
dec: globalVariableDec
	;

globalVariableDec: TK_IDENTIFIER ':' variableInfo ';'
	;

variableInfo: KW_BYTE '=' LIT_CHAR
	| KW_BYTE '=' LIT_INTEGER
	| KW_SHORT '=' LIT_INTEGER
	| KW_LONG '=' LIT_INTEGER
	| KW_FLOAT '=' LIT_REAL
	| KW_DOUBLE '=' LIT_REAL
	| KW_SHORT '[' LIT_INTEGER ']' intList
	| KW_LONG '[' LIT_INTEGER ']' intList
	| KW_FLOAT '[' LIT_INTEGER ']' realList
	| KW_DOUBLE '[' LIT_INTEGER ']' realList
	| KW_BYTE '[' LIT_INTEGER ']' intList
	| KW_SHORT '[' LIT_INTEGER ']' LIT_STRING
	;
	
intList: LIT_INTEGER intList
	|
	;
	
realList: LIT_REAL realList
	|
	;



%%

int yyerror(char* arg){

    fprintf(stderr, "Erro na linha %d\n", getLineNumber());
    return 0;
}
