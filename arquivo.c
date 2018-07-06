#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

#undef DEBUG
#define TAMANHO 4000

struct livros{
    char autor[50];
    lista_enc_t* livros;
};

livros_t* cria_livro(lista_enc_t* lista, char* autor){
    livros_t* livro = malloc(sizeof(livros_t));

    /*#ifdef DEBUG
        printf("%d\n", strlen(autor));
        puts(nome);
    #endif // DEBUG*/

    if(livro == NULL || autor == NULL){
        perror("Erro em arquivo.c: cria_livro");
        exit(EXIT_FAILURE);
    }

    /*livro->autor = malloc(strlen(autor));

    if(livro->autor == NULL){
        perror("Erro em arquivo.c: cria_livro");
        exit(EXIT_FAILURE);
    }
    */
    strcpy(livro->autor, autor);

    livro->livros = lista;

    return livro;
}

void inserir_livro(livros_t* livro, char* nome){
    if(livro == NULL || nome == NULL){
        perror("Erro em arquivo.c: inserir_livro");
        exit(EXIT_FAILURE);
    }
    char* nome_aux = malloc(strlen(nome)+1);
    strcpy(nome_aux, nome);
    no_t* no = cria_no(nome_aux);
    add_cauda(livro->livros, no);
}

char* obter_autor(livros_t* livro){
    if(livro == NULL || livro->autor == NULL){
        perror("Erro em arquivo.c: obter_autor");
        return NULL;
    }

    return livro->autor;
}

lista_enc_t* obter_livros(livros_t* livro){
    if(livro == NULL || livro->livros == NULL){
        return NULL;
    }

    return livro->livros;
}

void imprimir_livros(lista_enc_t* lista){
    if(lista == NULL){
        perror("Erro em arquivo.c: imprimir_livros");
        exit(EXIT_FAILURE);
    }

    no_t* no;
    char* string;

    for(no = obter_cabeca(lista); no != NULL; no = obtem_proximo(no)){
        string = obtem_dado(no);
        puts(string);
    }

}

lista_enc_t** ler_arquivo_livros(FILE* arquivo_livros){
    char string_aux[300] = {0};
    char string_nome[50] = {0};
    char string_autor[100] = {0};
    char string_buf[100] = {0};
    int count;
    lista_enc_t** lista = malloc(TAMANHO*sizeof(lista_enc_t*));

    if(lista == NULL){
        perror("Erro em arquivo.c: ler_arquivo_livros");
        exit(EXIT_FAILURE);
    }

    for(count = 0; count < TAMANHO; count++){
        lista[count] = cria_lista();
    }

    for(count = 0; fgets(string_aux, 300, arquivo_livros) != NULL; count++){}

    rewind(arquivo_livros);

    for(count = 0; fgets(string_aux, 100, arquivo_livros) != NULL; count++){
        sscanf(string_aux,"%99[^.]. %99[^–] – %49[^\n]", string_buf, string_nome, string_autor);
        #ifdef DEBUG
            puts(string_nome);
            puts(string_autor);
            printf("%d\n", count);
        #endif // DEBUG

        adicionar_tabela(lista, string_autor, string_nome);
    }

    return lista;
}

int escrever_arquivo(lista_enc_t** lista, FILE* arquivo_livros, int tamanho){
    int i, j = 1;
    livros_t* livro;
    char string_aux[100];
    no_t* no;
    no_t* no_aux;

    for(i = 0; i < tamanho; i++){
        if(lista[i] != NULL){
            for(no = obter_cabeca(lista[i]); no != NULL; no = obtem_proximo(no)){
                livro = obtem_dado(no);
                for(no_aux = obter_cabeca(livro->livros); no_aux != NULL; no_aux = obtem_proximo(no_aux)){
                    fprintf(arquivo_livros, "%d.", j);
                    strcpy(string_aux, obtem_dado(no_aux));
                    fwrite(string_aux, sizeof(char), strlen(string_aux), arquivo_livros);
                    fprintf(arquivo_livros, " - ");
                    fwrite(livro->autor, sizeof(char), strlen(livro->autor), arquivo_livros);
                    fprintf(arquivo_livros, "\n");
                    j++;
                }
            }
        }
    }
    return i;
}

void liberar_livro(livros_t* livro){
    if(livro == NULL || livro->autor == NULL || livro->livros == NULL){
        perror("Erro em arquivo.c: cria_livro");
        exit(EXIT_FAILURE);
    }

    no_t* no;
    char* string;

    while(lista_vazia(livro->livros) == 0){
        no = remover_cabeca(livro->livros);
        string = obtem_dado(no);
        free(string);
        free(no);
    }

    free(livro->livros);
}
