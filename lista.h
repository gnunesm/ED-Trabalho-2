#ifndef LISTA_H_
#define LISTA_H_

#include "arvore.h"

/*Tipo que define a lista (tipo opaco).*/
typedef struct tipolista TipoLista;

/*Inicializa o sentinela de uma lista
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
TipoLista* InicializaLista();

/*Insere um no na ultima posicao da lista
* inputs: aluno a ser inserido na lista (do tipo TipoItem) e a lista
* output: nenhum
* pre-condicao: no e lista nao sao nulos
* pos-condicao: lista contem o no inserido na ultima posicao
*/
void Insere (Arv* a, TipoLista* lista);

/*Retira um no que contem o caractere c da lista
* inputs: a lista e o caractere a ser retirado da lista
* output: o no retirado da lista ou NULL, se o caractere nao se encontrar na lista
* pre-condicao: lista nao e nula
* pos-condicao: lista nao cont�m o no com caractere c
*/
Arv* Retira (TipoLista* lista, char c);

/*Libera toda a memoria alocada para a lista
* inputs: a lista de nos
* output: Lista vazia (NULL)
* pre-condicao: lista nao e nula
* pos-condicao: memoria alocada e liberada
*/
TipoLista* Libera (TipoLista* lista);

/*Verifica se existe um unico elemento na lista
* inputs: a lista de nos
* output: 1 caso apenas um elemento, 0 caso contrario
* pre-condicao: lista nao e nula
* pos-condicao: 1 retornado caso haja 1 elemento, 0 caso contrario
*/
int unico(TipoLista *lista);

/*Retira o primeiro elemento da lista
* inputs: a lista de nos
* output: o no retirado
* pre-condicao: lista nao e nula
* pos-condicao: lista sem primeiro elemento e elemento retirado retornado
*/
Arv* Pop (TipoLista* lista);

/*Insere um no na lista de forma ordenada
* inputs: a lista de nos
* output: nenhum
* pre-condicao: lista e no nao sao nulos
* pos-condicao: lista com o no inserido e ordenada de forma crescente
*/
void Insere_ordenado (Arv* a, TipoLista* lista);

#endif /* LISTA_H_ */
