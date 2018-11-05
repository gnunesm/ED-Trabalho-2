#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "bitmap.h"

bitmap buffer;

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
    pesos[7] = 1;                                 // caracter artificial de fim de arquivo
    // Cria a lista ordenada de nós com os caracteres
    TipoLista *lista_arvores = InicializaLista();
    for(int i=0; i<256; i++)
        if(pesos[i] != 0)
            Insere_ordenado(arv_cria((unsigned char)i, pesos[i], NULL, NULL), lista_arvores);

    // Junta os nós para formar a árvore de Huffman
    Arv *nova, *a1, *a2;
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
        if(folha(a)) {
            for (int i=0; i<bitmapGetLength(b); i++) {
		        bitmapAppendLeastSignificantBit(tabela+info(a), bitmapGetBit(b, i));
            }
        }
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

FILE *iniciar_escrita(char *filename) {
    return fopen(filename, "w");
}

void escreve_bit(unsigned char bit, FILE *fp) {
    printf("tenta\n");
    bitmapAppendLeastSignificantBit(&buffer, bit);
    printf("consegue\n");
    if(bitmapGetLength(buffer) == 8) {
        printf("aqui\n");
        fprintf(fp, "%c", buffer.contents[0]);
        buffer.contents[0] = 0x00;
        buffer.length = 0;
    }
}

void insere_cabecalho(FILE *fp, Arv *a) {
    bitmap aux = bitmapInit(8);
    aux.length = 8;
    if(!arv_vazia(a)) {
        if(folha(a)) {
            escreve_bit(1, fp);
            aux.contents[0] = info(a);
            for(int i=0; i<8; i++)
                escreve_bit(bitmapGetBit(aux, i), fp);
        }
        else {
            escreve_bit(0, fp);
            insere_cabecalho(fp, get_sae(a));
            insere_cabecalho(fp, get_sad(a));
        }
    }
}

void encerrar_escrita(FILE *fp) {
    int falta = 8 - bitmapGetLength(buffer);
    for(int i=0; i<falta; i++)
        escreve_bit(0, fp);
    fclose(fp);
}

int main(int argc, char** argv) {
    
    buffer = bitmapInit(8);

    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        return 1;
    }

    Arv *huff = arv_huffman(argv[1]);

    arv_imprime(huff);

    bitmap tabela[256];
    bitmap aux = bitmapInit(8);
    for(int i=0; i<256; i++)
        tabela[i] = bitmapInit(8);
    preenche_tabela(tabela, huff, aux);

    char *output_name = (char *)malloc(sizeof(char)*(strlen(argv[1])+2));
    strcpy(output_name, argv[1]);
    strcpy(output_name+strlen(argv[1])-3, "comp");

    FILE *out = iniciar_escrita(output_name);

    insere_cabecalho(out, huff);

    FILE *in = fopen(argv[1], "rt");
    char c;
    
    while ((c = fgetc(in)) != EOF) {
        for(int i=0; i<bitmapGetLength(tabela[c]); i++)
		    escreve_bit(bitmapGetBit(tabela[c], i), out);
    }

    for(int i=0; i<bitmapGetLength(tabela[254]); i++)
		escreve_bit(bitmapGetBit(tabela[254], i), out);

    encerrar_escrita(out);
    fclose(in);

    return 0;
}