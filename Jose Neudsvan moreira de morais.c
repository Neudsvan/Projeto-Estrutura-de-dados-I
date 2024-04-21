#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "item.h"
#include "usuario.h"

// Função para exibir as opções iniciais
int exibir_opcoes_iniciais()
{
    int opcao;
    printf("\nOpções iniciais:\n");
    printf("1. Cadastrar usuário\n");
    printf("2. Login\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// Função para exibir mensagem de boas-vindas
void mensagem_boas_vindas()
{
    printf("Bem-vindo ao Sistema de Compras!\n");
}

// Função para exibir menu de opções
int exibir_menu()
{
    int escolha;
    printf("\nMenu:\n");
    printf("1. Cadastrar item\n");
    printf("2. Listar itens\n");
    printf("3. Editar item\n");
    printf("4. Excluir item\n");
    printf("5. Buscar item\n");
    printf("6. Ordenar itens\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    return escolha;
}

// Função principal
int main()
{
    setlocale(LC_ALL, "Portuguese"); // Define a localidade para português

    // Opções iniciais
    int opcao;
    do
    {
        opcao = exibir_opcoes_iniciais();

        switch (opcao)
        {
        case 1:
            cadastrar_usuario();
            break;
        case 2:
            // Login
            while (!login())
                ;
            break;
        default:
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 2);

    // Mensagem de boas-vindas
    mensagem_boas_vindas();

    // Menu principal
    int escolha;
    int c;
    do
    {
        escolha = exibir_menu();

        switch (escolha)
        {
        case 1:
            cadastrar_item();
            break;
        case 2:
            listar_itens();
            break;
        case 3:
            printf("Informe o código do produto: ");
            scanf("%d", &c);
            editar_item(c);
            break;
        case 4:
            excluir_item();
            break;
        case 5:
            buscar_item();
            break;
        case 6:
            ordenarLista();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (escolha != 0);

    return 0;
}
