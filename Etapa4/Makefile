etapa4: astree.o y.tab.o lex.yy.o hash.o semantic.o main.o
	gcc -o etapa4 y.tab.o lex.yy.o hash.o astree.o semantic.o main.o

main.o:	main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

astree.o:
	gcc -c astree.c

semantic.o:
	gcc -c semantic.c -g

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o *~ etapa4 lex.yy.c lex.yy.h y.tab.h y.tab.c y.output
