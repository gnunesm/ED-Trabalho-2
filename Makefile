all:
	gcc arvore.c lista.c bitmap.c compacta.c -Wall -o compacta
	gcc arvore.c lista.c bitmap.c descompacta.c -lm -Wall -o descompacta

compacta:
	./compacta

descompacta:
	./descompacta