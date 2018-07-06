#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_enc.h"
#include "hash.h"
#include "arquivo.h"

#undef DEBUG
#define TAMANHO 4000

int main()
{
    lista_enc_t* livros;
    lista_enc_t** lista;
    int i;
    char string_autor[25];
    char string_autor2[25];
    char string_livro[100];

    FILE* arquivo_livro = fopen("livros.txt", "r");

    if(arquivo_livro == NULL){
        perror("Erro no main: fopen de livros.txt");
        exit(EXIT_FAILURE);
    }

    FILE* arquivo_livro_mod = fopen("livros_mod.txt", "w");

    if(arquivo_livro_mod == NULL){
        perror("Erro no main: fopen de livros_mod.txt");
        exit(EXIT_FAILURE);
    }

    lista = ler_arquivo_livros(arquivo_livro);

     do{
        puts("Selecione a opcao desejada:");
        puts("1. Adicionar livro na biblioteca.");
        puts("2. Pesquisar livros do autor na biblioteca.");
        puts("3. Retirar livros de um autor da biblioteca.");
        puts("4. Sair.\n");
        scanf("%d", &i);
        getchar();

        switch(i){
        case 1:
            puts("\n\n");
            puts("Digite o nome do autor:");
            fscanf(stdin, "%s", string_autor);
            getchar();
            puts("Digite o sobrenome do autor:");
            fscanf(stdin, "%s", string_autor2);
            getchar();
            puts("Digite o nome do livro:");
            fscanf(stdin, "%s", string_livro);
            getchar();

            strcat(string_autor, " ");
            strcat(string_autor, string_autor2);

            adicionar_tabela(lista, string_autor, string_livro);
            puts("\n\n");
            break;
        case 2:
            puts("\n\n");
            puts("Digite o nome do autor:");
            fscanf(stdin, "%s", string_autor);
            getchar();
            puts("Digite o sobrenome do autor:");
            fscanf(stdin, "%s", string_autor2);
            getchar();

            strcat(string_autor, " ");
            strcat(string_autor, string_autor2);

            livros = obter_livros(pesquisar_tabela(lista, string_autor));
            puts("\n\n======================");
            if(livros == NULL){
                puts("Autor inexistente");
            }else{
                imprimir_livros(livros);
            }
            puts("======================\n\n");
            break;
        case 3:
            puts("\n\n");
            puts("Digite o nome do autor:");
            fscanf(stdin, "%s", string_autor);
            getchar();
            puts("Digite o sobrenome do autor:");
            fscanf(stdin, "%s", string_autor2);
            getchar();

            strcat(string_autor, " ");
            strcat(string_autor, string_autor2);

            liberar_autor_tabela(lista, string_autor);
            puts("\n\n");
            break;
        case 4:
            puts("\nPressione enter para sair...");
            getchar();
            break;
        default:
            puts("Opcao invalida!");
            puts("\nPressione enter para continuar.");
            getchar();
            break;
        }
    }while(i !=4);

    #ifdef DEBUG
        printf("%d\n", tamanho_lista(lista));
    #endif // DEBUG

    escrever_arquivo(lista, arquivo_livro_mod, TAMANHO);

    fclose(arquivo_livro);
    fclose(arquivo_livro_mod);

    deletar_tabela(lista);

    puts("Finalizado!\n");

    exit(EXIT_SUCCESS);
}
