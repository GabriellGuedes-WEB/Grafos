#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n)
{
    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));

    if (g == NULL)
        return NULL;

    g->n = n;

    g->adj = malloc(n * sizeof(int *));

    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->adj[i] = malloc(n * sizeof(int));

        if (g->adj[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(g->adj[j]);

            free(g->adj);
            free(g);
            return NULL;
        }

        for (int j = 0; j < n; j++)
            g->adj[i][j] = 0;
    }


    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int origem, int destino)
{
    g->adj[origem][destino] = 1;
}

void remover_aresta_matriz(GrafoMatriz *g, int origem, int destino)
{
    g->adj[origem][destino] = 0;
}

int grau_matriz(GrafoMatriz *g, int vertice)
{
    int grau = 0;

    for (int j = 0; j < g->n; j++) {
        grau += g->adj[vertice][j];
    }

    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *g, int origem, int destino)
{
    return g->adj[origem][destino] == 1;
}

void liberar_grafo_matriz(GrafoMatriz *g)
{
    for (int i = 0; i < g->n; i++)
        free(g->adj[i]);

    free(g->adj);
    free(g);
}
