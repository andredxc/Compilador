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

%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INTEGER
%token<symbol> LIT_REAL
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%type<ast> program
%type<ast> decList
%type<ast> dec
%type<ast> globalVariableDec
%type<ast> variableInfo
%type<ast> intList
%type<ast> realList
%type<ast> functionDec
%type<ast> parameterList
%type<ast> moreParameters
%type<ast> parameter
%type<ast> comand
%type<ast> comandBlock
%type<ast> moreComands
%type<ast> read
%type<ast> print
%type<ast> listElem
%type<ast> tail_listElem
%type<ast> return
%type<ast> fluxControl
%type<ast> expression
%type<ast> attribution
%type<ast> type
%type<ast> callFunc
%type<ast> listArg
%type<ast> tailArg

%token TOKEN_ERROR


%left '*' '/'
%left '-' '+'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left OPERATOR_OR OPERATOR_AND
%right '!'

%%

program: decList											{$$ = $1; /*ast = $$;*/}
	;

decList: dec decList										{$$ = astCreate(AST_CJTODEC_ELEM,0,$1,$2,0,0);}
	|														{$$ = 0;}
	;

dec: globalVariableDec										{$$ = $1;}
    | functionDec											{$$ = $1; astPrint($$, 0);}
	;

globalVariableDec: TK_IDENTIFIER ':' variableInfo ';' 		{$$ = astCreate(AST_DEC_VAR_GLOB,$1,$3,0,0,0);}
	;

variableInfo: KW_BYTE '=' LIT_CHAR							{$$ = astCreate(AST_DEC_VAR_BYTE,$3,0,0,0,0);}
	| KW_BYTE '=' LIT_INTEGER								{$$ = astCreate(AST_DEC_VAR_BYTE,$3,0,0,0,0);}
	| KW_SHORT '=' LIT_INTEGER								{$$ = astCreate(AST_DEC_VAR_SHORT,$3,0,0,0,0);}
	| KW_LONG '=' LIT_INTEGER								{$$ = astCreate(AST_DEC_VAR_LONG,$3,0,0,0,0);}
	| KW_FLOAT '=' LIT_REAL									{$$ = astCreate(AST_DEC_VAR_FLOAT,$3,0,0,0,0);}
	| KW_DOUBLE '=' LIT_REAL								{$$ = astCreate(AST_DEC_VAR_DOUBLE,$3,0,0,0,0);}
	| KW_SHORT '[' LIT_INTEGER ']' intList 					{$$ = astCreate(AST_DEC_VEC_SHORT,$3,$5,0,0,0);}
	| KW_LONG '[' LIT_INTEGER ']' intList					{$$ = astCreate(AST_DEC_VEC_LONG,$3,$5,0,0,0);}
	| KW_FLOAT '[' LIT_INTEGER ']' realList					{$$ = astCreate(AST_DEC_VEC_FLOAT,$3,$5,0,0,0);}
	| KW_DOUBLE '[' LIT_INTEGER ']' realList				{$$ = astCreate(AST_DEC_VEC_DOUBLE,$3,$5,0,0,0);}
	| KW_BYTE '[' LIT_INTEGER ']' intList					{$$ = astCreate(AST_DEC_VEC_BYTE,$3,$5,0,0,0);}
	//| KW_BYTE '[' LIT_INTEGER ']' LIT_STRING				{$$ = astCreate(AST_DEC_VEC_BYTE_STRING,$3,$1,$5,0,0);}
	;

intList: LIT_INTEGER intList								{$$ = astCreate(AST_DEC_VEC,$1,$2,0,0,0);}
	|														{$$ = 0;}
	;

realList: LIT_REAL realList									{$$ = astCreate(AST_DEC_VEC,$1,$2,0,0,0);}
	|														{$$ = 0;}
	;

functionDec: '(' type ')' TK_IDENTIFIER '(' parameterList ')' comandBlock {$$ = astCreate(AST_DEC_FUNC,$4,$2,$6,$8,0);}
    ;

parameterList: parameter moreParameters						 {$$ = astCreate(AST_DEC_PARAM_VEC,0,$1,$2,0,0);}
    |														{$$ = 0;}
    ;

moreParameters: ',' parameter moreParameters				{$$ = astCreate(AST_DEC_PARAM_VEC,0,$2,$3,0,0);}
    |														{$$ = 0;}
    ;

parameter: TK_IDENTIFIER ':' type				{$$ = astCreate(AST_DEC_PARAM,$1,$3,0,0,0);}
    ;

comand: comandBlock								{$$ = $1;}
    | fluxControl								{$$ = $1;}
    | attribution								{$$ = $1;}
    | read										{$$ = $1;}
    | return									{$$ = $1;}
    | print										{$$ = $1;}
    ;

comandBlock: '{' comand moreComands '}'			{ $$ = astCreate(AST_COMMAND_BLOCK, 0, $2, $3, 0, 0); }
    |											{$$ = 0;}
    ;

moreComands: ';' comand moreComands				{ $$ = astCreate(AST_VEC_COMMAND_BLOCK, 0, $2, $3, 0, 0); }
    |											{ $$ = 0; }
    ;

read: KW_READ '>' TK_IDENTIFIER             	{ $$ = astCreate(AST_READ, $3, 0, 0, 0, 0); }
    ;

print: KW_PRINT listElem                        { $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); }
    ;

listElem: LIT_STRING  tail_listElem             { $$ = astCreate(AST_PRINT_ARG, $1, 0, $2, 0, 0); }
    | expression tail_listElem                  { $$ = astCreate(AST_PRINT_ARG, 0, $1, $2, 0, 0); }
    ;

tail_listElem: ',' LIT_STRING tail_listElem     { $$ = astCreate(AST_PRINT_ARG, $2, 0, $3, 0, 0); }
	| ',' expression tail_listElem              { $$ = astCreate(AST_PRINT_ARG, 0, $2, $3, 0, 0); }
	|                                           { $$ = 0; }
	;

return: KW_RETURN expression                    { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }
    ;

fluxControl: KW_IF '(' expression ')' KW_THEN comand            { $$ = astCreate(AST_IF, 0, $3, $6, 0, 0); }
    | KW_IF '(' expression ')' KW_THEN comand KW_ELSE comand    { $$ = astCreate(AST_IF_ELSE, 0, $3, $6, $8, 0); }
    | KW_WHILE '(' expression ')' comand                        { $$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0); }
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
    | TK_IDENTIFIER                             { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']'          { $$ = astCreate(AST_ARRAY, $1, $3, 0, 0, 0); }
    | LIT_INTEGER                               { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_REAL                                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_CHAR                                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | callFunc                                  {$$ = $1;}
    | '!' expression                            { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
    ;

attribution: TK_IDENTIFIER '=' expression               { $$ = astCreate(AST_ATTR, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']' '=' expression   { $$ = astCreate(AST_ATTR_VEC, $1, $3, $6, 0, 0); }
    ;

type: KW_BYTE									{$$ = astCreate(AST_BYTE,0,0,0,0,0);}
    | KW_SHORT									{$$ = astCreate(AST_SHORT,0,0,0,0,0);}
    | KW_LONG									{$$ = astCreate(AST_LONG,0,0,0,0,0);}
    | KW_FLOAT									{$$ = astCreate(AST_FLOAT,0,0,0,0,0);}
    | KW_DOUBLE									{$$ = astCreate(AST_DOUBLE,0,0,0,0,0);}
    ;

callFunc: TK_IDENTIFIER '(' listArg ')'        { $$ = astCreate(AST_CALLFUNC, $1, 0, $3, 0, 0); }
    ;

listArg: expression tailArg                     { $$ = astCreate(AST_FUNC_ARG_LIST, 0, $1, $2, 0, 0); }
    |                                           { $$ = 0; }
    ;

tailArg: ',' expression tailArg                 { $$ = astCreate(AST_FUNC_ARG_LIST, 0, $2, $3, 0, 0); }
    |                                           { $$ = 0; }
    ;

%%

void yyerror(char* arg){

    fprintf(stderr, "Erro na linha %d\n", getLineNumber());
    exit(3);
}
