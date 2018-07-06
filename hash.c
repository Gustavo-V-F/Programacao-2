#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAMANHO 4000
#define DEBUG

int funcao_hash(char* nome){
    if(nome == NULL){
        return -1;
    }

    int i, tam, r_hash = {0};

    tam = strlen(nome);

    for(i = 0; i < tam; i++){
        if(nome[i] < 91 && nome[i] > 64){
            nome[i] += 32;
        }

        r_hash += nome[i];

    }

    return r_hash % TAMANHO;
}

livros_t* pesquisar_tabela_nome(lista_enc_t** tabela, char* nome){
    if(tabela == NULL){
        perror("Erro na funcao: pesquisar_tabela");
        exit(EXIT_FAILURE);
    }else if(nome == NULL){
        exit(EXIT_FAILURE);
    }

    int i = funcao_hash(nome);

    no_t* no;
    livros_t* livro;

    for(no = obtem_dado(obter_cabeca(tabela[i])); no != NULL; no = obtem_proximo(no)){
        livro = obtem_dado(no);

        if(strcmp(nome, obter_nome(livro)) == 0){
            return livro;
        }
    }
    return NULL;
}

livros_t* pesquisar_tabela_autor(lista_enc_t** tabela,char* nome){
    if(tabela == NULL || nome == NULL){
        perror("Erro na funcao: pesquisar_tabela");
        exit(EXIT_FAILURE);
    }

    int i = funcao_hash(nome);
    #ifdef DEBUG
            printf("%d\n", i);
    #endif // DEBUG

    no_t* no;
    livros_t* livro;

    for(no = obter_cabeca(tabela[i]); no != NULL; no = obtem_proximo(no)){
        livro = obtem_dado(no);


        if(strcmp(nome, obter_autor(livro)) == 0){
            return livro;
        }
    }
    return NULL;
}


void adicionar_tabela_autor(lista_enc_t** tabela, char* autor){
    if(tabela == NULL || autor == NULL){
        perror("Erro na funcao: adicionar_tabela");
    }
    livros_t* livro = pesquisar_tabela_autor(tabela, autor);
    livros_t* livro_nov = NULL;
    no_t* no = NULL;
    int i = funcao_hash(autor);

    if(livro == NULL){
        livro_nov = cria_livro(NULL, autor);
        no = cria_no(livro_nov);
        add_cauda(tabela[i], no);
    }

}

void deletar_tabela(lista_enc_t** tabela, char* nome){
    if(tabela == NULL || nome == NULL){
        perror("Erro na funcao: deletar_tabela");
        exit(EXIT_FAILURE);
    }

    livros_t* livro = pesquisar_tabela_nome(tabela, nome);
    livros_t* autor = pesquisar_tabela_autor(tabela, nome);
    livros_t* livro_aux;

    if(livro == NULL && autor == NULL){
        puts("Livro/Autor inexistente.");
        return;
    }else if(livro != NULL){
        inserir_proximo(obter_proximo(livro), obter_anterior(livro));
        inserir_anterior(obter_anterior(livro), obter_proximo(livro));
        liberar_livro_tabela(tabela, obter_nome(livro));
    }else if(autor != NULL){
        for(livro = obter_proximo(autor); obter_nome(livro) != NULL; livro = livro_aux){
            livro_aux = obter_proximo(livro);
            liberar_livro_tabela(tabela, obter_nome(livro));
        }
    }

}


void liberar_livro_tabela(lista_enc_t** tabela,char* nome){
    if(tabela == NULL || nome == NULL){
        perror("Erro na funcao:liberar_tabela");
        exit(EXIT_FAILURE);
    }

    int i = funcao_hash(nome);

    no_t* no;
    livros_t* livro;

    for(no = obter_cabeca(tabela[i]); no != NULL; no = obtem_proximo(no)){
        livro = obtem_dado(no);

        if(strcmp(nome, obter_nome(livro)) == 0){
            liberar_livro(livro);
            remover_no(tabela[i], no);
            return;
        }
    }
}
