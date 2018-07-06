#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#include "lista_enc.h"
#include "hash.h"

typedef struct livros livros_t;

livros_t* cria_livro(lista_enc_t* lista, char* autor);

void inserir_livro(livros_t* livro, char* nome);

char* obter_autor(livros_t* livro);
lista_enc_t* obter_livros(livros_t* livro);
void imprimir_livros(lista_enc_t* lista);

lista_enc_t** ler_arquivo_livros(FILE* arquivo_livros);

int escrever_arquivo(lista_enc_t** lista, FILE* arquivo_livros, int tamanho);

void liberar_livro(livros_t* livro);

#endif // ARQUIVO_H_INCLUDED
