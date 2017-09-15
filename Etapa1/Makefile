
etapa1: lex.yy.c main.o
	gcc lex.yy.c -o etapa1

main.o: main.c
	gcc main.c -c

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa1 *.o
