all: compacta descompacta
	
compacta: compacta.c
	gcc arvore.c bitmap.c compacta.c lista.c -Wall -o compacta

descompacta: descompacta.c
	gcc arvore.c bitmap.c descompacta.c -lm -Wall -o descompacta