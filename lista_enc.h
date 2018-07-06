#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "no.h"

typedef struct lista_enc lista_enc_t;

lista_enc_t* cria_lista();

void add_cabeca(lista_enc_t* lista, no_t* dado);
void add_cauda(lista_enc_t* lista, no_t* dado);

no_t *obter_cabeca(lista_enc_t *lista);
no_t *obter_cauda(lista_enc_t *lista);

no_t * remover_cabeca(lista_enc_t* lista);
no_t *remover_cauda(lista_enc_t *lista);
void *remover_no(lista_enc_t *lista, no_t *no_removido);

int lista_vazia(lista_enc_t* lista);

int tamanho_lista(lista_enc_t* lista);

#endif // LISTA_ENC_H_INCLUDED
