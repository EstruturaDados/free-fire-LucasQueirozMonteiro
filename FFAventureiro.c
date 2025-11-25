#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10


typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int ativo; 
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int opcao;
    int i;

    
    for (i = 0; i < MAX_ITENS; i++) {
        mochila[i].ativo = 0;
    }

    do {
        printf("\n===== MENU DA MOCHILA =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");   // 🔍 NOVA OPÇÃO
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            
            int pos = -1;
            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo == 0) {
                    pos = i;
                    break;
                }
            }

            if (pos == -1) {
                printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
            } else {
                printf("Digite o nome do item: ");
                scanf(" %[^\n]", mochila[pos].nome);

                printf("Digite o tipo do item: ");
                scanf(" %[^\n]", mochila[pos].tipo);

                printf("Digite a quantidade: ");
                scanf("%d", &mochila[pos].quantidade);

                mochila[pos].ativo = 1;

                printf("Item adicionado com sucesso!\n");
            }
            break;
        }

        case 2: {
            
            char nomeBusca[50];
            int encontrado = 0;

            printf("Digite o nome do item a remover: ");
            scanf(" %[^\n]", nomeBusca);

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeBusca) == 0) {
                    mochila[i].ativo = 0;
                    encontrado = 1;
                    printf("Item removido com sucesso!\n");
                    break;
                }
            }

            if (!encontrado) {
                printf("Item nao encontrado!\n");
            }

            break;
        }

        case 3:
         
            printf("\n===== ITENS NA MOCHILA =====\n");
            printf("%-20s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
            printf("----------------------------------------------------\n");

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo == 1) {
                    printf("%-20s %-20s %-10d\n",
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade);
                }
            }
            break;

        case 4: {
            // 🔍 
            char nomeBusca[50];
            int encontrado = 0;

            printf("Digite o nome do item que deseja buscar: ");
            scanf(" %[^\n]", nomeBusca);

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeBusca) == 0) {
                    encontrado = 1;

                    printf("\n===== ITEM ENCONTRADO =====\n");
                    printf("Nome: %s\n", mochila[i].nome);
                    printf("Tipo: %s\n", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);
                    break;
                }
            }

            if (!encontrado) {
                printf("Item nao encontrado!\n");
            }
            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
