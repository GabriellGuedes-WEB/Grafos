#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n)
{
    GrafoLista *g = malloc(sizeof(GrafoLista));

    if (g == NULL)
        return NULL;

    g->n = n;

    g->adj = malloc(n * sizeof(No *));

    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        g->adj[i] = NULL;

    return g;
}

void inserir_aresta_lista(GrafoLista *g, int origem, int destino)
{
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return;

    novo->destino = destino;
    novo->prox = g->adj[origem];

    g->adj[origem] = novo;
}

void remover_aresta_lista(GrafoLista *g, int origem, int destino)
{
    No *atual = g->adj[origem];
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL)
                g->adj[origem] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

int grau_lista(GrafoLista *g, int vertice)
{
    int grau = 0;
    No *atual = g->adj[vertice];

    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }

    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int origem, int destino)
{
    No *atual = g->adj[origem];

    while (atual != NULL) {
        if (atual->destino == destino)
            return 1;

        atual = atual->prox;
    }

    return 0;
}


void liberar_grafo_lista(GrafoLista *g)
{
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];

        while (atual != NULL) {
            No *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(g->adj);
    free(g);
}