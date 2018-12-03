#ifndef ARVORE_H_
#define ARVORE_H_

typedef struct arv Arv;

/*Cria uma arvore vazia
* inputs: nenhum
* output: NULL
* pre-condicao: nenhuma
* pos-condicao: NULL retornado
*/
Arv* arv_criavazia (void);

/*Cria uma arvore vazia
* inputs: caractere c, inteiro peso, sub-arvores esquerda e direita
* output: no com as informacoes e sub-arvores criado
* pre-condicao: nenhuma
* pos-condicao: no alocado e informacoes guardadas
*/
Arv* arv_cria (unsigned char c, int peso, Arv* e, Arv* d);

/*Libera a memoria alocada para a arvore
* inputs: arvore a
* output: NULL
* pre-condicao: arvore nao e nula
* pos-condicao: memoria liberada e arvore apontando para NULL
*/
Arv* arv_libera (Arv* a);

/*Verifica se uma arvore e vazia
* inputs: arvore a
* output: 1 caso arvore seja vazia, 0 caso contrario
* pre-condicao: nenhuma
* pos-condicao: inteiro retornado
*/
int arv_vazia (Arv* a);

/*Verifica a ocorrencia do caractere c na arvore
* inputs: arvore a, caractere c a ser verificado
* output: 1 caso c exista na arv, 0 caso contrario
* pre-condicao: arvore nao e nula
* pos-condicao: inteiro retornado
*/
int arv_pertence (Arv* a, unsigned char c);

/*Imprime uma arvore
* inputs: arvore a
* output: nenhum
* pre-condicao: arvore nao e nula
* pos-condicao: arvore e nos impressos no stdout
*/
void arv_imprime (Arv* a);

/*Retorna o pai de dado no que contenha o caractere c
* inputs: arvore a, caractere c
* output: no pai do no que contenha c
* pre-condicao: arvore nao e nula
* pos-condicao: no pai retornado
*/
Arv* arv_pai (Arv* a, unsigned char c);

/*Conta a quantidade de folhas da arvore binaria
* inputs: arvore a
* output: numero de folhas
* pre-condicao: arvore nao e nula
* pos-condicao: inteiro com numero de folhas retornado
*/
int folhas (Arv* a);

/*Conta as ocorrencias de determinado caractere na arvore
* inputs: arvore a, caractere c
* output: numero de ocorrencias do caractere c
* pre-condicao: arvore nao e nula
* pos-condicao: inteiro correspondente as ocorrencias retornado
*/
int ocorrencias (Arv* a, unsigned char c);

/*Retorna o campo que contem caractere do no
* inputs: arvore a
* output: caractere contido no no
* pre-condicao: no nao e nulo
* pos-condicao: caractere retornado
*/
unsigned char info (Arv* a);

/*Retorna o campo que contem o peso do no
* inputs: no/arvore a
* output: inteiro contido no no
* pre-condicao: no nao e nulo
* pos-condicao: int peso retornado
*/
int get_peso (Arv *a);

/*Verifica altura de uma arvore
* inputs: arvore a
* output: altura da arvore
* pre-condicao: arvore nao e nula
* pos-condicao: inteiro altura retornado
*/
int altura (Arv* a);

/*Verifica se dado no e um no folha
* inputs: no/arvore a
* output: 1 caso no seja folha, 0 caso contrario
* pre-condicao: arvore nao e nula
* pos-condicao: inteiro resposta retornado
*/
int folha(Arv *a);

/*Retorna a sub-arvore esquerda de um no
* inputs: no a
* output: sub-arvore esquerda do no
* pre-condicao: no nao e nulo
* pos-condicao: sub-arvore retornada
*/
Arv *get_sae(Arv *a);

/*Retorna a sub-arvore direita de um no
* inputs: no a
* output: sub-arvore direita do no
* pre-condicao: no nao e nulo
* pos-condicao: sub-arvore retornada
*/
Arv *get_sad(Arv *a);

#endif /* ARVORE_H_ */