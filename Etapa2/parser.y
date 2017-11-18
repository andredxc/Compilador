%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "hash.h"

    extern int getLineNumber();
    int yylex();
    void yyerror(char* arg);
%}

%union{ struct hash_struct* symbol; }

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

variableInfo: variableType '=' variableValue
	| variableType '[' LIT_INTEGER ']' valueList
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
    ;

valueList: variableValue valueList
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
    |
    ;

comandBlock: '{' comand moreComands '}'
    ;

moreComands: ';' comand moreComands
    |
    ;

read: KW_READ '>' TK_IDENTIFIER
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

expression: '(' expression ')'
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '>' expression
    | expression '<' expression
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_NE expression
    | expression OPERATOR_AND expression
    | expression OPERATOR_OR expression
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | callFunc
    | '!' expression
    ;

/*expression: '(' expression ')'
    | expression operator expression
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | callFunc
    | '!' expression
    ;
*/
										;
attribution: TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' expression ']' '=' expression
    ;

type: KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;

/*operator: '*'
    | '/'
    | '+'
    | '-'
    | '>'
    | '<'
    | OPERATOR_LE
    | OPERATOR_GE
    | OPERATOR_EQ
    | OPERATOR_NE
    | OPERATOR_OR
    | OPERATOR_AND
    ;
*/

callFunc: TK_IDENTIFIER '(' listArg ')';
    ;

listArg: expression tailArg
    |
    ;

tailArg: ',' expression tailArg
    |
    ;

%%

void yyerror(char* arg){

    fprintf(stderr, "Erro sintático na linha %d\n", getLineNumber());
    exit(3);
}
