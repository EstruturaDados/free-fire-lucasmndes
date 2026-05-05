#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// Struct do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para guardar comparações e tempo
long comparacoesBubble = 0;
long comparacoesInsertion = 0;
long comparacoesSelection = 0;
double tempoUltimoAlgoritmo = 0;

// Função para limpar o \n do fgets
void removerQuebraLinha(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

// Função para mostrar os componentes
void mostrarComponentes(Componente vetor[], int tamanho) {
    int i;

    printf("\n========= COMPONENTES CADASTRADOS =========\n");

    if (tamanho == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < tamanho; i++) {
        printf("%-30s %-20s %-10d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].prioridade);
    }
}

// Cadastro de componentes
void cadastrarComponentes(Componente vetor[], int *tamanho) {
    int continuar;

    do {
        if (*tamanho >= MAX) {
            printf("\nLimite maximo de 20 componentes atingido.\n");
            return;
        }

        printf("\nDigite o nome do componente: ");
        fgets(vetor[*tamanho].nome, 30, stdin);
        removerQuebraLinha(vetor[*tamanho].nome);

        printf("Digite o tipo do componente: ");
        fgets(vetor[*tamanho].tipo, 20, stdin);
        removerQuebraLinha(vetor[*tamanho].tipo);

        printf("Digite a prioridade (1 a 10): ");
        scanf("%d", &vetor[*tamanho].prioridade);
        getchar();

        (*tamanho)++;

        printf("Deseja cadastrar outro componente? (1 = sim / 0 = nao): ");
        scanf("%d", &continuar);
        getchar();

    } while (continuar == 1);

    mostrarComponentes(vetor, *tamanho);
}

// Bubble Sort por nome
void bubbleSortNome(Componente vetor[], int tamanho) {
    int i, j;
    Componente temp;

    comparacoesBubble = 0;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            comparacoesBubble++;

            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente vetor[], int tamanho) {
    int i, j;
    Componente chave;

    comparacoesInsertion = 0;

    for (i = 1; i < tamanho; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0) {
            comparacoesInsertion++;

            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }

        vetor[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente vetor[], int tamanho) {
    int i, j, menor;
    Componente temp;

    comparacoesSelection = 0;

    for (i = 0; i < tamanho - 1; i++) {
        menor = i;

        for (j = i + 1; j < tamanho; j++) {
            comparacoesSelection++;

            if (vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
        }
    }
}

// Medir tempo de um algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho) {
    clock_t inicio, fim;

    inicio = clock();
    algoritmo(vetor, tamanho);
    fim = clock();

    tempoUltimoAlgoritmo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Busca binária por nome
int buscaBinariaPorNome(Componente vetor[], int tamanho, char nomeBuscado[], int *comparacoes) {
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int resultado;

    *comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        (*comparacoes)++;

        resultado = strcmp(vetor[meio].nome, nomeBuscado);

        if (resultado == 0) {
            return meio;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

// Função para copiar vetor
void copiarVetor(Componente origem[], Componente destino[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

int main() {
    Componente componentes[MAX];
    Componente copia[MAX];
    int total = 0;
    int opcao;
    int indice;
    int comparacoesBusca;
    char nomeBusca[30];
    int ordenadoPorNome = 0;

    do {
        printf("\n============== MENU ==============\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Buscar componente-chave por nome (Busca Binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &total);
                ordenadoPorNome = 0;
                break;

            case 2:
                mostrarComponentes(componentes, total);
                break;

            case 3:
                if (total == 0) {
                    printf("\nNao ha componentes cadastrados.\n");
                } else {
                    copiarVetor(componentes, copia, total);
                    medirTempo(bubbleSortNome, copia, total);
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 1;

                    printf("\nComponentes ordenados por NOME com Bubble Sort.\n");
                    printf("Comparacoes: %ld\n", comparacoesBubble);
                    printf("Tempo de execucao: %.6f segundos\n", tempoUltimoAlgoritmo);
                    mostrarComponentes(componentes, total);
                }
                break;

            case 4:
                if (total == 0) {
                    printf("\nNao ha componentes cadastrados.\n");
                } else {
                    copiarVetor(componentes, copia, total);
                    medirTempo(insertionSortTipo, copia, total);
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 0;

                    printf("\nComponentes ordenados por TIPO com Insertion Sort.\n");
                    printf("Comparacoes: %ld\n", comparacoesInsertion);
                    printf("Tempo de execucao: %.6f segundos\n", tempoUltimoAlgoritmo);
                    mostrarComponentes(componentes, total);
                }
                break;

            case 5:
                if (total == 0) {
                    printf("\nNao ha componentes cadastrados.\n");
                } else {
                    copiarVetor(componentes, copia, total);
                    medirTempo(selectionSortPrioridade, copia, total);
                    copiarVetor(copia, componentes, total);
                    ordenadoPorNome = 0;

                    printf("\nComponentes ordenados por PRIORIDADE com Selection Sort.\n");
                    printf("Comparacoes: %ld\n", comparacoesSelection);
                    printf("Tempo de execucao: %.6f segundos\n", tempoUltimoAlgoritmo);
                    mostrarComponentes(componentes, total);
                }
                break;

            case 6:
                if (total == 0) {
                    printf("\nNao ha componentes cadastrados.\n");
                } else if (ordenadoPorNome == 0) {
                    printf("\nA busca binaria so pode ser usada depois de ordenar por NOME.\n");
                } else {
                    printf("\nDigite o nome do componente-chave: ");
                    fgets(nomeBusca, 30, stdin);
                    removerQuebraLinha(nomeBusca);

                    indice = buscaBinariaPorNome(componentes, total, nomeBusca, &comparacoesBusca);

                    if (indice != -1) {
                        printf("\nComponente-chave encontrado!\n");
                        printf("Nome: %s\n", componentes[indice].nome);
                        printf("Tipo: %s\n", componentes[indice].tipo);
                        printf("Prioridade: %d\n", componentes[indice].prioridade);
                    } else {
                        printf("\nComponente-chave nao encontrado.\n");
                    }

                    printf("Comparacoes na busca binaria: %d\n", comparacoesBusca);
                }
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
