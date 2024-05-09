#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOSPEDES 100
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    int numero_quarto;
} Hospede;

void inserirHospede(Hospede hospedes[], int *num_hospedes);
void listarHospedes(Hospede hospedes[], int num_hospedes);
void buscarHospede(Hospede hospedes[], int num_hospedes);
void editarHospede(Hospede hospedes[], int num_hospedes);
void liberarQuarto(Hospede hospedes[], int *num_hospedes);
void mostrarQuartosVazios(Hospede hospedes[], int num_hospedes);
void salvarLista(Hospede hospedes[], int num_hospedes);
void carregarLista(Hospede hospedes[], int *num_hospedes);

int main() {
    Hospede hospedes[MAX_HOSPEDES];
    int num_hospedes = 0;
    
    carregarLista(hospedes, &num_hospedes);
    
    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir hospedes\n");
        printf("2. Listar hospedes por ordem alfabetica\n");
        printf("3. Buscar hospede\n");
        printf("4. Editar hospede\n");
        printf("5. Liberar um quarto\n");
        printf("6. Mostrar os numeros dos quartos vazios\n");
        printf("7. Salvar lista de hospedes com respectivos quartos em arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                inserirHospede(hospedes, &num_hospedes);
                break;
            case 2:
                listarHospedes(hospedes, num_hospedes);
                break;
            case 3:
                buscarHospede(hospedes, num_hospedes);
                break;
            case 4:
                editarHospede(hospedes, num_hospedes);
                break;
            case 5:
                liberarQuarto(hospedes, &num_hospedes);
                break;
            case 6:
                mostrarQuartosVazios(hospedes, num_hospedes);
                break;
            case 7:
                salvarLista(hospedes, num_hospedes);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (escolha != 0);

    return 0;
}

void inserirHospede(Hospede hospedes[], int *num_hospedes) {
    if (*num_hospedes < MAX_HOSPEDES) {
        printf("Digite o nome do hospede: ");
        scanf("%s", hospedes[*num_hospedes].nome);
        printf("Digite o numero do quarto: ");
        scanf("%d", &hospedes[*num_hospedes].numero_quarto);
        (*num_hospedes)++;
        printf("Hospede inserido com sucesso!\n");
        salvarLista(hospedes, *num_hospedes);
    } else {
        printf("Limite de hospedes atingido!\n");
    }
}

void listarHospedes(Hospede hospedes[], int num_hospedes) {
    if (num_hospedes == 0) {
        printf("Nenhum hospede cadastrado!\n");
        return;
    }
    
    Hospede temp;
    int i, j;
    for (i = 0; i < num_hospedes - 1; i++) {
        for (j = i + 1; j < num_hospedes; j++) {
            if (strcmp(hospedes[i].nome, hospedes[j].nome) > 0) {
                temp = hospedes[i];
                hospedes[i] = hospedes[j];
                hospedes[j] = temp;
            }
        }
    }
    
    printf("Lista de hospedes por ordem alfabetica:\n");
    for (i = 0; i < num_hospedes; i++) {
        printf("%s - Quarto %d\n", hospedes[i].nome, hospedes[i].numero_quarto);
    }
}

void buscarHospede(Hospede hospedes[], int num_hospedes) {
    if (num_hospedes == 0) {
        printf("Nenhum hospede cadastrado!\n");
        return;
    }
    
    char nomeBusca[MAX_NOME];
    printf("Digite o nome do hospede que deseja buscar: ");
    scanf("%s", nomeBusca);
    
    int i;
    for (i = 0; i < num_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nomeBusca) == 0) {
            printf("%s esta no quarto %d.\n", nomeBusca, hospedes[i].numero_quarto);
            return;
        }
    }
    
    printf("Hospede nao encontrado.\n");
}

void editarHospede(Hospede hospedes[], int num_hospedes) {
    if (num_hospedes == 0) {
        printf("Nenhum hospede cadastrado!\n");
        return;
    }
    
    char nomeEditar[MAX_NOME];
    printf("Digite o nome do hospede que deseja editar: ");
    scanf("%s", nomeEditar);
    
    int i;
    for (i = 0; i < num_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nomeEditar) == 0) {
            printf("Digite o novo numero do quarto: ");
            scanf("%d", &hospedes[i].numero_quarto);
            printf("Hospede editado com sucesso!\n");
            salvarLista(hospedes, num_hospedes);
            return;
        }
    }
    
    printf("Hospede nao encontrado.\n");
}

void liberarQuarto(Hospede hospedes[], int *num_hospedes) {
    if (*num_hospedes == 0) {
        printf("Nenhum hospede cadastrado!\n");
        return;
    }
    
    int numQuarto;
    printf("Digite o numero do quarto a ser liberado: ");
    scanf("%d", &numQuarto);
    
    int i;
    for (i = 0; i < *num_hospedes; i++) {
        if (hospedes[i].numero_quarto == numQuarto) {
            printf("%s foi liberado do quarto %d.\n", hospedes[i].nome, hospedes[i].numero_quarto);
            strcpy(hospedes[i].nome, "");
            hospedes[i].numero_quarto = 0;
            (*num_hospedes)--;
            salvarLista(hospedes, *num_hospedes);
            return;
        }
    }
    
    printf("Quarto nao encontrado ou vazio.\n");
}

void mostrarQuartosVazios(Hospede hospedes[], int num_hospedes) {
    int i;
    printf("Quartos vazios:\n");
    for (i = 1; i <= MAX_HOSPEDES; i++) {
        int ocupado = 0;
        int j;
        for (j = 0; j < num_hospedes; j++) {
            if (hospedes[j].numero_quarto == i) {
                ocupado = 1;
                break;
            }
        }
        if (!ocupado) {
            printf("Quarto %d\n", i);
        }
    }
}

void salvarLista(Hospede hospedes[], int num_hospedes) {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    int i;
    for (i = 0; i < num_hospedes; i++) {
        fprintf(arquivo, "%s %d\n", hospedes[i].nome, hospedes[i].numero_quarto);
    }
    
    fclose(arquivo);
}

void carregarLista(Hospede hospedes[], int *num_hospedes) {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de hospedes nao encontrado. Iniciando com lista vazia.\n");
        return;
    }
    
    while (fscanf(arquivo, "%s %d", hospedes[*num_hospedes].nome, &hospedes[*num_hospedes].numero_quarto) != EOF) {
        (*num_hospedes)++;
    }
    
    fclose(arquivo);
}
