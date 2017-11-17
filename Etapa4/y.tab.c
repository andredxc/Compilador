#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "astree.h"
    #include "hash.h"

    extern int getLineNumber();
    int yylex();
    void yyerror(char* arg);
#line 13 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
    HASH_NODE* symbol;
    AST_NODE* ast;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 41 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_BYTE 257
#define KW_SHORT 258
#define KW_LONG 259
#define KW_FLOAT 260
#define KW_DOUBLE 261
#define KW_IF 262
#define KW_THEN 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_FOR 266
#define KW_READ 267
#define KW_RETURN 268
#define KW_PRINT 269
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define TK_IDENTIFIER 276
#define LIT_INTEGER 277
#define LIT_REAL 278
#define LIT_CHAR 279
#define LIT_STRING 280
#define TOKEN_ERROR 281
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    3,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    5,    5,    6,    6,    7,    7,    8,    9,
    9,   10,   10,   11,   12,   12,   12,   12,   12,   12,
   13,   13,   14,   14,   15,   16,   17,   17,   18,   18,
   18,   19,   20,   20,   20,   21,   21,   21,   21,   21,
   21,   21,   21,   21,   21,   21,   21,   21,   21,   21,
   21,   21,   21,   21,   21,   22,   22,   23,   23,   23,
   23,   23,   24,   25,   25,   26,   26,
};
static const short yylen[] = {                            2,
    1,    2,    0,    1,    1,    4,    3,    3,    3,    3,
    3,    3,    3,    3,    5,    5,    5,    5,    5,    5,
    5,    5,    2,    0,    2,    0,    2,    0,    8,    2,
    0,    3,    0,    3,    1,    1,    1,    1,    1,    1,
    4,    0,    3,    0,    3,    2,    2,    2,    3,    3,
    0,    2,    6,    8,    5,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    4,
    1,    1,    1,    1,    2,    3,    6,    1,    1,    1,
    1,    1,    4,    2,    0,    3,    0,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    1,    0,    4,    5,    0,   78,   79,
   80,   81,   82,    0,    2,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    6,    0,    8,    7,    0,    9,    0,   10,
    0,   12,   11,    0,   14,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   21,   22,
   15,   16,    0,   17,   19,   18,   20,    0,    0,    0,
   30,   23,   27,   25,   34,    0,   29,    0,    0,    0,
    0,    0,    0,    0,    0,   35,   38,   40,   39,   36,
   37,   32,    0,    0,    0,    0,   71,   72,   73,    0,
    0,    0,   74,    0,   46,    0,    0,    0,    0,    0,
    0,    0,   45,    0,    0,   75,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   47,   48,    0,    0,    0,   41,    0,    0,    0,    0,
    0,   56,    0,    0,    0,    0,   67,   68,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   43,    0,   55,
   70,    0,   84,   83,   49,   50,    0,    0,    0,    0,
    0,   86,   54,
};
static const short yydgoto[] = {                          3,
    4,    5,    6,   21,   59,   65,   60,    7,   55,   71,
   56,   85,   86,  110,   87,   88,  105,  131,   89,   90,
  102,   91,   14,  103,  141,  163,
};
static const short yysindex[] = {                       -38,
  -44, -228,    0,    0,  -38,    0,    0,   23,    0,    0,
    0,    0,    0,   -2,    0,  -48,  -45,  -41,   12,   54,
   -8, -208, -255, -180, -171, -167, -165, -163, -252, -147,
 -130, -141,    0,  111,    0,    0,   62,    0,   68,    0,
   76,    0,    0,   78,    0,    0,   79, -100, -230,  -92,
  -92, -124, -124,  130,  148,  147,  -92,  -81,    0,    0,
    0,    0,  -78,    0,    0,    0,    0, -228,   81, -100,
    0,    0,    0,    0,    0,  -75,    0,  147,  162,  163,
  144,  -23,  -33,   55,  152,    0,    0,    0,    0,    0,
    0,    0,  -23,  -23,  -64,  -25,    0,    0,    0,  -23,
  -23,   66,    0,  169,    0,   36,  -23,  -23,  -75,   89,
   15,   22,    0,  -23,  -23,    0,   29,  -23,  -23,  -23,
  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -23,  -28,
    0,    0,   66,  -39,  152,    0,  -47,  -75,   45,   57,
  176,    0, -107, -107, -107, -107,    0,    0,   -1,   -1,
  -51,  -51, -107, -107,  169,   36,  157,    0,  -75,    0,
    0,  -23,    0,    0,    0,    0,  -23,  -37,   57,   66,
  -75,    0,    0,
};
static const short yyrindex[] = {                       225,
    0,    0,    0,    0,  225,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  185,  178,  178,
  178,  178,  178,    0,    0,  187,  178,  180,    0,    0,
    0,    0,  182,    0,    0,    0,    0,    0,    1,    0,
    0,    0,    0,    0,    0,  -40,    0,  187,    0,    0,
    0,    0,    0,    0,  117,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   -7,    0,    0,    0,    0,
    0,   61,    0,   70,    0,   70,    0,    0,  -40,    0,
    0,    0,    0,    0,  218,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   82,    0,  117,    0,    0,   84,    0,  219,
    0,    0,   80,   90,  115,  137,    0,    0,  385,  393,
  323,  377,  330,  352,   70,   70,    0,    0,   84,    0,
    0,    0,    0,    0,    0,    0,    0,  -32,  219,   85,
   84,    0,    0,
};
static const short yygindex[] = {                         0,
  256,    0,    0,    0,  113,  -35,  217,    0,    0,  198,
  208,  120,  229,  170,    0,    0,    0,  -61,    0,    0,
  405,    0,  244,    0,    0,  145,
};
#define YYTABLESIZE 657
static const short yytable[] = {                        100,
   42,    2,  124,  127,  100,  126,  101,  125,  128,  100,
  129,  101,   23,    8,  115,   25,  101,   67,   42,   27,
  128,   35,  129,   36,   42,   43,   53,   74,    9,   10,
   11,   12,   13,   69,   69,   69,   69,   69,   22,   69,
   42,  127,   24,  126,  132,   26,   57,   76,   58,   28,
   33,   69,   69,  157,   69,  137,  124,  127,  128,  126,
  129,  125,  138,  124,  127,  114,  126,   34,  125,  142,
  124,  127,   29,  126,  128,  125,  129,  124,  127,  130,
  126,  128,  125,  129,   42,   69,  124,  127,  128,  126,
  129,  125,   53,  165,  166,  128,   37,  129,  124,  127,
  162,  126,   30,  125,  128,   38,  129,  124,  127,   39,
  126,   40,  125,   41,   31,  107,  128,   69,  129,   52,
   63,   63,   63,   63,   63,  128,   63,  129,   51,   44,
   64,   64,   64,   64,   64,   47,   64,  161,   63,   63,
   76,   63,   42,   77,   32,  108,   45,   46,   64,   64,
   48,   64,   57,   63,   49,   65,   65,   65,   65,   65,
   50,   65,   61,   62,   64,   66,  122,  123,   51,   72,
   52,   53,   63,   65,   65,   54,   65,   66,   66,   66,
   66,   66,   64,   66,   57,   52,   79,   68,   69,   80,
   70,   81,   82,   83,   51,   66,   66,   58,   66,   63,
   84,   93,   94,   76,   63,   95,   76,   65,   42,   77,
  109,  113,  130,  136,   64,  159,  164,  167,  118,  119,
  120,  121,  122,  123,    3,   31,  171,   33,  135,   66,
  118,  119,  120,  121,  122,  123,   24,    1,   28,   65,
   26,   44,   96,   97,   98,   99,  104,   96,   97,   98,
   99,  155,   96,   97,   98,   99,   69,  160,   85,   87,
   15,   66,   69,   69,   69,   69,   69,   69,  118,  119,
  120,  121,  122,  123,   73,   92,   42,   78,  168,   16,
   17,   18,   19,   20,  118,  119,  120,  121,  122,  123,
  173,  118,  119,  120,  121,  122,  123,   77,  118,  119,
  120,  121,  122,  123,  158,  118,  119,  120,  121,  122,
  123,   75,    0,  172,  118,  119,  120,  121,  122,  123,
    0,    0,    0,    0,   52,    0,  118,  119,  120,  121,
  122,  123,    0,   51,    0,  118,  119,  120,  121,  122,
  123,    0,    0,   63,    0,   76,    0,   42,   77,   63,
   63,   63,   63,   64,    0,    0,    0,    0,    0,   64,
   64,   64,   64,   58,   58,   58,   58,   58,    0,   58,
   62,   62,   62,   62,   62,    0,   62,    0,   65,    0,
    0,   58,    0,    0,   65,   65,   65,   65,   62,   62,
    0,   62,   61,   61,   61,   61,   61,    0,   61,    0,
   66,    0,    0,    0,    0,    0,   66,   66,   66,   66,
   61,   61,    0,   61,    0,   58,    0,   57,   57,   57,
   57,   57,   62,   57,    0,   59,   59,    0,   59,    0,
    0,   59,    0,   60,   60,   57,   60,    0,    0,   60,
    0,    0,    0,   59,   61,    0,    0,   58,    0,    0,
    0,   60,    0,    0,   62,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   57,
    0,    0,    0,    0,    0,    0,   61,   59,    0,    0,
    0,    0,    0,    0,    0,   60,    0,  106,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  111,  112,    0,
    0,   57,    0,    0,  116,  117,    0,    0,    0,   59,
    0,  133,  134,    0,    0,    0,    0,   60,  139,  140,
    0,    0,  143,  144,  145,  146,  147,  148,  149,  150,
  151,  152,  153,  154,  156,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  169,    0,    0,    0,
    0,  170,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   58,    0,    0,    0,
    0,    0,    0,   62,    0,    0,    0,    0,    0,   62,
   62,   62,   62,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   61,    0,    0,    0,    0,
    0,   61,   61,   61,   61,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   57,    0,    0,    0,    0,    0,    0,    0,   59,    0,
    0,    0,    0,    0,    0,    0,   60,
};
static const short yycheck[] = {                         33,
    0,   40,   42,   43,   33,   45,   40,   47,   60,   33,
   62,   40,   61,   58,   40,   61,   40,   53,   59,   61,
   60,  277,   62,  279,  277,  278,   59,   63,  257,  258,
  259,  260,  261,   41,   42,   43,   44,   45,   41,   47,
   40,   43,   91,   45,  106,   91,  277,  123,  279,   91,
   59,   59,   60,   93,   62,   41,   42,   43,   60,   45,
   62,   47,   41,   42,   43,   91,   45,  276,   47,   41,
   42,   43,   61,   45,   60,   47,   62,   42,   43,   44,
   45,   60,   47,   62,  125,   93,   42,   43,   60,   45,
   62,   47,  125,  155,  156,   60,  277,   62,   42,   43,
   44,   45,   91,   47,   60,  277,   62,   42,   43,  277,
   45,  277,   47,  277,   61,   61,   60,  125,   62,   59,
   41,   42,   43,   44,   45,   60,   47,   62,   59,  277,
   41,   42,   43,   44,   45,  277,   47,   93,   59,   60,
   59,   62,   59,   59,   91,   91,  277,  278,   59,   60,
   40,   62,  277,  278,   93,   41,   42,   43,   44,   45,
   93,   47,   50,   51,   52,   53,  274,  275,   93,   57,
   93,   93,   93,   59,   60,  276,   62,   41,   42,   43,
   44,   45,   93,   47,  277,  125,  262,   58,   41,  265,
   44,  267,  268,  269,  125,   59,   60,  279,   62,  278,
  276,   40,   40,  123,  125,   62,  125,   93,  125,  125,
   59,  276,   44,  125,  125,  263,   41,   61,  270,  271,
  272,  273,  274,  275,    0,   41,  264,   41,  109,   93,
  270,  271,  272,  273,  274,  275,   59,  276,   59,  125,
   59,  125,  276,  277,  278,  279,  280,  276,  277,  278,
  279,  280,  276,  277,  278,  279,  264,  138,   41,   41,
    5,  125,  270,  271,  272,  273,  274,  275,  270,  271,
  272,  273,  274,  275,   58,   78,  276,   70,  159,  257,
  258,  259,  260,  261,  270,  271,  272,  273,  274,  275,
  171,  270,  271,  272,  273,  274,  275,   69,  270,  271,
  272,  273,  274,  275,  135,  270,  271,  272,  273,  274,
  275,   68,   -1,  169,  270,  271,  272,  273,  274,  275,
   -1,   -1,   -1,   -1,  264,   -1,  270,  271,  272,  273,
  274,  275,   -1,  264,   -1,  270,  271,  272,  273,  274,
  275,   -1,   -1,  264,   -1,  264,   -1,  264,  264,  270,
  271,  272,  273,  264,   -1,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,   41,   42,   43,   44,   45,   -1,   47,
   41,   42,   43,   44,   45,   -1,   47,   -1,  264,   -1,
   -1,   59,   -1,   -1,  270,  271,  272,  273,   59,   60,
   -1,   62,   41,   42,   43,   44,   45,   -1,   47,   -1,
  264,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,
   59,   60,   -1,   62,   -1,   93,   -1,   41,   42,   43,
   44,   45,   93,   47,   -1,   41,   42,   -1,   44,   -1,
   -1,   47,   -1,   41,   42,   59,   44,   -1,   -1,   47,
   -1,   -1,   -1,   59,   93,   -1,   -1,  125,   -1,   -1,
   -1,   59,   -1,   -1,  125,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   -1,   -1,   -1,   -1,   -1,   -1,  125,   93,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   -1,   83,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,
   -1,  125,   -1,   -1,  100,  101,   -1,   -1,   -1,  125,
   -1,  107,  108,   -1,   -1,   -1,   -1,  125,  114,  115,
   -1,   -1,  118,  119,  120,  121,  122,  123,  124,  125,
  126,  127,  128,  129,  130,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  162,   -1,   -1,   -1,
   -1,  167,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,
   -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,
   -1,  270,  271,  272,  273,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  264,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  264,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  264,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_BYTE","KW_SHORT","KW_LONG","KW_FLOAT",
"KW_DOUBLE","KW_IF","KW_THEN","KW_ELSE","KW_WHILE","KW_FOR","KW_READ",
"KW_RETURN","KW_PRINT","OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE",
"OPERATOR_AND","OPERATOR_OR","TK_IDENTIFIER","LIT_INTEGER","LIT_REAL",
"LIT_CHAR","LIT_STRING","TOKEN_ERROR","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : program",
"program : decList",
"decList : dec decList",
"decList :",
"dec : globalVariableDec",
"dec : functionDec",
"globalVariableDec : TK_IDENTIFIER ':' variableInfo ';'",
"variableInfo : KW_BYTE '=' LIT_CHAR",
"variableInfo : KW_BYTE '=' LIT_INTEGER",
"variableInfo : KW_SHORT '=' LIT_INTEGER",
"variableInfo : KW_LONG '=' LIT_INTEGER",
"variableInfo : KW_FLOAT '=' LIT_REAL",
"variableInfo : KW_FLOAT '=' LIT_INTEGER",
"variableInfo : KW_DOUBLE '=' LIT_REAL",
"variableInfo : KW_DOUBLE '=' LIT_INTEGER",
"variableInfo : KW_SHORT '[' LIT_INTEGER ']' intList",
"variableInfo : KW_LONG '[' LIT_INTEGER ']' intList",
"variableInfo : KW_FLOAT '[' LIT_INTEGER ']' intList",
"variableInfo : KW_DOUBLE '[' LIT_INTEGER ']' intList",
"variableInfo : KW_FLOAT '[' LIT_INTEGER ']' realList",
"variableInfo : KW_DOUBLE '[' LIT_INTEGER ']' realList",
"variableInfo : KW_BYTE '[' LIT_INTEGER ']' intList",
"variableInfo : KW_BYTE '[' LIT_INTEGER ']' charList",
"intList : LIT_INTEGER intList",
"intList :",
"realList : LIT_REAL realList",
"realList :",
"charList : LIT_CHAR charList",
"charList :",
"functionDec : '(' type ')' TK_IDENTIFIER '(' parameterList ')' comandBlock",
"parameterList : parameter moreParameters",
"parameterList :",
"moreParameters : ',' parameter moreParameters",
"moreParameters :",
"parameter : TK_IDENTIFIER ':' type",
"comand : comandBlock",
"comand : fluxControl",
"comand : attribution",
"comand : read",
"comand : return",
"comand : print",
"comandBlock : '{' comand moreComands '}'",
"comandBlock :",
"moreComands : ';' comand moreComands",
"moreComands :",
"read : KW_READ '>' TK_IDENTIFIER",
"print : KW_PRINT listElem",
"listElem : LIT_STRING tail_listElem",
"listElem : expression tail_listElem",
"tail_listElem : ',' LIT_STRING tail_listElem",
"tail_listElem : ',' expression tail_listElem",
"tail_listElem :",
"return : KW_RETURN expression",
"fluxControl : KW_IF '(' expression ')' KW_THEN comand",
"fluxControl : KW_IF '(' expression ')' KW_THEN comand KW_ELSE comand",
"fluxControl : KW_WHILE '(' expression ')' comand",
"expression : '(' expression ')'",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : expression '>' expression",
"expression : expression '<' expression",
"expression : expression OPERATOR_LE expression",
"expression : expression OPERATOR_GE expression",
"expression : expression OPERATOR_EQ expression",
"expression : expression OPERATOR_NE expression",
"expression : expression OPERATOR_AND expression",
"expression : expression OPERATOR_OR expression",
"expression : TK_IDENTIFIER",
"expression : TK_IDENTIFIER '[' expression ']'",
"expression : LIT_INTEGER",
"expression : LIT_REAL",
"expression : LIT_CHAR",
"expression : callFunc",
"expression : '!' expression",
"attribution : TK_IDENTIFIER '=' expression",
"attribution : TK_IDENTIFIER '[' expression ']' '=' expression",
"type : KW_BYTE",
"type : KW_SHORT",
"type : KW_LONG",
"type : KW_FLOAT",
"type : KW_DOUBLE",
"callFunc : TK_IDENTIFIER '(' listArg ')'",
"listArg : expression tailArg",
"listArg :",
"tailArg : ',' expression tailArg",
"tailArg :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 228 "parser.y"

void yyerror(char* arg){

    fprintf(stderr, "Erro sintático na linha %d\n", getLineNumber());
    exit(3);
}
#line 483 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 85 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast; ast = yyval.ast; astPrint(yyval.ast, 0); }
break;
case 2:
#line 88 "parser.y"
	{yyval.ast = astCreate(AST_CJTODEC_ELEM,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0);}
break;
case 3:
#line 89 "parser.y"
	{yyval.ast = 0;}
break;
case 4:
#line 92 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 5:
#line 93 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast; /*astPrint($$, 0);*/}
break;
case 6:
#line 97 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_GLOB,yystack.l_mark[-3].symbol,yystack.l_mark[-1].ast,0,0,0);}
break;
case 7:
#line 100 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_BYTE,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 8:
#line 101 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_BYTE,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 9:
#line 102 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_SHORT,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 10:
#line 103 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_LONG,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 11:
#line 104 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_FLOAT,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 12:
#line 105 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_FLOAT,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 13:
#line 106 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_DOUBLE,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 14:
#line 107 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VAR_DOUBLE,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 15:
#line 108 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_SHORT,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 16:
#line 109 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_LONG,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 17:
#line 110 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_FLOAT,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 18:
#line 111 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_FLOAT,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 19:
#line 112 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_FLOAT,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 20:
#line 113 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_DOUBLE,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 21:
#line 114 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_BYTE,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 22:
#line 115 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC_BYTE,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 23:
#line 118 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 24:
#line 119 "parser.y"
	{yyval.ast = 0;}
break;
case 25:
#line 122 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 26:
#line 123 "parser.y"
	{yyval.ast = 0;}
break;
case 27:
#line 126 "parser.y"
	{yyval.ast = astCreate(AST_DEC_VEC,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 28:
#line 127 "parser.y"
	{yyval.ast = 0;}
break;
case 29:
#line 130 "parser.y"
	{yyval.ast = astCreate(AST_DEC_FUNC,yystack.l_mark[-4].symbol,yystack.l_mark[-6].ast,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0);}
break;
case 30:
#line 133 "parser.y"
	{yyval.ast = astCreate(AST_DEC_PARAM_VEC,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0);}
break;
case 31:
#line 134 "parser.y"
	{yyval.ast = 0;}
break;
case 32:
#line 137 "parser.y"
	{yyval.ast = astCreate(AST_DEC_PARAM_VEC,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0);}
break;
case 33:
#line 138 "parser.y"
	{yyval.ast = 0;}
break;
case 34:
#line 141 "parser.y"
	{yyval.ast = astCreate(AST_DEC_PARAM,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 35:
#line 144 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 36:
#line 145 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 37:
#line 146 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 38:
#line 147 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 39:
#line 148 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 40:
#line 149 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 41:
#line 152 "parser.y"
	{yyval.ast = astCreate(AST_COMMAND_BLOCK, 0, yystack.l_mark[-2].ast, yystack.l_mark[-1].ast, 0, 0);}
break;
case 42:
#line 153 "parser.y"
	{yyval.ast = 0;}
break;
case 43:
#line 156 "parser.y"
	{yyval.ast = astCreate(AST_VEC_COMMAND_BLOCK, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 44:
#line 157 "parser.y"
	{yyval.ast = 0;}
break;
case 45:
#line 160 "parser.y"
	{yyval.ast = astCreate(AST_READ, yystack.l_mark[0].symbol, 0, 0, 0, 0);}
break;
case 46:
#line 163 "parser.y"
	{yyval.ast = astCreate(AST_PRINT, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 47:
#line 166 "parser.y"
	{yyval.ast = astCreate(AST_PRINT_ARG, yystack.l_mark[-1].symbol, 0, yystack.l_mark[0].ast, 0, 0);}
break;
case 48:
#line 167 "parser.y"
	{yyval.ast = astCreate(AST_PRINT_ARG, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 49:
#line 170 "parser.y"
	{yyval.ast = astCreate(AST_PRINT_ARG, yystack.l_mark[-1].symbol, 0, yystack.l_mark[0].ast, 0, 0);}
break;
case 50:
#line 171 "parser.y"
	{yyval.ast = astCreate(AST_PRINT_ARG, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 51:
#line 172 "parser.y"
	{yyval.ast = 0; }
break;
case 52:
#line 175 "parser.y"
	{yyval.ast = astCreate(AST_RETURN, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 53:
#line 178 "parser.y"
	{yyval.ast = astCreate(AST_IF, 0, yystack.l_mark[-3].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 54:
#line 179 "parser.y"
	{yyval.ast = astCreate(AST_IF_ELSE, 0, yystack.l_mark[-5].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0);}
break;
case 55:
#line 180 "parser.y"
	{yyval.ast = astCreate(AST_WHILE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 56:
#line 183 "parser.y"
	{yyval.ast = astCreate(AST_EXPRESSION, 0, yystack.l_mark[-1].ast, 0, 0, 0);}
break;
case 57:
#line 184 "parser.y"
	{yyval.ast = astCreate(AST_ADD, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 58:
#line 185 "parser.y"
	{yyval.ast = astCreate(AST_SUB, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 59:
#line 186 "parser.y"
	{yyval.ast = astCreate(AST_MUL, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 60:
#line 187 "parser.y"
	{yyval.ast = astCreate(AST_DIV, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 61:
#line 188 "parser.y"
	{yyval.ast = astCreate(AST_GREATER, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 62:
#line 189 "parser.y"
	{yyval.ast = astCreate(AST_LESS, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 63:
#line 190 "parser.y"
	{yyval.ast = astCreate(AST_LE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 64:
#line 191 "parser.y"
	{yyval.ast = astCreate(AST_GE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 65:
#line 192 "parser.y"
	{yyval.ast = astCreate(AST_EQ, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 66:
#line 193 "parser.y"
	{yyval.ast = astCreate(AST_NE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 67:
#line 194 "parser.y"
	{yyval.ast = astCreate(AST_AND, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 68:
#line 195 "parser.y"
	{yyval.ast = astCreate(AST_OR, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 69:
#line 196 "parser.y"
	{yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0);}
break;
case 70:
#line 197 "parser.y"
	{yyval.ast = astCreate(AST_ARRAY, yystack.l_mark[-3].symbol, yystack.l_mark[-1].ast, 0, 0, 0);}
break;
case 71:
#line 198 "parser.y"
	{yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0);}
break;
case 72:
#line 199 "parser.y"
	{yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0);}
break;
case 73:
#line 200 "parser.y"
	{yyval.ast = astCreate(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0);}
break;
case 74:
#line 201 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 75:
#line 202 "parser.y"
	{yyval.ast = astCreate(AST_NOT, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 76:
#line 205 "parser.y"
	{yyval.ast = astCreate(AST_ATTR, yystack.l_mark[-2].symbol, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 77:
#line 206 "parser.y"
	{yyval.ast = astCreate(AST_ATTR_VEC, yystack.l_mark[-5].symbol, yystack.l_mark[-3].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 78:
#line 209 "parser.y"
	{yyval.ast = astCreate(AST_BYTE,0,0,0,0,0);}
break;
case 79:
#line 210 "parser.y"
	{yyval.ast = astCreate(AST_SHORT,0,0,0,0,0);}
break;
case 80:
#line 211 "parser.y"
	{yyval.ast = astCreate(AST_LONG,0,0,0,0,0);}
break;
case 81:
#line 212 "parser.y"
	{yyval.ast = astCreate(AST_FLOAT,0,0,0,0,0);}
break;
case 82:
#line 213 "parser.y"
	{yyval.ast = astCreate(AST_DOUBLE,0,0,0,0,0);}
break;
case 83:
#line 216 "parser.y"
	{yyval.ast = astCreate(AST_CALLFUNC, yystack.l_mark[-3].symbol, yystack.l_mark[-1].ast, 0, 0, 0);}
break;
case 84:
#line 219 "parser.y"
	{yyval.ast = astCreate(AST_FUNC_ARG_LIST, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 85:
#line 220 "parser.y"
	{yyval.ast = 0; }
break;
case 86:
#line 223 "parser.y"
	{yyval.ast = astCreate(AST_FUNC_ARG_LIST, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 87:
#line 224 "parser.y"
	{yyval.ast = 0;}
break;
#line 1033 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
