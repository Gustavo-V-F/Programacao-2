#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "lista_enc.h"
#include "arquivo.h"

int funcao_hash(char* nome);
void* pesquisar_tabela(lista_enc_t** tabela ,char* nome);
void adicionar_tabela(lista_enc_t** tabela, char* autor, char* nome);
void deletar_tabela(lista_enc_t** tabela);
void liberar_autor_tabela(lista_enc_t** tabela, char* autor);

#endif // HASH_H_INCLUDED
