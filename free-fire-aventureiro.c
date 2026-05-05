#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct do item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Struct do nó da lista encadeada
struct No {
    struct Item dados;
    struct No *proximo;
};

// =========================
// FUNÇÕES DO VETOR
// =========================

// Inserir item no vetor
void inserirItemVetor(struct Item vetor[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nVetor cheio. Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", vetor[*total].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", vetor[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &vetor[*total].quantidade);

    (*total)++;
    printf("Item inserido no vetor com sucesso.\n");
}

// Remover item do vetor pelo nome
void removerItemVetor(struct Item vetor[], int *total) {
    char nome[30];
    int i, j, achou = 0;

    if (*total == 0) {
        printf("\nO vetor esta vazio.\n");
        return;
    }

    printf("\nDigite o nome do item para remover do vetor: ");
    scanf(" %[^\n]", nome);

    for (i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            achou = 1;

            for (j = i; j < *total - 1; j++) {
                vetor[j] = vetor[j + 1];
            }

            (*total)--;
            printf("Item removido do vetor com sucesso.\n");
            break;
        }
    }

    if (achou == 0) {
        printf("Item nao encontrado no vetor.\n");
    }
}

// Listar itens do vetor
void listarItensVetor(struct Item vetor[], int total) {
    int i;

    printf("\n===== ITENS NO VETOR =====\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------------\n");

    for (i = 0; i < total; i++) {
        printf("%-30s %-20s %-10d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].quantidade);
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor(struct Item vetor[], int total) {
    char nome[30];
    int i, comparacoes = 0, achou = 0;

    if (total == 0) {
        printf("\nO vetor esta vazio.\n");
        return;
    }

    printf("\nDigite o nome do item para buscar no vetor: ");
    scanf(" %[^\n]", nome);

    for (i = 0; i < total; i++) {
        comparacoes++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("\nItem encontrado no vetor:\n");
            printf("Nome: %s\n", vetor[i].nome);
            printf("Tipo: %s\n", vetor[i].tipo);
            printf("Quantidade: %d\n", vetor[i].quantidade);
            achou = 1;
            break;
        }
    }

    if (achou == 0) {
        printf("Item nao encontrado no vetor.\n");
    }

    printf("Comparacoes na busca sequencial do vetor: %d\n", comparacoes);
}

// Ordenar vetor por nome usando Bubble Sort
void ordenarVetor(struct Item vetor[], int total) {
    int i, j;
    struct Item temp;

    if (total == 0) {
        printf("\nO vetor esta vazio.\n");
        return;
    }

    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - 1 - i; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("\nVetor ordenado por nome com sucesso.\n");
}

// Busca binária no vetor
void buscarBinariaVetor(struct Item vetor[], int total) {
    char nome[30];
    int inicio = 0, fim = total - 1, meio;
    int comparacoes = 0, resultado;

    if (total == 0) {
        printf("\nO vetor esta vazio.\n");
        return;
    }

    printf("\nDigite o nome do item para busca binaria no vetor: ");
    scanf(" %[^\n]", nome);

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;

        resultado = strcmp(vetor[meio].nome, nome);

        if (resultado == 0) {
            printf("\nItem encontrado na busca binaria:\n");
            printf("Nome: %s\n", vetor[meio].nome);
            printf("Tipo: %s\n", vetor[meio].tipo);
            printf("Quantidade: %d\n", vetor[meio].quantidade);
            printf("Comparacoes na busca binaria: %d\n", comparacoes);
            return;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item nao encontrado na busca binaria.\n");
    printf("Comparacoes na busca binaria: %d\n", comparacoes);
}

// =========================
// FUNÇÕES DA LISTA
// =========================

// Inserir item na lista encadeada
void inserirItemLista(struct No **inicio) {
    struct No *novo = (struct No *) malloc(sizeof(struct No));

    if (novo == NULL) {
        printf("Erro de memoria.\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        struct No *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    printf("Item inserido na lista com sucesso.\n");
}

// Remover item da lista pelo nome
void removerItemLista(struct No **inicio) {
    char nome[30];
    struct No *atual = *inicio;
    struct No *anterior = NULL;

    if (*inicio == NULL) {
        printf("\nA lista esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item para remover da lista: ");
    scanf(" %[^\n]", nome);

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na lista.\n");
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item removido da lista com sucesso.\n");
}

// Listar itens da lista
void listarItensLista(struct No *inicio) {
    struct No *atual = inicio;

    printf("\n===== ITENS NA LISTA =====\n");

    if (inicio == NULL) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------------\n");

    while (atual != NULL) {
        printf("%-30s %-20s %-10d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista
void buscarSequencialLista(struct No *inicio) {
    char nome[30];
    int comparacoes = 0;
    struct No *atual = inicio;

    if (inicio == NULL) {
        printf("\nA lista esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item para buscar na lista: ");
    scanf(" %[^\n]", nome);

    while (atual != NULL) {
        comparacoes++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado na lista:\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparacoes na busca sequencial da lista: %d\n", comparacoes);
            return;
        }

        atual = atual->proximo;
    }

    printf("Item nao encontrado na lista.\n");
    printf("Comparacoes na busca sequencial da lista: %d\n", comparacoes);
}

// Liberar memória da lista
void liberarLista(struct No **inicio) {
    struct No *atual = *inicio;
    struct No *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    *inicio = NULL;
}

// =========================
// MENU
// =========================

int main() {
    struct Item vetor[MAX_ITENS];
    int totalVetor = 0;

    struct No *lista = NULL;

    int opcao;

    do {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1 - Inserir item no vetor\n");
        printf("2 - Remover item do vetor\n");
        printf("3 - Listar itens do vetor\n");
        printf("4 - Buscar sequencial no vetor\n");
        printf("5 - Ordenar vetor por nome\n");
        printf("6 - Buscar binaria no vetor\n");
        printf("7 - Inserir item na lista\n");
        printf("8 - Remover item da lista\n");
        printf("9 - Listar itens da lista\n");
        printf("10 - Buscar sequencial na lista\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItemVetor(vetor, &totalVetor);
                break;

            case 2:
                removerItemVetor(vetor, &totalVetor);
                break;

            case 3:
                listarItensVetor(vetor, totalVetor);
                break;

            case 4:
                buscarSequencialVetor(vetor, totalVetor);
                break;

            case 5:
                ordenarVetor(vetor, totalVetor);
                break;

            case 6:
                buscarBinariaVetor(vetor, totalVetor);
                break;

            case 7:
                inserirItemLista(&lista);
                break;

            case 8:
                removerItemLista(&lista);
                break;

            case 9:
                listarItensLista(lista);
                break;

            case 10:
                buscarSequencialLista(lista);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);

    return 0;
}
