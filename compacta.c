#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "bitmap.h"

#define BIT_COUNT 50    // altura máxima suportada para a árvore de Huffman

bitmap buffer;          // buffer para acumular 8 bits antes da escrita no arquivo


/* Função que contabiliza a frequência de todos os caracteres no arquivo de
entrada e cria a árvore de Huffman.
Argumentos: ponteiro para o arquivo a ser lido
Retorno: ponteiro para a Árvore de Huffman derivada do arquivo
Pré-condição: nenhuma
Pós-condição: Árvore criada e já preenchida */
Arv *arv_huffman(char *filename) {
    int pesos[256] = { 0 };         // vetor de pesos (sugerido na Dica 1)

    FILE *fp;
    int c;
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
        nova = arv_cria((unsigned char)0, get_peso(a1)+get_peso(a2), a1, a2);
        Insere_ordenado(nova, lista_arvores);
    }
    Libera(lista_arvores);
    return nova;
}

/* Preenche recursivamente a tabela com os códigos binários da compressão de cada caracter existente
no arquivo.
Argumentos: ponteiro para o vetor de bitmaps e para a árvore de Huffman, bitmap auxiliar
Retorno: nenhum
Pré-condição: vetor tabela formado por bitmaps já inicializados
Pós-condição: bitmaps do vetor nas posições equivalentes a cada caracter presente na árvore
              estarão preenchidas com o código da compressão do caracter */
void preenche_tabela(bitmap *tabela, Arv *a, bitmap b) {
    if(!arv_vazia(a)) {
        if(folha(a)) {  // se encontra um nó folha, preenche a posição equivalente na tabela com o valor atual do bitmap auxiliar
            for (int i=0; i<bitmapGetLength(b); i++) {
		        bitmapAppendLeastSignificantBit(tabela+info(a), bitmapGetBit(b, i));
            }
        }
        else {  // se o nó não é folha, ocorre recursão, nas sub-árvores da esquerda e direita
            bitmap b2 = bitmapInit(BIT_COUNT);
            for (int i=0; i<bitmapGetLength(b); i++)
		        bitmapAppendLeastSignificantBit(&b2, bitmapGetBit(b, i));
            bitmapAppendLeastSignificantBit(&b2, 0);    // acrescenta 0 ao bitmap auxiliar antes de chamar a função à esquerda
            preenche_tabela(tabela, get_sae(a), b2);
            free(b2.contents);
            b2 = bitmapInit(BIT_COUNT);
            for (int i=0; i<bitmapGetLength(b); i++)
		        bitmapAppendLeastSignificantBit(&b2, bitmapGetBit(b, i));
            bitmapAppendLeastSignificantBit(&b2, 1);    // acrescenta 1 ao bitmap auxiliar antes de chamar a função à direita
            preenche_tabela(tabela, get_sad(a), b2);
            free(b2.contents);
        }
    }
}

/* Abre o arquivo de saída para escrita
Argumentos: nome do arquivo
Retorno: ponteiro para o arquivo aberto
Pré-condição: nenhuma
Pós-condição: arquivo aberto para escrita */
FILE *iniciar_escrita(char *filename) {
    return fopen(filename, "w");
}

void escreve_bit(unsigned char bit, FILE *fp) {
    bitmapAppendLeastSignificantBit(&buffer, bit);
    if(bitmapGetLength(buffer) == 8) {
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
    free(aux.contents);
}

void encerrar_escrita(FILE *fp) {
    int falta = 8 - bitmapGetLength(buffer);
    for(int i=0; i<falta; i++)
        escreve_bit(0, fp);
    fclose(fp);
}

void freeTabela(bitmap* t){
  for(int i=0;i<256;i++){
    if(t[i].contents!=NULL)
      free(t[i].contents);
  }
}

int main(int argc, char** argv) {

    buffer = bitmapInit(8);

    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        free(buffer.contents);
        return 1;
    }

    Arv *huff = arv_huffman(argv[1]);

    arv_imprime(huff);

    bitmap tabela[256];
    bitmap aux = bitmapInit(BIT_COUNT);
    for(int i=0; i<256; i++)
        tabela[i] = bitmapInit(BIT_COUNT);
    preenche_tabela(tabela, huff, aux);
    
    char *output_name = (char *)malloc(sizeof(char)*(strlen(argv[1])+2));
    strcpy(output_name, argv[1]);
    strcpy(output_name+strlen(argv[1])-3, "comp");

    FILE *out = iniciar_escrita(output_name);
    
    insere_cabecalho(out, huff);
    FILE *in = fopen(argv[1], "rt");
    int c;

    while ((c = fgetc(in)) != EOF) {
        for(int i=0; i<bitmapGetLength(tabela[c]); i++)
		    escreve_bit(bitmapGetBit(tabela[c], i), out);
    }

    for(int i=0; i<bitmapGetLength(tabela[7]); i++)
		escreve_bit(bitmapGetBit(tabela[7], i), out);

    encerrar_escrita(out);
    fclose(in);

    freeTabela(tabela);
    arv_libera(huff);
    free(output_name);
    free(aux.contents);
    free(buffer.contents);

    return 0;
}
