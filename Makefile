all:
	make -C Etapa1
	make -C Etapa2

clean:
	make clean -C Etapa1
	make clean -C Etapa2
