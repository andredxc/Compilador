%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "astree.h"
    #include "hash.h"

    extern int getLineNumber();
    int yylex();
    void yyerror(char* arg);
%}

%union{
    HASH_NODE* symbol;
    AST_NODE* ast;
}

%type <ast> expression
%type <ast> callFunc
%type <ast> read
%type <ast> attribution
%type <ast> listArg

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

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR


%left '*' '/'
%left '-' '+'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left OPERATOR_OR OPERATOR_AND
%right '!'

%%

program: decList
	;

decList: dec decList
	|
	;

dec: globalVariableDec
    | functionDec
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

functionDec: '(' type ')' TK_IDENTIFIER '(' parameterList ')' comandBlock
    ;

parameterList: parameter moreParameters
    |
    ;

moreParameters: ',' parameter moreParameters
    |
    ;

parameter: TK_IDENTIFIER ':' type
    ;

comand: comandBlock
    | fluxControl
    | attribution
    | read
    | return
    | print
    ;

comandBlock: '{' comand moreComands '}'
    |
    ;

moreComands: ';' comand moreComands
    |
    ;

read: KW_READ '>' TK_IDENTIFIER             { $$ = astCreate(AST_READ, $3, 0, 0, 0, 0); }
    ;

print: KW_PRINT listElem
    ;

listElem: LIT_STRING  tail_listElem
            | expression tail_listElem
            ;

tail_listElem: ',' LIT_STRING tail_listElem
			| ',' expression tail_listElem
			|
			;

return: KW_RETURN expression
    ;

fluxControl: KW_IF '(' expression ')' KW_THEN comand
    | KW_IF '(' expression ')' KW_THEN comand KW_ELSE comand
    | KW_WHILE '(' expression ')' comand
    ;

expression: '(' expression ')'                  { $$ = $2; }
    | expression '+' expression                 { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
    | expression '-' expression                 { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
    | expression '*' expression                 { $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0); }
    | expression '/' expression                 { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
    | expression '>' expression                 { $$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0); }
    | expression '<' expression                 { $$ = astCreate(AST_LESS, 0, $1, $3, 0, 0); }
    | expression OPERATOR_LE expression         { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
    | expression OPERATOR_GE expression         { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
    | expression OPERATOR_EQ expression         { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
    | expression OPERATOR_NE expression         { $$ = astCreate(AST_NE, 0, $1, $3, 0, 0); }
    | expression OPERATOR_AND expression        { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
    | expression OPERATOR_OR expression         { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
    | TK_IDENTIFIER                             { $$ = astCreate(AST_IDENTIFIER, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']'          { $$ = astCreate(AST_ARRAY, $1, $3, 0, 0, 0); }
    | LIT_INTEGER                               { $$ = astCreate(AST_LITINT, $1, 0, 0, 0, 0); }
    | LIT_REAL                                  { $$ = astCreate(AST_LITREAL, $1, 0, 0, 0, 0); }
    | LIT_CHAR                                  { $$ = astCreate(AST_LITCHAR, $1, 0, 0, 0, 0); }
    | callFunc                                  { $$ = astCreate(AST_CALLFUNC, 0, $1, 0, 0, 0); }
    | '!' expression                            { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
    ;

attribution: TK_IDENTIFIER '=' expression               { astPrint($3, 0); }
    | TK_IDENTIFIER '[' expression ']' '=' expression
    ;

type: KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;

callFunc: TK_IDENTIFIER '(' listArg ')'        { $$ = astCreate(AST_CALLFUNC, $1, 0, $3, 0, 0); }
    ;

listArg: expression tailArg
    |
    ;

tailArg: ',' expression tailArg
    |
    ;

%%

void yyerror(char* arg){

    fprintf(stderr, "Erro na linha %d\n", getLineNumber());
    exit(3);
}
