#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"

bitmap buffer;
unsigned int current_bit = 7;

int le_bit(FILE *fp) {
    if(current_bit == 7)
        buffer.contents[0] = fgetc(fp);
    int bit = (int) bitmapGetBit(buffer, 7 - current_bit);
    if(current_bit == 0)
        current_bit = 7;
    else
        current_bit--;
    return bit;
}

Arv *resgata_arvore(FILE *fp) {
    if(le_bit(fp) == 0)
        return arv_cria((unsigned char)0, 5, resgata_arvore(fp), resgata_arvore(fp));
    int n = 0;
    for(int i=0; i<8; i++) {
        if(le_bit(fp) == 1)
            n += pow(2, 7-i);
    }
    return arv_cria((unsigned char) n, 4, NULL, NULL);
}

int main(int argc, char** argv) {

    buffer = bitmapInit(8);
    buffer.length = 8;

    if(argc < 2) {
        printf("Erro: Nome do arquivo de entrada não especificado\n");
        // free(buffer.contents);
        return 1;
    }

    FILE *fp, *sd;

    if((fp = fopen(argv[1], "rb")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", argv[1]);
        return 1;
    }

    // char *output_name = (char *)malloc(sizeof(char)*(strlen(argv[1])+2));
    // strcpy(output_name, argv[1]);
    // strcat(output_name, "2");
    // strcpy(output_name+strlen(argv[1])-3, "txt");

    char *output_name = "descompactado.txt";

    if((sd = fopen(output_name, "w")) == NULL) {
        printf("Erro na abertura do arquivo %s\n", output_name);
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

    return 0;
}