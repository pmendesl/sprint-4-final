//INTEGRANTES//
//Alexandre Bertini RM: 563346//
//Leonardo Auhusto RM: 565564//
//Pedro Mendes RM: 562242 //
//Guilherme Peres RM: 563981 //
//Gabriel de Matos RM: 565218//


#include <stdio.h>
#include <stdlib.h>

// Definição da struct Dispositivo
typedef struct {
    char nome[50];
    float consumo; // consumo estimado em kWh
    int prioridade; // 1 = Alta, 2 = Média, 3 = Baixa
} Dispositivo;

// Protótipos das funções
void cadastrarDispositivo(Dispositivo *disp);
void exibirDispositivo(const Dispositivo *disp);

int main() {
    int numDispositivos;
    Dispositivo *vetorDispositivos;

    // Solicita a quantidade de dispositivos
    printf("Quantos dispositivos deseja cadastrar? ");
    scanf("%d", &numDispositivos);

    // Aloca memória dinamicamente para o vetor de dispositivos
    vetorDispositivos = (Dispositivo *)malloc(numDispositivos * sizeof(Dispositivo));

    // Verifica se a alocação foi bem-sucedida
    if (vetorDispositivos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1; // Retorna código de erro
    }

    // Cadastro dos dispositivos
    printf("\n--- Cadastro de Dispositivos ---\n");
    for (int i = 0; i < numDispositivos; i++) {
        printf("\nDispositivo %d:\n", i + 1);
        cadastrarDispositivo(&vetorDispositivos[i]);
    }

    // Exibição dos dispositivos cadastrados
    printf("\n--- Dispositivos Cadastrados ---\n");
    for (int i = 0; i < numDispositivos; i++) {
        exibirDispositivo(&vetorDispositivos[i]);
    }

    // Libera a memória alocada
    free(vetorDispositivos);

    return 0; // Programa executado com sucesso
}

// Função para cadastrar um dispositivo
void cadastrarDispositivo(Dispositivo *disp) {
    printf("Nome do dispositivo: ");
    // Limpa o buffer de entrada antes de ler a string
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(disp->nome, 50, stdin);
    // Remove a nova linha que fgets pode adicionar
    for(int i = 0; i < 50; i++){
        if(disp->nome[i] == '\n'){
            disp->nome[i] = '\0';
            break;
        }
    }

    printf("Consumo estimado (kWh): ");
    scanf("%f", &disp->consumo);

    printf("Prioridade (1=Alta, 2=Média, 3=Baixa): ");
    scanf("%d", &disp->prioridade);
}

// Função para exibir os dados de um dispositivo
void exibirDispositivo(const Dispositivo *disp) {
    printf("\nNome: %s\n", disp->nome);
    printf("Consumo: %.2f kWh\n", disp->consumo);
    printf("Prioridade: ");
    if (disp->prioridade == 1) {
        printf("Alta - Atenção! Consumo prioritário.\n");
    } else if (disp->prioridade == 2) {
        printf("Média - Consumo moderado.\n");
    } else if (disp->prioridade == 3) {
        printf("Baixa - Consumo pode ser otimizado.\n");
    } else {
        printf("Inválida - Prioridade não reconhecida.\n");
    }
}

