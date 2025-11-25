#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10


typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} Criterio;


typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;  
    int ativo;
} Item;


int insertionSort(Item v[], int n, Criterio c);
int comparar(Item a, Item b, Criterio c);
int buscaBinaria(Item v[], int n, char nome[]);

int main() {
    Item mochila[MAX_ITENS];
    int opcao, i;
    bool ordenadaPorNome = false;  

    
    for (i = 0; i < MAX_ITENS; i++)
        mochila[i].ativo = 0;

    do {
        printf("\n===== MENU DA MOCHILA =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (Sequencial)\n");
        printf("5. Ordenar mochila\n");
        printf("6. Buscar item (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: { 
            int pos = -1;
            for (i = 0; i < MAX_ITENS; i++)
                if (!mochila[i].ativo) { pos = i; break; }

            if (pos == -1) {
                printf("Mochila cheia!\n");
            } else {
                printf("Nome: ");
                scanf(" %[^\n]", mochila[pos].nome);

                printf("Tipo: ");
                scanf(" %[^\n]", mochila[pos].tipo);

                printf("Quantidade: ");
                scanf("%d", &mochila[pos].quantidade);

                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[pos].prioridade);

                mochila[pos].ativo = 1;
                ordenadaPorNome = false; // perdeu ordenação

                printf("Item adicionado!\n");
            }
        } break;

        case 2: { 
            char nomeBusca[50];
            bool encontrado = false;

            printf("Nome do item a remover: ");
            scanf(" %[^\n]", nomeBusca);

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo && strcmp(mochila[i].nome, nomeBusca) == 0) {
                    mochila[i].ativo = 0;
                    encontrado = true;
                    ordenadaPorNome = false;
                    printf("Item removido!\n");
                    break;
                }
            }

            if (!encontrado) printf("Item nao encontrado!\n");
        } break;

        case 3: 
            printf("\n===== ITENS =====\n");
            printf("%-15s %-15s %-10s %-10s\n",
                "Nome", "Tipo", "Qtd", "Prioridade");
            printf("----------------------------------------------\n");

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo) {
                    printf("%-15s %-15s %-10d %-10d\n",
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade,
                           mochila[i].prioridade);
                }
            }
            break;

        case 4: { 
            char nomeBusca[50];
            bool encontrado = false;

            printf("Nome do item a buscar: ");
            scanf(" %[^\n]", nomeBusca);

            for (i = 0; i < MAX_ITENS; i++) {
                if (mochila[i].ativo &&
                    strcmp(mochila[i].nome, nomeBusca) == 0) {

                    printf("\n===== ITEM ENCONTRADO =====\n");
                    printf("Nome: %s\n", mochila[i].nome);
                    printf("Tipo: %s\n", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);
                    printf("Prioridade: %d\n", mochila[i].prioridade);
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado)
                printf("Item nao encontrado!\n");
        } break;

        case 5: { 
            int escolha;
            printf("\nOrdenar por:\n");
            printf("1. Nome\n");
            printf("2. Tipo\n");
            printf("3. Prioridade\n");
            printf("Escolha: ");
            scanf("%d", &escolha);

            int comparacoes = insertionSort(mochila, MAX_ITENS, escolha);

            if (escolha == ORDENAR_NOME)
                ordenadaPorNome = true;
            else
                ordenadaPorNome = false;

            printf("Mochila ordenada!\n");
            printf("Comparacoes feitas: %d\n", comparacoes);
        } break;

        case 6: { 
            if (!ordenadaPorNome) {
                printf("A mochila precisa estar ordenada por NOME antes!\n");
                break;
            }

            char nomeBusca[50];
            printf("Nome para busca binaria: ");
            scanf(" %[^\n]", nomeBusca);

            int pos = buscaBinaria(mochila, MAX_ITENS, nomeBusca);

            if (pos == -1) {
                printf("Item NAO encontrado.\n");
            } else {
                printf("\n===== ITEM ENCONTRADO (BINARIO) =====\n");
                printf("Nome: %s\n", mochila[pos].nome);
                printf("Tipo: %s\n", mochila[pos].tipo);
                printf("Quantidade: %d\n", mochila[pos].quantidade);
                printf("Prioridade: %d\n", mochila[pos].prioridade);
            }

        } break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


int comparar(Item a, Item b, Criterio c) {
    if (!a.ativo && b.ativo) return 1;
    if (a.ativo && !b.ativo) return -1;

    switch (c) {
        case ORDENAR_NOME:
            return strcmp(a.nome, b.nome);

        case ORDENAR_TIPO:
            return strcmp(a.tipo, b.tipo);

        case ORDENAR_PRIORIDADE:
            return a.prioridade - b.prioridade;
    }
    return 0;
}


int insertionSort(Item v[], int n, Criterio c) {
    int comp = 0;

    for (int i = 1; i < n; i++) {
        Item atual = v[i];
        int j = i - 1;

        while (j >= 0 && (comp++, comparar(v[j], atual, c) > 0)) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;
    }
    return comp;
}


int buscaBinaria(Item v[], int n, char nome[]) {
    int inicio = 0;
    int fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (!v[meio].ativo) { 
            if (meio < fim) inicio = meio + 1;
            else return -1;
            continue;
        }

        int cmp = strcmp(nome, v[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
