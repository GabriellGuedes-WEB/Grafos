
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main(void) {
    // A = 0, B = 1, C = 2, D = 3, E = 4, F = 5
    const int num_vertices = 6;
    const int origem = 0; // A
    const int destino = 5; // F

    GrafoListaPonderado *g = criar_grafo(num_vertices);

    if (g == NULL) {
        fprintf(stderr, "Erro ao criar o grafo.\n");
        return EXIT_FAILURE;
    }

    // Arestas do grafo da imagem (não direcionado)
    adicionar_aresta(g, 0, 1, 4);  // A - B
    adicionar_aresta(g, 0, 2, 2);  // A - C
    adicionar_aresta(g, 1, 2, 1);  // B - C
    adicionar_aresta(g, 1, 3, 5);  // B - D
    adicionar_aresta(g, 1, 4, 8);  // B - E
    adicionar_aresta(g, 2, 3, 4);  // C - D
    adicionar_aresta(g, 2, 4, 10); // C - E
    adicionar_aresta(g, 3, 4, 2);  // D - E
    adicionar_aresta(g, 3, 5, 1);  // D - F
    adicionar_aresta(g, 4, 5, 3);  // E - F

    int dist[6];
    int pred[6];

    dijkstra(g, origem, dist, pred);

    const char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    printf("Origem: %c\n\n", vertices[origem]);
    printf("Distancias minimas:\n");

    for (int i = 0; i < num_vertices; i++) {
        if (dist[i] == INFINITO) {
            printf("  ate %c: INFINITO\n", vertices[i]);
        } else {
            printf("  ate %c: %d\n", vertices[i], dist[i]);
        }
    }

   printf("\nCaminho minimo de %c ate %c: ",
       vertices[origem], vertices[destino]);

if (dist[destino] == INFINITO) {
    printf("Nao existe caminho.\n");
} else {
    int tamanho = 0;

    int *caminho = reconstruir_caminho(
        origem,
        destino,
        pred,
        num_vertices,
        &tamanho
    );

    if (caminho == NULL) {
        printf("Erro ao reconstruir o caminho.\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            printf("%c", vertices[caminho[i]]);

            if (i < tamanho - 1) {
                printf(" -> ");
            }
        }

        printf("\nCusto total: %d\n", dist[destino]);

        free(caminho);
    }
}}
