#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arvore.h"
#include "bitmap.h"

bitmap buffer;
unsigned int current_bit = 0;

int le_bit(FILE *fp) {
    if(current_bit == 7)
        buffer.contents[0] = fgetc(fp);
    int bit = (int) bitmapGetBit(buffer, current_bit);
    if(current_bit == 0)
        current_bit = 7;
    else
        current_bit--;
    return bit;
}

Arv *resgata_arvore(FILE *fp) {
    if(le_bit(fp) == 0)
        return arv_cria((unsigned char)0, 0, resgata_arvore(fp), resgata_arvore(fp));
    int n = 0;
    for(int i=0; i<8; i++) {
        if(le_bit(fp) == 1)
            n += pow(2, i);
    }
    return arv_cria((unsigned char) n, 0, resgata_arvore(fp), resgata_arvore(fp));
}

int main(int argc, char** argv) {

    buffer = bitmapInit(8);
    buffer.length = 8;

    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        // free(buffer.contents);
        return 1;
    }

    FILE *fp;

    if((fp = fopen(argv[1], "rb")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", argv[1]);
        return 1;
    }

    Arv *huff = resgata_arvore(fp);

    arv_imprime (huff);

    fclose(fp);

    return 0;
}