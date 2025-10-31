*   **Pedro Mendes** - RM: 562242
*   **Leonardo** - RM: 565564
*   **Alexandre** - RM: 563346
*   **Guilherme Peres** - RM: 563981
*   **Gabriel de Matos** - RM: 565218

--

# Simulação de Consumo Inteligente - Sprint 4: Consolidação e Análise de Desempenho

Este projeto em C simula um sistema de gerenciamento de dispositivos elétricos com base na prioridade de consumo e um limite de energia disponível. A Sprint 4 focou na **consolidação do código** (agora em `main.c`), na implementação de **cadastro dinâmico** e na **análise de desempenho** de múltiplos algoritmos de ordenação.

## 🚀 Funcionalidades Principais

1.  **Consolidação do Código:** O código-fonte foi unificado em um único arquivo (`main.c`), garantindo a integração de todas as funcionalidades desenvolvidas nas sprints anteriores.
2.  **Cadastro Dinâmico de Dispositivos:** O sistema agora utiliza alocação dinâmica de memória (`malloc` e `realloc`) para gerenciar a lista de dispositivos, permitindo um número ilimitado de cadastros, atendendo ao requisito de escalabilidade.
3.  **Simulação de Decisão de Consumo:** O sistema decide quais dispositivos manter ligados, priorizando aqueles com maior importância (menor número de prioridade), respeitando um limite de energia (kWh) definido pelo usuário.
4.  **Múltiplos Algoritmos de Ordenação:** Implementação de cinco algoritmos de ordenação para classificar os dispositivos por prioridade, essenciais para a simulação e a análise de complexidade:
    *   Bubble Sort
    *   Selection Sort
    *   Insertion Sort
    *   Merge Sort
    *   Quick Sort
5.  **Comparação de Desempenho:** Ferramenta interativa (Opção 4 no menu) para comparar o desempenho dos 5 algoritmos de ordenação em termos de **tempo de execução**, **número de comparações** e **número de trocas**.
6.  **Persistência de Dados:** Os dispositivos cadastrados são salvos e carregados automaticamente em um arquivo binário (`dispositivos.dat`).

## 🛠️ Como Compilar e Executar

### Pré-requisitos
É necessário ter um compilador C (como o GCC) instalado no sistema.

### Compilação
Navegue até o diretório do projeto (`sprint-3`) e execute o seguinte comando:

```bash
gcc -o sprint4_app main.c
```

### Execução
Após a compilação, execute o programa:

```bash
./sprint4_app
```

## 📋 Menu de Uso

O programa é executado via linha de comando e apresenta um menu interativo:

| Opção | Descrição |
| :---: | :--- |
| **1** | **Cadastrar Novo Dispositivo:** Permite adicionar um novo dispositivo com nome, consumo (kWh) e prioridade (1=Alta, 2=Média, 3=Baixa). |
| **2** | **Listar Dispositivos:** Exibe todos os dispositivos cadastrados, seu status atual e o consumo total estimado. |
| **3** | **Simular Decisão de Consumo Inteligente:** Solicita um limite de energia e realiza a simulação, desligando dispositivos de menor prioridade para se manter dentro do limite. |
| **4** | **Comparar Desempenho de Algoritmos de Ordenação:** Executa os 5 algoritmos e exibe uma tabela comparativa de tempo, comparações e trocas. |
| **5** | **Salvar Dispositivos:** Salva o estado atual dos dispositivos em disco. |
| **6** | **Sair:** Salva os dispositivos e encerra o programa. |

## 💡 Análise Técnica da Sprint 4

A Sprint 4 representa a maturidade do sistema. A adoção da **alocação dinâmica** elimina as limitações de capacidade do sistema. A implementação de algoritmos de ordenação avançados ($O(n \log n)$) como **Merge Sort** e **Quick Sort** permite que a simulação de consumo inteligente mantenha um alto desempenho, mesmo com um grande volume de dispositivos.

A ferramenta de comparação de desempenho é fundamental para a **validação técnica** do projeto, demonstrando empiricamente a diferença de complexidade entre os algoritmos quadráticos ($O(n^2)$) e os log-lineares ($O(n \log n)$).

| Algoritmo | Complexidade (Pior Caso) | Tipo |
| :--- | :--- | :--- |
| **Bubble Sort** | $O(n^2)$ | Simples, Quadrático |
| **Selection Sort** | $O(n^2)$ | Simples, Quadrático |
| **Insertion Sort** | $O(n^2)$ | Simples, Quadrático |
| **Merge Sort** | $O(n \log n)$ | Avançado, Log-linear |
| **Quick Sort** | $O(n^2)$ (Pior), $O(n \log n)$ (Médio) | Avançado, Log-linear (na média) |


A integração dos múltiplos algoritmos de ordenação e a ferramenta de comparação de desempenho não apenas cumprem os requisitos técnicos, mas também fornecem uma plataforma de aprendizado e validação empírica dos conceitos de **Análise de Complexidade de Algoritmos**.

O resultado final é um sistema robusto em C, capaz de simular de forma eficiente a tomada de decisão de consumo, priorizando a eficiência energética e a satisfação do usuário ao manter ligados os dispositivos mais importantes.

