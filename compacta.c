#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "lista.h"

Arv *arv_huffman(char *filename) {
    int pesos[256] = { 0 };         // vetor de pesos (sugerido na Dica 1)

    FILE *fp;
    char c;
    if((fp = fopen(filename, "rt")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", filename);
        return NULL;
    }

    // Preenchimento do vetor de pesos
    while ((c = fgetc(fp)) != EOF)
        pesos[(int)c]++;
    fclose(fp);

    int maior_peso = 0;
    int peso, i;
    for (i=0; i<256; i++)
        if(pesos[i] > maior_peso)
            maior_peso = pesos[i];

    // Cria a lista ordenada de nós com os caracteres
    TipoLista *lista_arvores = InicializaLista();
    int j;
    for(i=1; i<=maior_peso; i++)
        for(j=0; j<256; j++)
            if(pesos[j] == i)
                Insere(arv_cria((char)j, i, NULL, NULL), lista_arvores);

    // Junta os nós para formar a árvore de Huffman
    Arv *nova, *a1, *a2;
    int novo_peso;
    while(!unico(lista_arvores)) {
        a1 = Pop(lista_arvores);
        a2 = Pop(lista_arvores);
        nova = arv_cria((char)0, get_peso(a1)+get_peso(a2), a1, a2);
        Insere(nova, lista_arvores);
    }
    Libera(lista_arvores);
    return nova;
}

int main(int argc, char** argv) {
    
    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        return 1;
    }

    Arv *huff = arv_huffman(argv[1]);

    return 0;
}