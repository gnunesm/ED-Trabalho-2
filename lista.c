#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"

typedef struct cel Celula;

struct cel{
    Arv *arv;
    Celula *prox;
};

struct tipolista {
    Celula *prim;
    Celula *ult;
};

TipoLista* InicializaLista() {
    TipoLista *lista = (TipoLista *) malloc(sizeof(TipoLista));
    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}


// Insere no final
void Insere (Arv *a, TipoLista* lista) {
    Celula *cel = (Celula *) malloc(sizeof(Celula));
    cel->arv = a;
    cel->prox = NULL;
    if(lista->prim == NULL) {
        lista->prim = cel;
        lista->ult = cel;
    }
    else {
        lista->ult->prox = cel;
        lista->ult = cel;
    }
}

// void Imprime (TipoLista* lista) {
//     if(lista->prim == NULL)
//         printf("Lista vazia.\n");
//     else {
//         TipoItem *aluno;
//         for(Celula *aux=lista->prim;aux!=NULL;aux=aux->prox) {
//             aluno = aux->item;
//             printf("%s    %d    %s\n", aluno->nome, aluno->matricula, aluno->endereco);
//         }
//         printf("\n");
//     }
// }

Arv* Retira (TipoLista* lista, char c) {
    Celula *aux = lista->prim;
    Celula *ant = NULL;
    Arv *a;
    while(aux!=NULL) {
        if(info(aux->arv) == c) {
            if(ant == NULL)
                lista->prim = aux->prox;
            else
                ant->prox = aux->prox;
            a = aux->arv;
            free(aux);
            return a;
        }
        ant = aux;
        aux = aux->prox;
    }
    return NULL;
}

Arv* Pop (TipoLista* lista) {
    if(lista->prim != NULL) {
        Celula *c = lista->prim;
        lista->prim = c->prox;
        if(lista->prim == NULL)
            lista->ult = NULL;
        Arv *a = c->arv;
        free(c);
        return a;
    }
    return NULL;
}

TipoLista* Libera (TipoLista* lista) {
    Celula *aux = lista->prim;
    Celula *next;
    while(aux!=NULL) {
        // arv_libera(aux->arv);
        next = aux->prox;
        free(aux);
        aux = next;
    }
    free(lista);
    return NULL;
}

int unico(TipoLista *lista) {
    if(lista->prim->prox == NULL)
        return 1;
    return 0;
}

void Insere_ordenado (Arv *a, TipoLista* lista) {
    Celula *cel = (Celula *) malloc(sizeof(Celula));
    cel->arv = a;
    Celula *aux;
    if(lista->prim == NULL) {
        lista->prim = cel;
        lista->ult = cel;
        cel->prox = NULL;
    }
    else {
        if(get_peso(lista->prim->arv) <= get_peso(a)) {
            for(aux=lista->prim; aux->prox != NULL && get_peso(aux->prox->arv)<=get_peso(a); aux=aux->prox) {
            }
            cel->prox = aux->prox;
            aux->prox = cel;
        }
        else {
            cel->prox = lista->prim;
            lista->prim = cel;
        }
    }
}