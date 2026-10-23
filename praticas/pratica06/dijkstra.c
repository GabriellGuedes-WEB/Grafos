#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   GRAFO
   ========================================================= */

/* Cria um grafo com num_vertices vértices. */
GrafoListaPonderado *criar_grafo(int num_vertices) {
    if (num_vertices <= 0) {
        return NULL;
    }

    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));

    if (g == NULL) {
        return NULL;
    }

    g->num_vertices = num_vertices;
    g->listas = calloc((size_t) num_vertices, sizeof(Aresta *));

    if (g->listas == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

/* Adiciona uma aresta não direcionada. */
int adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
) {
    if (g == NULL ||
        origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices ||
        peso < 0) {
        return 0;
    }

    Aresta *aresta1 = malloc(sizeof(Aresta));

    if (aresta1 == NULL) {
        return 0;
    }

    Aresta *aresta2 = malloc(sizeof(Aresta));

    if (aresta2 == NULL) {
        free(aresta1);
        return 0;
    }

    aresta1->destino = destino;
    aresta1->peso = peso;
    aresta1->prox = g->listas[origem];

    aresta2->destino = origem;
    aresta2->peso = peso;
    aresta2->prox = g->listas[destino];

    g->listas[origem] = aresta1;
    g->listas[destino] = aresta2;

    return 1;
}

/* Libera toda a memória do grafo. */
void liberar_grafo(GrafoListaPonderado *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->listas[i];

        while (atual != NULL) {
            Aresta *proxima = atual->prox;
            free(atual);
            atual = proxima;
        }
    }

    free(g->listas);
    free(g);
}

/* =========================================================
   MIN-HEAP
   ========================================================= */

/* Troca dois nós e atualiza suas posições. */
static void trocar_nos(MinHeap *heap, int i, int j) {
    NoHeap temporario = heap->dados[i];

    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temporario;

    heap->posicao[heap->dados[i].vertice] = i;
    heap->posicao[heap->dados[j].vertice] = j;
}

/* Restaura a propriedade de heap subindo um nó. */
static void subir_heap(MinHeap *heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap->dados[pai].distancia <=
            heap->dados[i].distancia) {
            break;
        }

        trocar_nos(heap, i, pai);
        i = pai;
    }
}

/* Restaura a propriedade de heap descendo um nó. */
static void descer_heap(MinHeap *heap, int i) {
    while (1) {
        int menor = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        if (esquerda < heap->tamanho &&
            heap->dados[esquerda].distancia <
            heap->dados[menor].distancia) {
            menor = esquerda;
        }

        if (direita < heap->tamanho &&
            heap->dados[direita].distancia <
            heap->dados[menor].distancia) {
            menor = direita;
        }

        if (menor == i) {
            break;
        }

        trocar_nos(heap, i, menor);
        i = menor;
    }
}

/* Cria a Min-Heap. */
MinHeap *criar_min_heap(int capacidade) {
    if (capacidade <= 0) {
        return NULL;
    }

    MinHeap *heap = malloc(sizeof(MinHeap));

    if (heap == NULL) {
        return NULL;
    }

    heap->dados = malloc((size_t) capacidade * sizeof(NoHeap));
    heap->posicao = malloc((size_t) capacidade * sizeof(int));

    if (heap->dados == NULL || heap->posicao == NULL) {
        free(heap->dados);
        free(heap->posicao);
        free(heap);
        return NULL;
    }

    heap->capacidade = capacidade;
    heap->tamanho = capacidade;

    for (int i = 0; i < capacidade; i++) {
        heap->dados[i].vertice = i;
        heap->dados[i].distancia = INFINITO;
        heap->posicao[i] = i;
    }

    return heap;
}

/* Libera a memória da Min-Heap. */
void liberar_min_heap(MinHeap *heap) {
    if (heap == NULL) {
        return;
    }

    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

/* Remove e retorna o nó de menor distância. */
NoHeap extrair_minimo(MinHeap *heap) {
    NoHeap invalido = {-1, INFINITO};

    if (heap == NULL || heap->tamanho == 0) {
        return invalido;
    }

    NoHeap minimo = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];

    heap->tamanho--;

    /* O vértice extraído deixa de pertencer à heap. */
    heap->posicao[minimo.vertice] = -1;

    if (heap->tamanho > 0) {
        heap->dados[0] = ultimo;
        heap->posicao[ultimo.vertice] = 0;
        descer_heap(heap, 0);
    }

    return minimo;
}

/* Atualiza a distância de um vértice e reorganiza a heap. */
void diminuir_chave(MinHeap *heap, int vertice, int distancia) {
    if (heap == NULL ||
        vertice < 0 || vertice >= heap->capacidade) {
        return;
    }

    int i = heap->posicao[vertice];

    if (i < 0 || i >= heap->tamanho) {
        return;
    }

    if (distancia >= heap->dados[i].distancia) {
        return;
    }

    heap->dados[i].distancia = distancia;
    subir_heap(heap, i);
}

/* =========================================================
   DIJKSTRA
   ========================================================= */

/* Calcula as menores distâncias a partir da origem.
   Retorna 1 em caso de sucesso e 0 em caso de erro. */
int dijkstra(
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
    MinHeap *heap = criar_min_heap(n);

    if (heap == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        pred[i] = -1;
    }

    dist[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0) {
        NoHeap minimo = extrair_minimo(heap);
        int u = minimo.vertice;

        /* Os vértices restantes são inalcançáveis. */
        if (minimo.distancia == INFINITO) {
            break;
        }

        Aresta *aresta = g->listas[u];

        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;

            /* Só processa vértices ainda presentes na heap. */
            if (heap->posicao[v] != -1 &&
                dist[u] <= INT_MAX - peso) {

                int nova_distancia = dist[u] + peso;

                if (nova_distancia < dist[v]) {
                    dist[v] = nova_distancia;
                    pred[v] = u;

                    diminuir_chave(heap, v, nova_distancia);
                }
            }

            aresta = aresta->prox;
        }
    }

    liberar_min_heap(heap);
    return 1;
}

/* =========================================================
   RECONSTRUÇÃO DO CAMINHO
   ========================================================= */

/* Monta o caminho da origem ao destino.
   O vetor retornado deve ser liberado pelo chamador. */
int *reconstruir_caminho(
    int origem,
    int destino,
    const int *pred,
    int num_vertices,
    int *tamanho
) {
    if (tamanho == NULL) {
        return NULL;
    }

    *tamanho = 0;

    if (pred == NULL ||
        num_vertices <= 0 ||
        origem < 0 || origem >= num_vertices ||
        destino < 0 || destino >= num_vertices) {
        return NULL;
    }

    int *caminho = malloc((size_t) num_vertices * sizeof(int));

    if (caminho == NULL) {
        return NULL;
    }

    int atual = destino;
    int quantidade = 0;

    /* Percorre os predecessores do destino até a origem. */
    while (atual != -1 && quantidade < num_vertices) {
        caminho[quantidade++] = atual;

        if (atual == origem) {
            break;
        }

        atual = pred[atual];
    }

    /* Se não chegou à origem, não existe caminho válido. */
    if (quantidade == 0 || caminho[quantidade - 1] != origem) {
        free(caminho);
        return NULL;
    }

    /* Inverte a sequência para ficar da origem ao destino. */
    for (int i = 0; i < quantidade / 2; i++) {
        int temporario = caminho[i];
        caminho[i] = caminho[quantidade - 1 - i];
        caminho[quantidade - 1 - i] = temporario;
    }

    *tamanho = quantidade;
    return caminho;
}