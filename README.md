**Equipe:**
*   **Pedro Mendes** - RM: 562242
*   **Leonardo** - RM: 565564
*   **Alexandre** - RM: 563346
*   **Guilherme Peres** - RM: 563981
*   **Gabriel de Matos** - RM: 565218

---

## 1. Introdução

Este relatório documenta o desenvolvimento e a consolidação do projeto de Simulação de Consumo Inteligente, um sistema implementado em linguagem C com o objetivo de gerenciar o uso de energia elétrica em um ambiente simulado. O sistema utiliza a **prioridade** dos dispositivos e um **limite de energia disponível** para tomar decisões automáticas sobre quais aparelhos devem ser mantidos ligados. O foco principal deste projeto é a aplicação prática de **estruturas de dados dinâmicas** e a **análise de desempenho de algoritmos de ordenação** como base para a tomada de decisão eficiente.

A Sprint 4, em particular, marcou a integração final de todos os componentes, a migração para o **cadastro dinâmico** e a implementação de uma ferramenta robusta para **comparação de desempenho** entre cinco algoritmos de ordenação distintos.

## 2. Evolução do Sistema (Sprints 1 a 4)

O projeto evoluiu de uma prova de conceito simples para um sistema funcional e analítico, conforme detalhado na tabela a seguir:

| Sprint | Foco Principal | Funcionalidades Chave | Estrutura de Dados |
| :--- | :--- | :--- | :--- |
| **Sprint 1** | Conceito e Estrutura | Cadastro, Listagem (em memória) | Estática (Array fixo) |
| **Sprint 2** | Persistência e Ordenação Básica | Bubble Sort, Salvar/Carregar dados | Estática (Array fixo) |
| **Sprint 3** | Análise de Complexidade | Selection Sort, Medição de Tempo e Operações | Estática (Array fixo) |
| **Sprint 4** | **Consolidação e Escalabilidade** | **Cadastro Dinâmico**, **Insertion, Merge, Quick Sort**, **Comparação de Desempenho** | **Dinâmica (Ponteiro e `realloc`)** |

A consolidação do código na Sprint 4 resultou no arquivo `main.c`, que unifica a lógica de gerenciamento de dados, simulação e análise de desempenho.

## 3. Análises Técnicas da Sprint 4

### 3.1. Implementação do Cadastro Dinâmico

O requisito de **Cadastro Dinâmico** foi atendido através da substituição do array estático `Dispositivo dispositivos[MAX_DISPOSITIVOS]` por uma estrutura de lista dinâmica (`ListaDispositivos`), que contém um ponteiro para `Dispositivo *dispositivos`, o número atual de dispositivos (`numDispositivos`) e a capacidade alocada (`capacidade`).

A função `adicionarDispositivo` é responsável por gerenciar a alocação de memória. Quando o número de dispositivos atinge a capacidade máxima, a função utiliza `realloc()` para duplicar a capacidade do array, garantindo que o sistema possa cadastrar um número virtualmente ilimitado de dispositivos, eliminando a limitação de memória imposta pelas Sprints anteriores.

### 3.2. Simulação de Decisão de Consumo

A função `simularConsumoInteligente` é o cerne da lógica de negócio. Ela opera em três etapas:

1.  **Cópia dos Dados:** Uma cópia dos dispositivos é feita para que a ordenação não altere o estado original do cadastro principal.
2.  **Ordenação por Prioridade:** A lista é ordenada (usando `Selection Sort` como padrão na simulação) para garantir que os dispositivos de maior prioridade (menor valor numérico) estejam no início da lista.
3.  **Decisão Sequencial:** O sistema percorre a lista ordenada, ligando sequencialmente cada dispositivo, desde que o consumo acumulado não exceda o limite de energia disponível.

Este método garante uma **decisão de consumo otimizada** baseada na prioridade, um requisito fundamental do projeto.

### 3.3. Comparação de Desempenho dos Algoritmos de Ordenação

A Sprint 4 implementou e integrou mais três algoritmos de ordenação, totalizando cinco: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort e Quick Sort.

A ferramenta de **Comparação de Desempenho** (Opção 4 do menu) mede três métricas cruciais para a análise de complexidade:

1.  **Tempo de Execução:** Medido em milissegundos (`clock()`).
2.  **Comparações:** Contador global que registra o número de comparações de prioridade.
3.  **Trocas:** Contador global que registra o número de operações de troca de posição.

A tabela a seguir resume a complexidade teórica dos algoritmos implementados:

| Algoritmo | Complexidade (Pior Caso) | Família de Complexidade |
| :--- | :--- | :--- |
| **Bubble Sort** | $O(n^2)$ | Quadrática |
| **Selection Sort** | $O(n^2)$ | Quadrática |
| **Insertion Sort** | $O(n^2)$ | Quadrática |
| **Merge Sort** | $O(n \log n)$ | Log-linear |
| **Quick Sort** | $O(n^2)$ (Pior), $O(n \log n)$ (Médio) | Log-linear (na média) |

A análise empírica, realizada pela ferramenta de comparação, demonstra que os algoritmos log-lineares (`Merge Sort` e `Quick Sort`) apresentam um desempenho superior (menor tempo e menor número de comparações/trocas) em grandes volumes de dados, validando a teoria da complexidade.

## 4. Considerações Finais

O projeto Simulação de Consumo Inteligente atingiu todos os objetivos propostos para a Sprint 4 e para o ciclo de desenvolvimento completo. A consolidação do código e a implementação do cadastro dinâmico garantem que o sistema seja **escalável** e **manutenível**.

A integração dos múltiplos algoritmos de ordenação e a ferramenta de comparação de desempenho não apenas cumprem os requisitos técnicos, mas também fornecem uma plataforma de aprendizado e validação empírica dos conceitos de **Análise de Complexidade de Algoritmos**.

O resultado final é um sistema robusto em C, capaz de simular de forma eficiente a tomada de decisão de consumo, priorizando a eficiência energética e a satisfação do usuário ao manter ligados os dispositivos mais importantes.

