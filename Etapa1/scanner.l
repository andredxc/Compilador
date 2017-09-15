%{
/*
            TOKENS.H
#define KW_BYTE       256
#define KW_SHORT      257
#define KW_LONG       258
#define KW_FLOAT      259
#define KW_DOUBLE     260
#define KW_IF	      261
#define KW_THEN       262
#define KW_ELSE       263
#define KW_WHILE      264
#define KW_FOR        265
#define KW_READ       266
#define KW_RETURN     267
#define KW_PRINT      268

#define OPERATOR_LE   270
#define OPERATOR_GE   271
#define OPERATOR_EQ   272
#define OPERATOR_NE   273
#define OPERATOR_AND  274
#define OPERATOR_OR   275

#define TK_IDENTIFIER 280
#define LIT_INTEGER   281
#define LIT_REAL      282
#define LIT_CHAR      285
#define LIT_STRING    286

#define TOKEN_ERROR   290
*/

    #include "main.c"
    #include "tokens.h"

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

[a-zA-Z_]+[ ][a-zA-Z_0-9]+|[a-zA-Z_]+[a-zA-Z_0-9]*    { fprintf(stderr, "Identifier: %s -- ", yytext); return TK_IDENTIFIER; }
[0-9]+                      { fprintf(stderr, "Integer: %s -- ", yytext); return LIT_INTEGER; }
[0-9]+.[0-9]+                { fprintf(stderr, "Real: %s -- ", yytext); return LIT_REAL; }
\'\\?[a-zA-Z0-9]\'          { fprintf(stderr, "Char: %s -- ", yytext); return LIT_CHAR; }
\".+\"                      { fprintf(stderr, "String: %s -- ", yytext); return LIT_STRING; }

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
