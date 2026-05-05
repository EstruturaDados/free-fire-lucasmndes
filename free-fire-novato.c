#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct para representar cada item da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Função para listar os itens
void listarItens(struct Item mochila[], int total) {
    int i;

    printf("\n===== ITENS NA MOCHILA =====\n");

    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------------\n");

    for (i = 0; i < total; i++) {
        printf("%-30s %-20s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função para buscar item pelo nome
void buscarItem(struct Item mochila[], int total) {
    char nomeBusca[30];
    int i, encontrado = 0;

    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("Item nao encontrado.\n");
    }
}

// Função para inserir item
void inserirItem(struct Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila esta cheia. Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[*total].nome);

    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[*total].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("Item cadastrado com sucesso.\n");
    listarItens(mochila, *total);
}

// Função para remover item pelo nome
void removerItem(struct Item mochila[], int *total) {
    char nomeRemover[30];
    int i, j, encontrado = 0;

    if (*total == 0) {
        printf("\nA mochila esta vazia. Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;

            for (j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;

            printf("Item removido com sucesso.\n");
            listarItens(mochila, *total);
            break;
        }
    }

    if (encontrado == 0) {
        printf("Item nao encontrado.\n");
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n======= MENU DO INVENTARIO =======\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                buscarItem(mochila, totalItens);
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
