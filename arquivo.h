#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include "lista_enc.h"


typedef struct livros livros_t;

livros_t* cria_livro(char* nome, char* autor);
char* obter_nome(livros_t* livro);
char* obter_autor(livros_t* livro);
livros_t* obter_proximo(livros_t* livro);
livros_t* obter_anterior(livros_t* livro);

void inserir_proximo(livros_t* livro, livros_t* proximo);
void inserir_anterior(livros_t* livro, livros_t* anterior);

lista_enc_t** ler_arquivo_livros(FILE* arquivo_livros);

int escrever_arquivo(livros_t* livro, FILE* arquivo_livros, int tamanho);

void liberar_livro(livros_t* livro);

#endif // ARQUIVO_H_INCLUDED
