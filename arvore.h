#ifndef ARVORE_H_
#define ARVORE_H_

typedef struct arv Arv;

//Cria uma �rvore vazia
Arv* arv_criavazia (void);

//cria uma �rvore com a informa��o do n� raiz c, e
//com sub�rvore esquerda e e sub�rvore direita d
Arv* arv_cria (unsigned char c, int peso, Arv* e, Arv* d);

//libera o espa�o de mem�ria ocupado pela �rvore a
Arv* arv_libera (Arv* a);

//retorna true se a �rvore estiver vazia e false 
//caso contr�rio
int arv_vazia (Arv* a);

//indica a ocorr�ncia (1) ou n�o (0) do caracter c
int arv_pertence (Arv* a, unsigned char c);

//imprime as informa��es dos n�s da �rvore
void arv_imprime (Arv* a);

//retorna o pai de um dado no
Arv* arv_pai (Arv* a, unsigned char c);

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a);

//retorna o numero de ocorrencias de um dado caracter na arvore 
int ocorrencias (Arv* a, unsigned char c);

//retorna o campo informacao de um dado no
unsigned char info (Arv* a);

int get_peso (Arv *a);

//retorna a altura da arvore
int altura (Arv* a);

int folha(Arv *a);

Arv *get_sae(Arv *a);

Arv *get_sad(Arv *a);

#endif /* ARVORE_H_ */