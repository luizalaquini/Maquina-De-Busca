all:
	make compile
	make executar

compile:
	gcc *.c -o trab3

executar:
	valgrind ./trab3 teste1