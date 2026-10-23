#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>

/* Representa uma distância infinita. */
#define INFINITO INT_MAX

/* Aresta da lista de adjacência. */
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

/* Grafo ponderado representado por lista de adjacência. */
typedef struct {
    int num_vertices;
    Aresta **listas;
} GrafoListaPonderado;

/* Nó armazenado na Min-Heap. */
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

/* Min-Heap com controle da posição de cada vértice. */
typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao;
} MinHeap;

/* Funções para manipulação do grafo. */
GrafoListaPonderado *criar_grafo(int num_vertices);
int adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
);
void liberar_grafo(GrafoListaPonderado *g);

/* Funções da Min-Heap. */
MinHeap *criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap *heap);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int distancia);

/* Algoritmo de Dijkstra. */
int dijkstra(
    GrafoListaPonderado *g,
    int origem,
    int *dist,
    int *pred
);

/* Retorna o caminho em um vetor alocado dinamicamente.
   O chamador deve liberar o vetor com free().
   Se não houver caminho, retorna NULL e define tamanho como 0. */
int *reconstruir_caminho(
    int origem,
    int destino,
    const int *pred,
    int num_vertices,
    int *tamanho
);

#endif