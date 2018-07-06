#include <stdio.h>
#include <stdlib.h>
#include "no.h"

#undef DEBUG

struct no{
    void* dado;
    void* proximo;
    void* anterior;
};

no_t* cria_no(void* dado){
    no_t* no = malloc(sizeof(no_t));

    if(no == NULL){
        perror("Erro na funcao: cria_no");
        exit(EXIT_FAILURE);
    }

    no->dado = dado;
    no->proximo = NULL;
    no->anterior = NULL;

    return no;
}

void liga_nos(no_t* no_p, no_t* no_s){
    if(no_p == NULL || no_s == NULL){
            fprintf(stderr, "Erro na funcao: liga_nos");
            exit(EXIT_FAILURE);
    }

    no_p->proximo = no_s;
    no_s->anterior = no_p;
}

void desliga_no(no_t* no){
    if(no == NULL){
        fprintf(stderr, "Erro na funcao: desliga_no");
        exit(EXIT_FAILURE);
    }

    no->proximo = NULL;
    no->anterior = NULL;
}

void desliga_no_anterior (no_t *no)
{
    if(no == NULL) {
        fprintf(stderr,"Erro na funcao: desliga_no_anterior");
        exit(EXIT_FAILURE);
    }

    no->anterior = NULL;
}

void desliga_no_proximo (no_t *no)
{
    if(no == NULL) {
        fprintf(stderr,"Erro na funcao: desliga_no_proximo");
        exit(EXIT_FAILURE);
    }

    no->proximo = NULL;
}

void* obtem_dado(no_t* no){
    if(no == NULL){
        fprintf(stderr, "Erro na funcao: obtem_dado");
        exit(EXIT_FAILURE);
    }

    return no->dado;
}

no_t* obtem_proximo(no_t* no){
    if(no == NULL){
        fprintf(stderr, "Erro na funcao: obtem_proximo");
        exit(EXIT_FAILURE);
    }

    return no->proximo;
}

no_t* obtem_anterior(no_t* no){
    if(no == NULL){
        fprintf(stderr, "Erro na funcao: obtem_proximo");
        exit(EXIT_FAILURE);
    }

    return no->anterior;
}
