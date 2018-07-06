#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "hash.h"

#undef DEBUG
#define TAMANHO 4000

struct livros{
    char* nome;
    char* autor;
    livros_t* proximo;
    livros_t* anterior;
};

livros_t* cria_livro(char* nome, char* autor){
    livros_t* livro = malloc(sizeof(livros_t));

    if(livro == NULL){
        perror("Erro em arquivo.c: cria_livro");
        exit(EXIT_FAILURE);
    }

    if(nome != NULL){
        livro->nome = malloc(strlen(nome));
        strcpy(livro->nome, nome);
    }
    livro->autor = malloc(strlen(autor));
    strcpy(livro->autor, autor);
    livro->proximo = NULL;
    livro->anterior = NULL;

    return livro;
}

char* obter_nome(livros_t* livro){
    if(livro == NULL){
        perror("Erro em arquivo.c: obter_nome");
        exit(EXIT_FAILURE);
    }else if(livro->nome == NULL){
        puts("Esse eh o dado do autor.");
        exit(EXIT_FAILURE);
    }

    return livro->nome;
}

char* obter_autor(livros_t* livro){
    if(livro == NULL || livro->autor == NULL){
       #ifdef DEBUG
            perror("Erro em arquivo.c: obter_autor");
       #endif // DEBUG
       return NULL;
    }

    return livro->autor;
}

livros_t* obter_proximo(livros_t* livro){
    if(livro == NULL){
       perror("Erro em arquivo.c: obter_proximo");
       exit(EXIT_FAILURE);
    }

    return livro->proximo;
}

livros_t* obter_anterior(livros_t* livro){
    if(livro == NULL){
       perror("Erro em arquivo.c: obter_anterior");
       exit(EXIT_FAILURE);
    }

    return livro->anterior;
}

void inserir_proximo(livros_t* livro, livros_t* proximo){
    if(livro == NULL || proximo == NULL){
       perror("Erro em arquivo.c: inserir_proximo");
       return;
    }

    livro->proximo = proximo;
}
void inserir_anterior(livros_t* livro, livros_t* anterior){
    if(livro == NULL || anterior == NULL){
       perror("Erro em arquivo.c: inserir_anterior");
       return;
    }

    livro->anterior = anterior;
}


lista_enc_t** ler_arquivo_livros(FILE* arquivo_livros){
    char string_aux[100] = {0};
    char string_nome[100] = {0};
    char string_autor[100] = {0};
    char string_buf[100] = {0};
    int count;
    lista_enc_t** lista = malloc(TAMANHO*sizeof(lista));

    for(count = 0; count < TAMANHO; count++){
        lista[count] = cria_lista();
    }

    for(count = 0; fgets(string_aux, 100, arquivo_livros) != NULL; count++){}

    count--;

    rewind(arquivo_livros);

    for(count = 0; fgets(string_aux, 100, arquivo_livros) != NULL; count++){
        sscanf(string_aux,"%99[^.]. %99[^–] – %99[^\n]", string_buf, string_nome, string_autor);
        #ifdef DEBUG
            puts(string_nome);
            puts(string_autor);
        #endif // DEBUG

        adicionar_tabela_autor(lista, string_autor);
    }

    return lista;
}

int escrever_arquivo(livros_t* livro, FILE* arquivo_livros_out, int tamanho){
    int i;

    for(i = 0; i < tamanho; i++){
        fwrite(livro[i].nome, 1, strlen(livro[i].nome), arquivo_livros_out);
        fwrite(livro[i].autor, 1, strlen(livro[i].autor), arquivo_livros_out);
    }

    return 0;
}

void liberar_livro(livros_t* livro){
    if(livro->nome != NULL){
        free(livro->nome);
    }
    free(livro->autor);
    free(livro);
}
