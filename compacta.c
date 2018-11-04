#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "lista.h"
#include "bitmap.h"

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

    // Cria a lista ordenada de nós com os caracteres
    TipoLista *lista_arvores = InicializaLista();
    for(int i=0; i<256; i++)
        if(pesos[i] != 0)
            Insere_ordenado(arv_cria((char)i, pesos[i], NULL, NULL), lista_arvores);

    // Junta os nós para formar a árvore de Huffman
    Arv *nova, *a1, *a2;
    int novo_peso;
    while(!unico(lista_arvores)) {
        a1 = Pop(lista_arvores);
        a2 = Pop(lista_arvores);
        nova = arv_cria((char)0, get_peso(a1)+get_peso(a2), a1, a2);
        Insere_ordenado(nova, lista_arvores);
    }
    Libera(lista_arvores);
    return nova;
}

void preenche_tabela(bitmap *tabela, Arv *a, bitmap b) {
    if(!arv_vazia(a)) {
        if(folha(a))
            for (int i=0; i<bitmapGetLength(b); i++)
		        bitmapAppendLeastSignificantBit(tabela+info(a), bitmapGetBit(b, i));
        else {
            bitmap b2 = bitmapInit(8);
            for (int i=0; i<bitmapGetLength(b); i++)
		        bitmapAppendLeastSignificantBit(&b2, bitmapGetBit(b, i));
            bitmapAppendLeastSignificantBit(&b2, 0);
            preenche_tabela(tabela, get_sae(a), b2);
            b2 = bitmapInit(8);
            for (int i=0; i<bitmapGetLength(b); i++)
		        bitmapAppendLeastSignificantBit(&b2, bitmapGetBit(b, i));
            bitmapAppendLeastSignificantBit(&b2, 1);
            preenche_tabela(tabela, get_sad(a), b2);
        }
    }
}

int main(int argc, char** argv) {
    
    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        return 1;
    }

    Arv *huff = arv_huffman(argv[1]);

    bitmap tabela[256];
    bitmap aux = bitmapInit(8);
    for(int i=0; i<256; i++)
        tabela[i] = bitmapInit(8);
    preenche_tabela(tabela, huff, aux);

    return 0;
}