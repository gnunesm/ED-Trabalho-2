#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arv {
    char c;
    int peso;
    Arv *sae;
    Arv *sad;
};

Arv *arv_criavazia (void) {
    return NULL;
}

Arv *arv_cria (char c, int peso, Arv* e, Arv* d) {
    Arv *arvore = (Arv *) malloc(sizeof(Arv));
    arvore->c = c;
    arvore->peso = peso;
    arvore->sae = e;
    arvore->sad = d;
    return arvore;
}

void imprime_aux(Arv *a) {
    if(arv_vazia(a))
        printf("<>");
    else {
        printf("<%c%d", a->c, a->peso);
        imprime_aux(a->sae);
        imprime_aux(a->sad);
        printf(">");
    }
}

void arv_imprime (Arv* a) {
    if(arv_vazia(a))
        printf("<>\n");
    else {
        printf("<%c%d", a->c, a->peso);
        imprime_aux(a->sae);
        imprime_aux(a->sad);
        printf(">\n");
    }
}

int arv_pertence (Arv* a, char c) {
    if(arv_vazia(a))
        return 0;
    else
        return a->c==c || arv_pertence(a->sae, c) || arv_pertence(a->sad, c);
}

char info (Arv* a) {
    return a->c;
}

int maior(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}

int altura (Arv* a) {
    if(arv_vazia(a))
        return -1;
    else
        return maior(altura(a->sae), altura(a->sad)) + 1;
}

Arv *arv_pai (Arv* a, char c) {
    if(arv_vazia(a))
        return NULL;
    if(info(a) == c)
        return NULL;
    if((!arv_vazia(a->sae) && info(a->sae)==c) || (!arv_vazia(a->sad) && info(a->sad)==c))
        return a;
    Arv *pai = arv_pai(a->sae, c);
    if(pai == NULL)
        pai = arv_pai(a->sad, c);
    return pai;
}

int arv_vazia (Arv* a) {
    if(a == NULL)
        return 1;
    else
        return 0;
}

int folhas (Arv* a) {
    if(arv_vazia(a))
        return 0;
    if(arv_vazia(a->sae) && arv_vazia(a->sad))
        return 1;
    return folhas(a->sae) + folhas(a->sad);
}

int ocorrencias (Arv* a, char c) {
    if(arv_vazia(a))
        return 0;
    if(info(a) == c)
        return ocorrencias(a->sae, c) + ocorrencias(a->sad, c) + 1;
    return ocorrencias(a->sae, c) + ocorrencias(a->sad, c);
}

Arv *arv_libera (Arv* a) {
    if(arv_vazia(a))
        return NULL;
    arv_libera(a->sae);
    arv_libera(a->sad);
    free(a);
    return NULL;
}

int get_peso (Arv *a) {
    return a->peso;
}

int folha(Arv *a) {
    if(a->sae==NULL && a->sae==NULL)
        return 1;
    return 0;
}

Arv *get_sae(Arv *a) {
    return a->sae;
}

Arv *get_sad(Arv *a) {
    return a->sad;
}