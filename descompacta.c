#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"

bitmap buffer; // buffer que guarda o último byte lido do arquivo
unsigned int current_bit = 7; // valor do próximo bit a ser lido no buffer

/* Função de interface para ler um bit do arquivo
Argumentos: ponteiro para o arquivo
Retorno: valor do bit (0 ou 1)
Pré-condição: arquivo já aberto para leitura
Pós-condição: buffer atualizado caso o byte anterior já tivesse sido lido por completo */
int le_bit(FILE *fp) {
    if(current_bit == 7)
        buffer.contents[0] = fgetc(fp); // armazena no buffer um novo byte, se o anterior tiver acabado
    int bit = (int) bitmapGetBit(buffer, 7 - current_bit); // toma o valor do próximo bit ainda não lido
    // Atualiza o valor do próximo bit a ser lido
    if(current_bit == 0)
        current_bit = 7;
    else
        current_bit--;
    return bit;
}

/* Função que recria recursivamente a árvore de huffman a partir do cabeçalho do arquivo
Argumentos: ponteiro para o arquivo
Retorno: ponteiro para a árvore criada
Pré-condição: arquivo já aberto para leitura
Pós-condição: árvore de Huffman criada e preenchida */
Arv *resgata_arvore(FILE *fp) {
    if(le_bit(fp) == 0) // se o bit é zero, cria nó não folha e, por recursão, suas sub-árvores
        return arv_cria((unsigned char)0, 5, resgata_arvore(fp), resgata_arvore(fp));
    // se o bit for 1, calcula o valor do caracter pela soma de potências de 2
    int n = 0;
    for(int i=0; i<8; i++) {
        if(le_bit(fp) == 1)
            n += pow(2, 7-i);
    }
    return arv_cria((unsigned char) n, 4, NULL, NULL); // retorna nó folha criado
}

int main(int argc, char** argv) {

    buffer = bitmapInit(8);
    buffer.length = 8;

    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        free(buffer.contents);
        return 1;
    }

    FILE *fp, *sd;

    if((fp = fopen(argv[1], "rb")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", argv[1]);
        free(buffer.contents);
        return 1;
    }

    char *output_name = "descompactado.txt";

    if((sd = fopen(output_name, "w")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", output_name);
        free(buffer.contents);
        return 1;
    }

    Arv *huff = resgata_arvore(fp);

    arv_imprime(huff);

    unsigned char c = 0;
    Arv *aux;

    while(c != 7) {
        aux = huff;
        while(!folha(aux)) {
            if(le_bit(fp) == 1)
                aux = get_sae(aux);
            else
                aux = get_sad(aux);
        }
        c = info(aux);
        if(c != 7)
            fprintf(sd, "%c", c);
    }

    fclose(fp);
    fclose(sd);
    free(buffer.contents);
    arv_libera(huff);

    return 0;
}