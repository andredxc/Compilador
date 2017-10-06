
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

globalVariable: TK_IDENTIFIER ':' variableType '=' variableValue ';'
            ;

variableType: KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;
    
variableValue: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | LIT_STRING
    ;



%%

int yyerror(char* arg){

    fprintf(stderr, "Erro na linha %d\n", getLineNumber());
    return 0;
}
