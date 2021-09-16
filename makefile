all:
	make compile
	make executar

compile:
	gcc *.c -o trab3 -g

executar:
	valgrind --leak-check=full ./trab3 teste1