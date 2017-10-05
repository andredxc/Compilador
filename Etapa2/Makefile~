etapa2: lex.yy.o main.o hash.o
		gcc -o etapa2 lex.yy.o main.o hash.o

main.o:	main.c
		gcc -c main.c

hash.o: hash.c
		gcc -c hash.c 

lex.yy.o: lex.yy.c
		gcc -c lex.yy.c

lex.yy.c: scanner.l
		flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o etapa2 lex.yy.c lex.yy.h y.tab.h y.tab.c
