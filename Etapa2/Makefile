etapa2: hash.o y.tab.o lex.yy.o main.o
	gcc -o etapa2 lex.yy.o main.o hash.o y.tab.o

main.o:	main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o *~ etapa2 lex.yy.c lex.yy.h y.tab.h y.tab.c y.output
