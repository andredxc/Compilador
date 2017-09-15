%{
	#include "main.c"

	int isRunning();

	int running = 1;
%}
%%

"int"			{ fprintf(stderr, "Found int\n");return 111; }

%%

int yywrap(){

	running = 0;
	return 1;
}

int isRunning(){
	return running;
}
