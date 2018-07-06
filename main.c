#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"
#include "hash.h"
#include "arquivo.h"

#undef DEBUG

int main()
{
    lista_enc_t** lista = NULL;

    FILE* arquivo_livro = fopen("livros.txt", "r");

    if(arquivo_livro == NULL){
        perror("Erro no main: fopen de livros.txt");
        exit(EXIT_FAILURE);
    }

    FILE* arquivo_livrob = fopen("livros.bin", "wb");

    if(arquivo_livrob == NULL){
        perror("Erro no main: fopen de livros.bin");
        fclose(arquivo_livro);
        exit(EXIT_FAILURE);
    }

    lista = ler_arquivo_livros(arquivo_livro);

    #ifdef DEBUG
        printf("%d\n", tamanho_lista(lista));
    #endif // DEBUG

    fclose(arquivo_livro);
    fclose(arquivo_livrob);
    //libera_lista(lista);

    puts("Finalizado!\n");

    exit(EXIT_SUCCESS);
}
