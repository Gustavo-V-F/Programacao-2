#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "lista_enc.h"
#include "arquivo.h"

int funcao_hash(char* nome);
livros_t* pesquisar_tabela_nome(lista_enc_t** tabela ,char* nome);
livros_t* pesquisar_tabela_autor(lista_enc_t** tabela ,char* nome);
void adicionar_tabela_autor(lista_enc_t** tabela, char* autor);
void deletar_tabela(lista_enc_t** tabela, char* nome);
void liberar_livro_tabela(lista_enc_t** tabela, char* nome);

#endif // HASH_H_INCLUDED
