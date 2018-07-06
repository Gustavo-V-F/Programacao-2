#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"

#undef DEBUG

struct lista_enc{
    no_t* cabeca;
    no_t* cauda;
    int tamanho;
};

lista_enc_t* cria_lista(){
    lista_enc_t* lista = malloc(sizeof(lista_enc_t));

    if(lista == NULL){
        perror("Erro na funcao: cria_lista");
        exit(EXIT_FAILURE);
    }

    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->tamanho = 0;

    return lista;
}

void add_cabeca(lista_enc_t* lista, no_t* no){
    if(lista == NULL || no == NULL){
        fprintf(stderr, "Erro na funcao: add_cabeca");
        exit(EXIT_FAILURE);
    }

    if(lista_vazia(lista) == 1){
        lista->cabeca = no;
        lista->cauda = no;
        lista->tamanho++;

        desliga_no(no);
    }else{
        liga_nos(no, lista->cabeca);

        lista->cabeca = no;
        lista->tamanho++;
    }
}

void add_cauda(lista_enc_t* lista, no_t* no){
    if(lista == NULL || no == NULL){
        fprintf(stderr, "Erro na funcao: add_cauda");
        exit(EXIT_FAILURE);
    }

    if(lista_vazia(lista) == 1){
        lista->cabeca = no;
        lista->cauda = no;
        lista->tamanho++;

        desliga_no(no);
    }else{
        desliga_no(no);

        liga_nos(lista->cauda, no);

        lista->cauda = no;
        lista->tamanho++;
    }
}

no_t *obter_cabeca(lista_enc_t *lista){

	if(lista == NULL){
	        #ifdef DEBUG
                fprintf(stderr,"Erro na funcao: obter_cabeca");
	        #endif // DEBUG
	        return NULL;
	    }

	return lista->cabeca;
}

no_t *obter_cauda(lista_enc_t *lista){

	if(lista == NULL){
	        fprintf(stderr,"Erro na funcao: obter_cauda");
	        exit(EXIT_FAILURE);
	    }

	return lista->cauda;
}

no_t *remover_cabeca(lista_enc_t *lista){
	no_t *proximo;
	no_t *removido;

	if(lista == NULL){
	    fprintf(stderr,"Erro na funcao: remover_cabeca");
	    exit(EXIT_FAILURE);
	}

	if(lista->cabeca == NULL){
		return NULL;
	}

	removido = lista->cabeca;

	if(lista->cauda == lista->cabeca){
		lista->tamanho = 0;

		lista->cauda = NULL;
		lista->cabeca = NULL;

		return removido;
	}

	proximo = obtem_proximo(lista->cabeca);
	desliga_no(removido);
	lista->cabeca = proximo;
	desliga_no_anterior(proximo);
	lista->tamanho--;


	return removido;
}

no_t *remover_cauda(lista_enc_t *lista){
	no_t *anterior;
	no_t *removido;

	if(lista == NULL){
	    fprintf(stderr,"Erro na funcao: remover_cauda");
	    exit(EXIT_FAILURE);
	}

	if(lista->cauda == NULL){
		return NULL;
	}

	removido = lista->cauda;

	if(lista->cauda == lista->cabeca) {
		lista->tamanho = 0;

		lista->cauda = NULL;
		lista->cabeca = NULL;

		return removido;
	}

	anterior = obtem_anterior(lista->cauda);
	desliga_no(removido);
	lista->cauda = anterior;
	desliga_no_proximo(anterior);
	lista->tamanho--;

	return removido;
}

void *remover_no(lista_enc_t *lista, no_t *no_removido){
	no_t *no;
	void *dado;

	no_t *proximo;
	no_t *anterior;

	if(lista == NULL || no_removido == NULL){
		fprintf(stderr,"Erro na funcao: remover_no");
		exit(EXIT_FAILURE);
	}

	no = obter_cabeca(lista);

	while(no){
		dado = obtem_dado(no);

		if (no == no_removido){

			if (no == lista->cabeca)
				remover_cabeca(lista);
			else if (no == lista->cauda)
				remover_cauda(lista);
			else
			{
				proximo = obtem_proximo(no);
				anterior = obtem_anterior(no);
				liga_nos(anterior, proximo);
				lista->tamanho--;
			}
			free(no);
			break;
		}
		no = obtem_proximo(no);
	}

	return dado;
}

int lista_vazia(lista_enc_t* lista){
    if(lista->tamanho == 0){
       return 1;
    }

    return 0;
}

int tamanho_lista(lista_enc_t* lista){
    if(lista == NULL){
        fprintf(stderr, "Erro na funcao: tamanho_lista");
        return -1;
    }

    return lista->tamanho;
}
