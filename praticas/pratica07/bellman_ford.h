#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#define INF 1000000000

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta **lista;
} GrafoListaPonderado;

// Funcoes de manipulacao do grafo
GrafoListaPonderado *criar_grafo(int num_vertices);

void adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
);

void liberar_grafo(GrafoListaPonderado *g);

// Algoritmo de Bellman-Ford
int bellman_ford(
    GrafoListaPonderado *g,
    int origem,
    int *dist,
    int *pred
);

// Reconstrucao de ciclo negativo
void reconstruir_ciclo_negativo(
    int *pred,
    int vertice,
    int n
);

#endif