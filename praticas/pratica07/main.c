#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

// Exibe as menores distancias encontradas
void imprimir_distancias(int *dist, int *pred, int n) {

    printf("\nVertice | Distancia | Predecessor\n");
    printf("---------------------------------\n");

    for (int i = 0; i < n; i++) {

        if (dist[i] == INF) {
            printf("%7d |       INF | %11d\n", i, pred[i]);
        } else {
            printf("%7d | %9d | %11d\n", i, dist[i], pred[i]);
        }
    }
}

// Teste 1: grafo sem ciclo negativo
void teste_sem_ciclo_negativo() {

    printf("\n=== TESTE 1: SEM CICLO NEGATIVO ===\n");

    int n = 5;

    GrafoListaPonderado *g = criar_grafo(n);

    if (g == NULL) {
        printf("Erro ao criar grafo.\n");
        return;
    }

    adicionar_aresta(g, 0, 1, 6);
    adicionar_aresta(g, 0, 2, 7);
    adicionar_aresta(g, 1, 2, 8);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 1, 4, -4);
    adicionar_aresta(g, 2, 3, -3);
    adicionar_aresta(g, 2, 4, 9);
    adicionar_aresta(g, 3, 1, -2);
    adicionar_aresta(g, 4, 0, 2);
    adicionar_aresta(g, 4, 3, 7);

    int *dist = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int));

    if (dist == NULL || pred == NULL) {
        printf("Erro de alocacao de memoria.\n");
        free(dist);
        free(pred);
        liberar_grafo(g);
        return;
    }

    int resultado = bellman_ford(g, 0, dist, pred);

    if (resultado == 1) {

        printf("Bellman-Ford executado com sucesso!\n");

        imprimir_distancias(dist, pred, n);

    } else {

        printf("O grafo possui ciclo negativo.\n");
    }

    free(dist);
    free(pred);
    liberar_grafo(g);
}

// Teste 2: grafo com ciclo negativo
void teste_com_ciclo_negativo() {

    printf("\n=== TESTE 2: COM CICLO NEGATIVO ===\n");

    int n = 4;

    GrafoListaPonderado *g = criar_grafo(n);

    if (g == NULL) {
        printf("Erro ao criar grafo.\n");
        return;
    }

    adicionar_aresta(g, 0, 1, 1);
    adicionar_aresta(g, 1, 2, -1);
    adicionar_aresta(g, 2, 3, -1);
    adicionar_aresta(g, 3, 1, -1);

    int *dist = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int));

    if (dist == NULL || pred == NULL) {
        printf("Erro de alocacao de memoria.\n");
        free(dist);
        free(pred);
        liberar_grafo(g);
        return;
    }

    int resultado = bellman_ford(g, 0, dist, pred);

    if (resultado == 1) {

        printf("Bellman-Ford executado com sucesso!\n");

        imprimir_distancias(dist, pred, n);

    } else {

        printf("Nao existem menores caminhos bem definidos "
               "para todos os vertices alcancaveis.\n");
    }

    free(dist);
    free(pred);
    liberar_grafo(g);
}

int main() {

    printf("====================================\n");
    printf("       ALGORITMO BELLMAN-FORD       \n");
    printf("====================================\n");

    teste_sem_ciclo_negativo();

    teste_com_ciclo_negativo();

    return 0;
}