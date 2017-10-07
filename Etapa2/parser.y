
%{
    #include <stdio.h>

    extern int getLineNumber();
    int yylex();
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

%left OPERATOR_OR OPERATOR_AND 
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '-' '+'
%left '*' '/'
%right '!'

%%
 
// Um programa é composto por um conjunto de declarações de funções	ou declarações de variáveis globais (podem aparecer em qualquer ordem)
program: decList
	;

decList: dec decList
	|
	;

dec: globalVariableDec
    | functionDec
	;

// Todas as declarações de variáveis devem ser terminadas por ponto e vírgula
// As variáveis são declaradas pela sequência de seu nome, dois-pontos, seu tipo, sinal de '=' e o valor de inicialização obrigatório
// Declaração de vetores: definição	de seu tamanho inteiro positivo entre colchetes, colocada imediatamente à direita do tipo.
//  	a inicialização	é opcional, e quando presente, será dada pela sequência de valores literais separados por caraceres em	
//      branco,	entre o tamanho e o terminador ponto-e-vírgula.	
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

// As declarações de funções NÃO devem terminar com ponto e virgula
// Cada função é definida por seu cabeçalho seguido	de seu corpo. O cabeçalho consiste no tipo do valor	de retorno entre parênteses,
// seguido do nome da função e depois de uma lista entre parênteses, de parâmetros de entrada, separados por vírgula, onde cada parâmetro
// é definido por nome, seguido de dois pontos e tipo, e não podem ser do tipo vetor. O corpo da função é composto por um bloco
functionDec: '(' type ')' TK_IDENTIFIER '(' parameterList ')' comandBlock
    parameterList: parameter moreParameters
    |
    ;

moreParameters: ',' parameter moreParameters
    |
    ;

parameter: TK_IDENTIFIER ':' type
    ;


/* Os comandos da linguagem podem ser: atribuição, construções de controle de fluxo, read, print, return e comando vazio.*/
comand: comandBlock
    | fluxControl
    | attribution
    | read
    | return
    | print
    ;

/* Um bloco de comandos é definido entre chaves, e consiste em uma sequência de comandos, separados por ponto-e-vírgula. 
 O símbolo de ponto-e-vírgula está associado à lista de comandos presentes dentro de um bloco, e não a cada comando em si.
 Considerando que os comandos poderão aparecer recursivamente dentro de outros comandos, não é permitido que cada um deles venha 
 acompanhado de um ponto-e-vírgula adicional, mas apenas quando ocorrem na formação da lista dentro do bloco. Um bloco de comandos 
 é considerado como um comando único simples, recursivamente, e pode ser utilizado em qualquer construção que aceite um comando simples.
*/

comandBlock: '{' comand moreComands '}'
    |
    ;

moreComands: ';' comand moreComands
    |
    ;



/* O comando read é identificado pela palavra reservada read, seguida do símbolo '>' e de variável, na qual o valor lido da entrada padrão,
 se disponível e compatível, será	colocado. Somente variáveis	escalares são aceitas no comando input, e não vetores ou posições de vetores
*/
read: KW_READ '>' TK_IDENTIFIER
    ;

/* O comando print é identificado pela palavra reservada print,	seguida	de uma lista de	elementos separados por vírgula, onde cada elemento
   pode ser um string ou uma expressão aritmética a	ser	impressa.*/
print: KW_PRINT listElem
    ;

listElem: LIT_STRING  tail_listElem
            | expression tail_listElem
            ;

tail_listElem: ',' LIT_STRING tail_listElem
			| ',' expression tail_listElem
			| 
			;

/* O comando return é identificado pela palavra reservada return seguida de uma expressão que dá o valor de retorno.*/
return: KW_RETURN expression
    ;

fluxControl: KW_IF '(' expression ')' KW_THEN comand
    | KW_IF '(' expression ')' KW_THEN comand KW_ELSE comand
    | KW_WHILE '(' expression ')' comand
    ;

/* As expressões aritméticas têm como folhas identificadores, opcionalmente seguidos de expressão inteira entre colchetes, ou podem ser 
literais. As expressões aritméticas podem ser formadas recursivamente com operadores aritméticos, assim como permitem o uso de parênteses
para associatividade. Expressões Lógicas (Booleanas) podem ser formadas através dos operadores relacionais aplicados a expressões aritméticas,
ou de operadores lógicos aplicados a expressões lógicas, recursivamente. Os operadores válidos são:	+,-,*,/,<,>,! (lógico),	e os listados
na tabela da etapa1 representados com mais de um caractere. Expressões também podem ser formadas considerando literais do tipo caractere.
Finalmente, um operando possível de expressão é uma	chamada de função, feita pelo seu nome, seguido de lista de argumentos entre parênteses,
separados por vírgula.		
*/
expression: '(' expression ')'
    | expression operator expression
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | callFunc
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

operator: OPERATOR_LE
    | OPERATOR_GE
    | OPERATOR_EQ
    | OPERATOR_NE
    | OPERATOR_AND
    | OPERATOR_OR
    | '+'
    | '-'
    | '*'
    | '/'
    | '>'
    | '<'
    | '!'
    ;

callFunc: TK_IDENTIFIER '(' listArg ')';
    ;

listArg: expression tailArg
    | 
    ;

tailArg: ',' expression tailArg
    |
    ;

%%

int yyerror(char* arg){

    fprintf(stderr, "Erro na linha %d\n", getLineNumber());
    return 0;
}
