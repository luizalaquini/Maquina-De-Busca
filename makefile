all:
	make compile
	make executar

compile:
	gcc *.c -o trab3 -g

executar:
	./trab3 exemplo2 <exemplo2/searches.txt >sol.txt