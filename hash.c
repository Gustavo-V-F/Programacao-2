#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAMANHO 4000
#undef DEBUG

int funcao_hash(char* nome){
    if(nome == NULL){
        return -1;
    }
    char nome_aux[50];

    int i, tam, r_hash = {0};

    tam = strlen(nome);

    strcpy(nome_aux, nome);

    for(i = 0; i < tam; i++){
        if(nome_aux[i] < 91 && nome_aux[i] > 64){
            nome_aux[i] += 32;
        }

        r_hash += nome_aux[i];

    }

    return r_hash % TAMANHO;
}

void* pesquisar_tabela(lista_enc_t** tabela, char* autor){
    if(tabela == NULL || autor == NULL){
        perror("Erro na funcao: pesquisar_tabela");
        exit(EXIT_FAILURE);
    }

    int i = funcao_hash(autor);
    #ifdef DEBUG
            printf("%d\thash\n", i);
    #endif // DEBUG

    no_t* no;
    livros_t* livro;

    if(lista_vazia(tabela[i]) == 1){
        return NULL;
    }

    for(no = obter_cabeca(tabela[i]); no != NULL; no = obtem_proximo(no)){
        livro = obtem_dado(no);

        if(strcmp(autor, obter_autor(livro)) == 0){
            return livro;
        }
    }
    return NULL;
}


void adicionar_tabela(lista_enc_t** tabela, char* autor, char* nome){
    if(tabela == NULL || autor == NULL || nome == NULL){
        perror("Erro na funcao: adicionar_tabela");
    }

    livros_t* livro = pesquisar_tabela(tabela, autor);
    lista_enc_t* lista;
    no_t* no = NULL;
    int i;

    if(livro == NULL){
        i = funcao_hash(autor);
        lista = cria_lista();
        livro = cria_livro(lista, autor);
        no = cria_no(livro);
        add_cauda(tabela[i], no);
        inserir_livro(livro, nome);
    }else{
        lista = obter_livros(livro);
        inserir_livro(livro, nome);
    }
}

void deletar_tabela(lista_enc_t** tabela){
    if(tabela == NULL){
        perror("Erro na funcao: deletar_tabela");
        exit(EXIT_FAILURE);
    }

    int i;
    no_t* no;
    livros_t* livro;

    for(i = 0; i < TAMANHO; i++){
       for(no = obter_cabeca(tabela[i]); no != NULL; no = obter_cabeca(tabela[i])){
            livro = obtem_dado(no);

            if(livro != NULL){
                liberar_livro(livro);
                remover_cabeca(tabela[i]);
            }
        }
    }

}


void liberar_autor_tabela(lista_enc_t** tabela,char* autor){
    if(tabela == NULL || autor == NULL){
        perror("Erro na funcao:liberar_autor_tabela");
        exit(EXIT_FAILURE);
    }

    int i = funcao_hash(autor);

    no_t* no;
    livros_t* livro;

    for(no = obter_cabeca(tabela[i]); no != NULL; no = obtem_proximo(no)){
        livro = obtem_dado(no);

        if(strcmp(autor, obter_autor(livro)) == 0){
            liberar_livro(livro);
            remover_no(tabela[i], no);
            break;
        }
    }
}
