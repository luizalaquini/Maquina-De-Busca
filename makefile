all:
	make compile
	make executar

compile:
	gcc *.c -o trab3 -g

executar:
	./trab3 criacao_testes <criacao_testes/searches.txt >criacao_testes/sol.txt