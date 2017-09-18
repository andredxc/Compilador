%{

    #include <stdio.h>
	#include <string.h>
    #include "tokens.h"
    #include "hash.h"

    int isRunning();
    int getLineNumber();

    int running = 1;
    int lineNumber = 1;
%}

%x COMMENT

%%

[ \t]                       {  }
[\n]                        { lineNumber++; }



"byte"                      { return KW_BYTE; }
"short"                     { return KW_SHORT; }
"long"                      { return KW_LONG; }
"float"                     { return KW_FLOAT; }
"double"                    { return KW_DOUBLE; }
"if"                        { return KW_IF; }
"then"                      { return KW_THEN; }
"else"                      { return KW_ELSE; }
"while"                     { return KW_WHILE; }
"for"                       { return KW_FOR; }
"read"                      { return KW_READ; }
"print"                     { return KW_PRINT; }
"return"                    { return KW_RETURN; }

"<="                        { return OPERATOR_LE; }
">="                        { return OPERATOR_GE; }
"=="                        { return OPERATOR_EQ; }
"!="                        { return OPERATOR_NE; }
"&&"                        { return OPERATOR_AND; }
"||"                        { return OPERATOR_OR; }
[-+,;:(){}*<>=!&$#\\\/\[\]]	{ fprintf(stderr, "Operator: %s -- ", yytext); return yytext[0]; }

[a-zA-Z_]+[ a-zA-Z_0-9]+[a-zA-Z_0-9]+|[a-zA-Z_]+[a-zA-Z_0-9]*    { hashInsert(TK_IDENTIFIER, yytext); fprintf(stderr, "Identifier: %s -- ", yytext); return TK_IDENTIFIER; }
[0-9]+                      { hashInsert(LIT_INTEGER, yytext); fprintf(stderr, "Integer: %s -- ", yytext); return LIT_INTEGER; }
[0-9]+.[0-9]+               { hashInsert(LIT_REAL, yytext); fprintf(stderr, "Real: %s -- ", yytext); return LIT_REAL; }
\'\\?[a-zA-Z0-9]\'          { hashInsert(LIT_CHAR, yytext); fprintf(stderr, "Char: %s -- ", yytext); return LIT_CHAR; }
\".+\"                      { hashInsert(LIT_STRING, yytext); fprintf(stderr, "String: %s -- ", yytext); return LIT_STRING; }

"//".*                      {  }
"/*"                        { BEGIN(COMMENT); }
<COMMENT>.                  {  }
<COMMENT>"\n"               { lineNumber++; }
<COMMENT>"*/"               { BEGIN(INITIAL); }

.                           { return TOKEN_ERROR; }

%%

int yywrap(){

    running = 0;
    return 1;
}

int isRunning(){
    return running;
}

int getLineNumber(){
    return lineNumber;
}
