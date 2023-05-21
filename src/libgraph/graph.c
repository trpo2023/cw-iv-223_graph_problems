#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { INT_MAX = 1000000000 };

void Number_of_paths(int** g, int src, int dst, bool* pos, int V, int* count)
{
    pos[src] = true;
    if (src == dst) {
        *count = *count + 1;
        pos[dst] = false;

    } else {
        for (int i = 0; i < V; ++i) {
            if (g[src][i] != INT_MAX && !pos[i]) {
                Number_of_paths(g, i, dst, pos, V, count);
                pos[i] = false;
            }
        }
    }
}

int PriorityQueueExtractMin(int* D, bool* pos, int V)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; ++i) {
        if (D[i] <= min && !pos[i]) {
            min = D[i];
            min_index = i;
        }
    }
    return min_index;
}

void ShortestPathDijkstra(int** g, int src, int* D, bool* pos, int* prev, int V)
{
    for (int i = 0; i < V; ++i) {
        D[i] = INT_MAX;
        pos[i] = false;
        prev[i] = -1;
    }
    D[src] = 0;
    for (int i = 0; i < V - 1; ++i) {
        int u = PriorityQueueExtractMin(D, pos, V);
        pos[u] = true;
        for (int v = 0; v < V; ++v) {
            if (D[u] + g[u][v] < D[v]) {
                D[v] = D[u] + g[u][v];
                prev[v] = u;
            }
        }
    }
}

void print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V)
{
    ShortestPathDijkstra(g, src, D, pos, prev, V);
    printf("Расстояние от вершины %d до вершины %d - %d\n",
           src + 1,
           dst + 1,
           D[dst]);
    int i = dst, count = 0;
    while (prev[i] != prev[src]) {
        i = prev[i];
        count++;
    }
    i = dst;
    int j = 1, path[count];
    while (prev[i] != prev[src]) {
        path[count - j++] = i + 1;
        i = prev[i];
    }
    printf("Путь из вершины %d в вершину %d\n%d", src + 1, dst + 1, src + 1);
    for (int i = 0; i < count; ++i) {
        printf(" -> %d", path[i]);
    }
    printf("\n");
}