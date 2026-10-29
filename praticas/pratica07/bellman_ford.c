#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

// Criacao do grafo
GrafoListaPonderado *criar_grafo(int num_vertices) {

    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));

    if (g == NULL) {
        return NULL;
    }

    g->num_vertices = num_vertices;

    g->lista = calloc(num_vertices, sizeof(Aresta *));

    if (g->lista == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

// Adiciona uma aresta direcionada
void adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
) {

    if (g == NULL ||
        origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {
        return;
    }

    Aresta *nova = malloc(sizeof(Aresta));

    if (nova == NULL) {
        return;
    }

    nova->destino = destino;
    nova->peso = peso;
    nova->prox = g->lista[origem];

    g->lista[origem] = nova;
}

// Libera a memoria utilizada
void liberar_grafo(GrafoListaPonderado *g) {

    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->num_vertices; i++) {

        Aresta *atual = g->lista[i];

        while (atual != NULL) {

            Aresta *temp = atual;
            atual = atual->prox;

            free(temp);
        }
    }

    free(g->lista);
    free(g);
}

// Reconstrucao do ciclo negativo
void reconstruir_ciclo_negativo(
    int *pred,
    int vertice,
    int n
) {

    int x = vertice;

    // Retrocede n vezes para garantir
    // que estamos dentro do ciclo
    for (int i = 0; i < n; i++) {
        if (x < 0 || x >= n) {
            printf("Nao foi possivel reconstruir o ciclo.\n");
            return;
        }

        x = pred[x];
    }

    if (x < 0 || x >= n) {
        printf("Nao foi possivel reconstruir o ciclo.\n");
        return;
    }

    int *ciclo = malloc((n + 1) * sizeof(int));

    if (ciclo == NULL) {
        return;
    }

    int atual = x;
    int tamanho = 0;

    do {

        if (atual < 0 || atual >= n || tamanho >= n) {
            free(ciclo);
            printf("Erro ao reconstruir o ciclo.\n");
            return;
        }

        ciclo[tamanho++] = atual;
        atual = pred[atual];

    } while (atual != x);

    ciclo[tamanho++] = x;

    printf("\nCiclo negativo encontrado:\n");

    // Imprime na ordem das arestas
    for (int i = tamanho - 1; i >= 0; i--) {

        printf("%d", ciclo[i]);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\n");

    free(ciclo);
}

// Algoritmo de Bellman-Ford
int bellman_ford(
    GrafoListaPonderado *g,
    int origem,
    int *dist,
    int *pred
) {

    if (g == NULL || dist == NULL || pred == NULL ||
        origem < 0 || origem >= g->num_vertices) {
        return 0;
    }

    int n = g->num_vertices;

    // Inicializacao
    for (int i = 0; i < n; i++) {

        dist[i] = INF;
        pred[i] = -1;
    }

    dist[origem] = 0;

    // Relaxacao das arestas n-1 vezes
    for (int i = 0; i < n - 1; i++) {

        int alterou = 0;

        for (int u = 0; u < n; u++) {

            Aresta *atual = g->lista[u];

            while (atual != NULL) {

                int v = atual->destino;
                int peso = atual->peso;

                if (dist[u] != INF &&
                    (long long)dist[u] + peso < dist[v]) {

                    dist[v] = dist[u] + peso;
                    pred[v] = u;

                    alterou = 1;
                }

                atual = atual->prox;
            }
        }

        // Otimizacao: encerra se nao houve alteracao
        if (!alterou) {
            break;
        }
    }

    // Verificacao de ciclos negativos
    for (int u = 0; u < n; u++) {

        Aresta *atual = g->lista[u];

        while (atual != NULL) {

            int v = atual->destino;
            int peso = atual->peso;

            if (dist[u] != INF &&
                (long long)dist[u] + peso < dist[v]) {

                pred[v] = u;

                reconstruir_ciclo_negativo(pred, v, n);

                return 0;
            }

            atual = atual->prox;
        }
    }

    return 1;
}