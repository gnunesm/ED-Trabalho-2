all:
	gcc arvore.c bitmap.c compacta.c lista.c -Wall -o app

run:
	./app
