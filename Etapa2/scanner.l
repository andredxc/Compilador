%{
    /*
    * André D. Carneiro e Victória Simonetti
    */

    #include <stdio.h>
	#include <string.h>
    #include "hash.h"
    #include "y.tab.h"

    int running = 1;
    int lineNumber = 1;

    int getLineNumber();
    int isRunning();
    void initMe();
%}

%x COMMENT
%x STRING

%%

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
[-+,;:(){}*<>=!&$#\\\/\[\]]	{ return yytext[0]; }

[a-zA-Z_]+[ a-zA-Z_0-9]+[a-zA-Z_0-9]+|[a-zA-Z_]+[a-zA-Z_0-9]*    { hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }
[0-9]+                      { yylval.symbol = hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER; }
[0-9]+\.[0-9]+              { yylval.symbol = hashInsert(LIT_REAL, yytext); return LIT_REAL; }
'.'                         { yylval.symbol = hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
\"(\\.|[^\\"])+\"		    { yylval.symbol = hashInsert(LIT_STRING, yytext); return LIT_STRING; }

\n						{++lineNumber;}
[ \t]                   {  }
"//".*                  {  }
"/*"					{ BEGIN(COMMENT); }
.                       { return TOKEN_ERROR; }

<COMMENT>"*/" 			BEGIN(INITIAL);
<COMMENT>.
<COMMENT>\n				{++lineNumber;}

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

void initMe(){
    hashInit();
}
