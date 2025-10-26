/*******************************************************************************
 * SPRINT 4 - CONSOLIDAÇÃO E ANÁLISE DE DESEMPENHO
 * 
 * Objetivo: Consolidar código em C com cadastro dinâmico, simulação de decisão 
 * de consumo com múltiplos algoritmos de ordenação e comparação de desempenho.
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para medir o tempo de execução
#include <ctype.h> // Para tolower

#define MAX_NOME 50

// Estrutura para representar um dispositivo
typedef struct {
    char nome[MAX_NOME];
    float consumo;     // Consumo em kWh
    int prioridade;    // Quanto menor o número, maior a prioridade (1 = máxima prioridade)
    int status;        // 1 = ligado, 0 = desligado
} Dispositivo;

// Estrutura para armazenar o vetor dinâmico e seu tamanho
typedef struct {
    Dispositivo *dispositivos;
    int numDispositivos;
    int capacidade;
} ListaDispositivos;

// Variáveis globais para análise de desempenho
long long comparacoes = 0;
long long trocas = 0;

// Protótipos das funções
void exibirMenu();
void resetarContadores();
void copiarDispositivos(Dispositivo *origem, Dispositivo *destino, int numDispositivos);
float calcularConsumoTotal(ListaDispositivos *lista);

// Funções de Gerenciamento de Lista Dinâmica
ListaDispositivos *inicializarLista();
void adicionarDispositivo(ListaDispositivos *lista, Dispositivo novoDispositivo);
void cadastrarDispositivo(ListaDispositivos *lista);
void listarDispositivos(ListaDispositivos *lista);

// Funções de Simulação e Ordenação (a serem implementadas na Fase 3)
void simularConsumoInteligente(ListaDispositivos *lista);
void bubbleSort(Dispositivo *dispositivos, int numDispositivos);
void selectionSort(Dispositivo *dispositivos, int numDispositivos);
void insertionSort(Dispositivo *dispositivos, int numDispositivos); // Novo algoritmo
void mergeSort(Dispositivo *dispositivos, int numDispositivos); // Novo algoritmo
void quickSort(Dispositivo *dispositivos, int numDispositivos); // Novo algoritmo
void compararAlgoritmos(ListaDispositivos *lista);

// Funções de Persistência (Simplificadas para esta fase)
void salvarDispositivos(ListaDispositivos *lista);
void carregarDispositivos(ListaDispositivos *lista);


// Implementação das Funções de Gerenciamento de Lista Dinâmica
ListaDispositivos *inicializarLista() {
    ListaDispositivos *lista = (ListaDispositivos *)malloc(sizeof(ListaDispositivos));
    if (lista == NULL) {
        perror("Erro ao alocar memória para a lista");
        exit(EXIT_FAILURE);
    }
    lista->numDispositivos = 0;
    lista->capacidade = 10; // Capacidade inicial
    lista->dispositivos = (Dispositivo *)malloc(lista->capacidade * sizeof(Dispositivo));
    if (lista->dispositivos == NULL) {
        perror("Erro ao alocar memória para dispositivos");
        free(lista);
        exit(EXIT_FAILURE);
    }
    return lista;
}

void adicionarDispositivo(ListaDispositivos *lista, Dispositivo novoDispositivo) {
    if (lista->numDispositivos >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->dispositivos = (Dispositivo *)realloc(lista->dispositivos, lista->capacidade * sizeof(Dispositivo));
        if (lista->dispositivos == NULL) {
            perror("Erro ao realocar memória para dispositivos");
            exit(EXIT_FAILURE);
        }
    }
    lista->dispositivos[lista->numDispositivos++] = novoDispositivo;
}

void cadastrarDispositivo(ListaDispositivos *lista) {
    Dispositivo novoDispositivo;
    printf("\n--- Cadastro de Novo Dispositivo ---\n");
    
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Nome do Dispositivo (max %d caracteres): ", MAX_NOME - 1);
    // fgets é mais seguro que scanf para strings
    if (fgets(novoDispositivo.nome, MAX_NOME, stdin) != NULL) {
        // Remove a quebra de linha se estiver presente
        novoDispositivo.nome[strcspn(novoDispositivo.nome, "\n")] = 0;
    } else {
        printf("Erro de leitura.\n");
        return;
    }

    printf("Consumo em kWh (ex: 0.5): ");
    if (scanf("%f", &novoDispositivo.consumo) != 1 || novoDispositivo.consumo <= 0) {
        printf("Entrada inválida para consumo. Cadastro cancelado.\n");
        // Limpa o buffer de entrada
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Prioridade (1=Alta, 2=Media, 3=Baixa): ");
    if (scanf("%d", &novoDispositivo.prioridade) != 1 || novoDispositivo.prioridade < 1 || novoDispositivo.prioridade > 3) {
        printf("Entrada inválida para prioridade. Cadastro cancelado.\n");
        // Limpa o buffer de entrada
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    novoDispositivo.status = 1; // Inicialmente ligado
    adicionarDispositivo(lista, novoDispositivo);
    printf("\nDispositivo '%s' cadastrado com sucesso!\n", novoDispositivo.nome);
    
    // Limpa o buffer de entrada
    while ((c = getchar()) != '\n' && c != EOF);
}

void listarDispositivos(ListaDispositivos *lista) {
    if (lista->numDispositivos == 0) {
        printf("\nNenhum dispositivo cadastrado.\n");
        return;
    }
    printf("\n--- Dispositivos Cadastrados (%d) ---\n", lista->numDispositivos);
    for (int i = 0; i < lista->numDispositivos; i++) {
        printf("%d. Nome: %s | Consumo: %.2f kWh | Prioridade: %d | Status: %s\n",
               i + 1,
               lista->dispositivos[i].nome,
               lista->dispositivos[i].consumo,
               lista->dispositivos[i].prioridade,
               lista->dispositivos[i].status ? "LIGADO" : "DESLIGADO");
    }
    printf("Consumo Total Estimado: %.2f kWh\n", calcularConsumoTotal(lista));
}

// Implementação das funções auxiliares
void exibirMenu() {
    printf("\n============================================\n");
    printf("       MENU - SIMULAÇÃO DE CONSUMO (S4)       \n");
    printf("============================================\n");
    printf("1. Cadastrar Novo Dispositivo (Dinâmico)\n");
    printf("2. Listar Dispositivos Cadastrados\n");
    printf("3. Simular Decisão de Consumo Inteligente\n");
    printf("4. Comparar Desempenho de Algoritmos de Ordenação\n");
    printf("5. Salvar Dispositivos\n");
    printf("6. Sair\n");
    printf("--------------------------------------------\n");
}

float calcularConsumoTotal(ListaDispositivos *lista) {
    float total = 0.0;
    for (int i = 0; i < lista->numDispositivos; i++) {
        if (lista->dispositivos[i].status == 1) {
            total += lista->dispositivos[i].consumo;
        }
    }
    return total;
}

void resetarContadores() {
    comparacoes = 0;
    trocas = 0;
}

void copiarDispositivos(Dispositivo *origem, Dispositivo *destino, int numDispositivos) {
    memcpy(destino, origem, numDispositivos * sizeof(Dispositivo));
}

// Funções de Persistência (Simplificadas)
void salvarDispositivos(ListaDispositivos *lista) {
    FILE *arquivo = fopen("dispositivos.dat", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para salvar");
        return;
    }
    fwrite(&lista->numDispositivos, sizeof(int), 1, arquivo);
    fwrite(lista->dispositivos, sizeof(Dispositivo), lista->numDispositivos, arquivo);
    fclose(arquivo);
    printf("\n%d dispositivos salvos com sucesso!\n", lista->numDispositivos);
}

void carregarDispositivos(ListaDispositivos *lista) {
    FILE *arquivo = fopen("dispositivos.dat", "rb");
    if (arquivo == NULL) {
        // Arquivo não existe ou erro, retorna com lista vazia
        return; 
    }
    
    int numCarregados;
    if (fread(&numCarregados, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return;
    }

    // Garante que a lista tem capacidade suficiente
    if (numCarregados > lista->capacidade) {
        lista->capacidade = numCarregados;
        lista->dispositivos = (Dispositivo *)realloc(lista->dispositivos, lista->capacidade * sizeof(Dispositivo));
        if (lista->dispositivos == NULL) {
            perror("Erro ao realocar memória para carregar dispositivos");
            fclose(arquivo);
            exit(EXIT_FAILURE);
        }
    }

    if (fread(lista->dispositivos, sizeof(Dispositivo), numCarregados, arquivo) != numCarregados) {
        printf("Erro ao ler dados dos dispositivos.\n");
        fclose(arquivo);
        return;
    }
    
    lista->numDispositivos = numCarregados;
    fclose(arquivo);
    printf("\n%d dispositivos carregados do arquivo.\n", lista->numDispositivos);
}

// Implementações de Ordenação
void bubbleSort(Dispositivo *dispositivos, int numDispositivos) {
    resetarContadores();
    int i, j;
    Dispositivo temp;
    for (i = 0; i < numDispositivos - 1; i++) {
        for (j = 0; j < numDispositivos - i - 1; j++) {
            comparacoes++;
            // Ordena por prioridade (menor número = maior prioridade)
            if (dispositivos[j].prioridade > dispositivos[j + 1].prioridade) {
                trocas++;
                temp = dispositivos[j];
                dispositivos[j] = dispositivos[j + 1];
                dispositivos[j + 1] = temp;
            }
        }
    }
}

void selectionSort(Dispositivo *dispositivos, int numDispositivos) {
    resetarContadores();
    int i, j, min_idx;
    Dispositivo temp;
    for (i = 0; i < numDispositivos - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < numDispositivos; j++) {
            comparacoes++;
            // Encontra o dispositivo com a maior prioridade (menor número)
            if (dispositivos[j].prioridade < dispositivos[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o elemento encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            trocas++;
            temp = dispositivos[min_idx];
            dispositivos[min_idx] = dispositivos[i];
            dispositivos[i] = temp;
        }
    }
}

void insertionSort(Dispositivo *dispositivos, int numDispositivos) {
    resetarContadores();
    int i, j;
    Dispositivo chave;
    for (i = 1; i < numDispositivos; i++) {
        chave = dispositivos[i];
        j = i - 1;

        /* Move os elementos de dispositivos[0..i-1], que são maiores que a chave (menor prioridade),
           para uma posição à frente de sua posição atual */
        while (j >= 0) {
            comparacoes++;
            if (dispositivos[j].prioridade > chave.prioridade) {
                trocas++;
                dispositivos[j + 1] = dispositivos[j];
                j = j - 1;
            } else {
                break; // A chave encontrou sua posição
            }
        }
        dispositivos[j + 1] = chave;
    }
}

// Função auxiliar para Merge Sort
void merge(Dispositivo *dispositivos, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários
    Dispositivo *L = (Dispositivo *)malloc(n1 * sizeof(Dispositivo));
    Dispositivo *R = (Dispositivo *)malloc(n2 * sizeof(Dispositivo));
    if (!L || !R) {
        perror("Erro de alocação em merge");
        if (L) free(L);
        if (R) free(R);
        return;
    }

    // Copia dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = dispositivos[l + i];
    for (j = 0; j < n2; j++)
        R[j] = dispositivos[m + 1 + j];

    // Merge dos arrays temporários de volta para dispositivos[l..r]
    i = 0; // Índice inicial do primeiro sub-array
    j = 0; // Índice inicial do segundo sub-array
    k = l; // Índice inicial do sub-array merged
    while (i < n1 && j < n2) {
        comparacoes++;
        // Ordena por prioridade (menor número = maior prioridade)
        if (L[i].prioridade <= R[j].prioridade) {
            dispositivos[k] = L[i];
            i++;
        } else {
            dispositivos[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        dispositivos[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        dispositivos[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

// Função principal que implementa Merge Sort
void mergeSortRec(Dispositivo *dispositivos, int l, int r) {
    if (l < r) {
        // Encontra o ponto médio
        int m = l + (r - l) / 2;

        // Ordena a primeira e a segunda metade
        mergeSortRec(dispositivos, l, m);
        mergeSortRec(dispositivos, m + 1, r);

        merge(dispositivos, l, m, r);
    }
}

void mergeSort(Dispositivo *dispositivos, int numDispositivos) {
    resetarContadores();
    mergeSortRec(dispositivos, 0, numDispositivos - 1);
}

// Função auxiliar para Quick Sort
int partition(Dispositivo *dispositivos, int low, int high) {
    // Escolhe o pivô (último elemento)
    int pivot = dispositivos[high].prioridade; 
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        comparacoes++;
        // Se o elemento atual for menor ou igual ao pivô
        if (dispositivos[j].prioridade <= pivot) {
            i++; // Incrementa o índice do menor elemento
            // Troca dispositivos[i] e dispositivos[j]
            if (i != j) {
                trocas++;
                Dispositivo temp = dispositivos[i];
                dispositivos[i] = dispositivos[j];
                dispositivos[j] = temp;
            }
        }
    }
    // Troca dispositivos[i + 1] e dispositivos[high] (pivô)
    if (i + 1 != high) {
        trocas++;
        Dispositivo temp = dispositivos[i + 1];
        dispositivos[i + 1] = dispositivos[high];
        dispositivos[high] = temp;
    }
    return (i + 1);
}

// Função principal que implementa Quick Sort
void quickSortRec(Dispositivo *dispositivos, int low, int high) {
    if (low < high) {
        // pi é o índice de partição, dispositivos[pi] está agora no lugar certo
        int pi = partition(dispositivos, low, high);

        // Separa os elementos antes e depois da partição
        quickSortRec(dispositivos, low, pi - 1);
        quickSortRec(dispositivos, pi + 1, high);
    }
}

void quickSort(Dispositivo *dispositivos, int numDispositivos) {
    resetarContadores();
    quickSortRec(dispositivos, 0, numDispositivos - 1);
}

void simularConsumoInteligente(ListaDispositivos *lista) {
    if (lista->numDispositivos == 0) {
        printf("\nNenhum dispositivo cadastrado para simulação.\n");
        return;
    }

    float energiaDisponivel;
    printf("\n--- Simulação de Consumo Inteligente ---\n");
    printf("Informe o limite de energia disponível (em kWh): ");
    if (scanf("%f", &energiaDisponivel) != 1 || energiaDisponivel <= 0) {
        printf("Entrada inválida para energia disponível. Simulação cancelada.\n");
        return;
    }

    // Cria uma cópia da lista para ordenação e simulação
    ListaDispositivos listaSimulacao = *lista;
    listaSimulacao.dispositivos = (Dispositivo *)malloc(lista->numDispositivos * sizeof(Dispositivo));
    if (listaSimulacao.dispositivos == NULL) {
        perror("Erro ao alocar memória para simulação");
        return;
    }
    copiarDispositivos(lista->dispositivos, listaSimulacao.dispositivos, lista->numDispositivos);

    // 1. Ordena os dispositivos pela prioridade (usando Selection Sort como padrão para a simulação)
    // O Selection Sort é escolhido aqui, mas o usuário pode ser perguntado sobre qual usar
    printf("\nOrdenando dispositivos por prioridade (Selection Sort)...\n");
    selectionSort(listaSimulacao.dispositivos, listaSimulacao.numDispositivos);
    
    // 2. Simulação de Decisão de Consumo
    float consumoAtual = 0.0;
    int desligados = 0;
    
    printf("\nDispositivos ligados (por ordem de prioridade):\n");
    for (int i = 0; i < listaSimulacao.numDispositivos; i++) {
        Dispositivo *disp = &listaSimulacao.dispositivos[i];
        
        // Se o consumo do dispositivo couber na energia restante
        if (consumoAtual + disp->consumo <= energiaDisponivel) {
            consumoAtual += disp->consumo;
            disp->status = 1; // Mantém ligado
            printf("  [LIGADO] %s (Prioridade %d, Consumo %.2f kWh)\n", disp->nome, disp->prioridade, disp->consumo);
        } else {
            disp->status = 0; // Desliga
            desligados++;
            printf("  [DESLIGADO] %s (Prioridade %d, Consumo %.2f kWh) - Limite de energia atingido.\n", disp->nome, disp->prioridade, disp->consumo);
        }
    }

    printf("\n--- Resultado da Simulação ---\n");
    printf("Energia Disponível: %.2f kWh\n", energiaDisponivel);
    printf("Consumo Total Estimado: %.2f kWh\n", consumoAtual);
    printf("Dispositivos Desligados: %d\n", desligados);
    printf("Dispositivos Ligados: %d\n", listaSimulacao.numDispositivos - desligados);
    printf("------------------------------\n");

    free(listaSimulacao.dispositivos); // Libera a memória da cópia
}

void compararAlgoritmos(ListaDispositivos *lista) {
    if (lista->numDispositivos == 0) {
        printf("\nNenhum dispositivo cadastrado para comparação.\n");
        return;
    }

    printf("\n--- Comparação de Desempenho de Algoritmos de Ordenação ---\n");
    printf("Número de Dispositivos: %d\n\n", lista->numDispositivos);

    // Array de ponteiros para funções de ordenação
    void (*algoritmos[])(Dispositivo *, int) = {
        bubbleSort,
        selectionSort,
        insertionSort,
        mergeSort,
        quickSort
    };
    char *nomes[] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort"
    };
    int numAlgoritmos = sizeof(algoritmos) / sizeof(algoritmos[0]);

    printf("| Algoritmo       | Tempo (ms) | Comparações | Trocas     |\n");
    printf("|-----------------|------------|-------------|------------|\n");

    for (int i = 0; i < numAlgoritmos; i++) {
        // 1. Cria uma cópia da lista para o teste
        Dispositivo *copia = (Dispositivo *)malloc(lista->numDispositivos * sizeof(Dispositivo));
        if (!copia) {
            perror("Erro ao alocar memória para cópia");
            return;
        }
        copiarDispositivos(lista->dispositivos, copia, lista->numDispositivos);
        
        // 2. Medição de Tempo
        clock_t inicio = clock();
        
        // 3. Executa o algoritmo
        algoritmos[i](copia, lista->numDispositivos);
        
        clock_t fim = clock();
        double tempo_execucao = ((double)(fim - inicio) * 1000.0) / CLOCKS_PER_SEC; // Tempo em milissegundos

        // 4. Exibe Resultados
        printf("| %-15s | %10.4f | %11lld | %10lld |\n", 
               nomes[i], 
               tempo_execucao, 
               comparacoes, 
               trocas);

        free(copia);
    }
    printf("------------------------------------------------------------------\n");
}


// Função Principal
int main() {
    ListaDispositivos *lista = inicializarLista();
    int opcao;
    
    carregarDispositivos(lista);
    
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida. Tente novamente.\n");
            // Limpa o buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = 0; // Para garantir que o loop continue
            continue;
        }
        
        switch(opcao) {
            case 1:
                cadastrarDispositivo(lista);
                break;
            case 2:
                listarDispositivos(lista);
                break;
            case 3:
                simularConsumoInteligente(lista);
                break;
            case 4:
                compararAlgoritmos(lista);
                break;
            case 5:
                salvarDispositivos(lista);
                break;
            case 6:
                salvarDispositivos(lista); // Salva ao sair
                printf("Saindo do sistema. Memória liberada.\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while(opcao != 6);

    // Libera a memória alocada dinamicamente
    free(lista->dispositivos);
    free(lista);
    
    return 0;
}
