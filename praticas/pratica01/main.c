#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main(void)
{
    /* Teste da matriz */
    GrafoMatriz *g = criar_grafo_matriz(4);

    if (g == NULL) {
        printf("Erro ao criar grafo\n");
        return 1;
    }

    inserir_aresta_matriz(g, 0, 2);
    inserir_aresta_matriz(g, 1, 3);

    printf("0 e 2 sao adjacentes? %d\n",
        sao_adjacentes_matriz(g, 0, 2));

    printf("0 e 3 sao adjacentes? %d\n",
        sao_adjacentes_matriz(g, 0, 3));

    printf("Vertices: %d\n", g->n);

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++)
            printf("%d ", g->adj[i][j]);

        printf("\n");
    }

    liberar_grafo_matriz(g);

    /* Teste da lista */
    GrafoLista *gl = criar_grafo_lista(4);

    if (gl == NULL) {
        printf("Erro ao criar grafo lista\n");
        return 1;
    }

    printf("Vertices da lista: %d\n", gl->n);

    inserir_aresta_lista(gl, 0, 2);
    inserir_aresta_lista(gl, 0, 3);

    remover_aresta_lista(gl, 0, 3);

    for (int i = 0; i < gl->n; i++) {
        printf("%d: ", i);

        No *atual = gl->adj[i];

        while (atual != NULL) {
            printf("%d ", atual->destino);
            atual = atual->prox;
        }

        printf("\n");
    }

printf("Grau do vertice 0: %d\n", grau_lista(gl, 0));
printf("Grau do vertice 1: %d\n", grau_lista(gl, 1));
printf("0 e 2 sao adjacentes? %d\n",
    sao_adjacentes_lista(gl, 0, 2));

printf("0 e 3 sao adjacentes? %d\n",
    sao_adjacentes_lista(gl, 0, 3));

    liberar_grafo_lista(gl);

    return 0;
}