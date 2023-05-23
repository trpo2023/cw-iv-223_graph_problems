#include "graph.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #pragma warning(disable : 4996)

#define INT_MAX 1000000000

void NumberOfPaths(
        int** g,
        int src,
        int dst,
        bool* pos,
        int V,
        int* count,
        int a,
        int* prev,
        int* b)
{
    pos[src] = true;
    if (src == dst) {
        *count = *count + 1;
        pos[dst] = false;
        prev[a++] = dst;
        printf("%d) ", *b);
        *b = *b + 1;
        for (int i = 0; i < a - 1; ++i) {
            printf("%d -> ", prev[i] + 1);
        }
        printf("%d\n", prev[a - 1] + 1);

    } else {
        for (int i = 0; i < V; ++i) {
            if (g[src][i] != INT_MAX && !pos[i]) {
                prev[a++] = src;
                NumberOfPaths(g, i, dst, pos, V, count, a, prev, b);
                a--;
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

// longest path

int LongestPath(int N, int M, int** adj_matrix)
{
    // setlocale(0, "");

    // заполнение матрицы смежности
    // int** adj_matrix = adj_matrix_init(N);

    /*for (int i = 0; i < M; i++) {
        printf("Введите начальную вершину, конечную и длину пути (например: 1 "
               "4 10): ");
        int l = lon;
        scanf("%d %d %d", &initV, &endV, &l);
        adj_matrix[initV - 1][endV - 1] = l;
    }*/

    // формирование массива вершин
    struct node* node_array = malloc(sizeof(struct node) * N);
    NodeInit(&node_array[0], 1);

    for (int i = 1; i < N; i++) {
        NodeInit(&node_array[i], 0);
    }

    // цикл по матрице и обновление характеристик вершин
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj_matrix[i][j] != 0) {
                if (node_array[j].lp_len
                    < node_array[i].lp_len + adj_matrix[i][j]) {
                    node_array[j].lp_len
                            = node_array[i].lp_len + adj_matrix[i][j];
                    node_array[j].lp_count = node_array[i].lp_count;
                } else if (
                        node_array[j].lp_len
                        == node_array[i].lp_len + adj_matrix[i][j]) {
                    node_array[j].lp_count += node_array[i].lp_count;
                }
            }
        }
    }
    // printf("Самый длинный путь: %d\n", node_array[N - 1].lp_len);
    // printf("Количество самых длинных путей: %d\n", node_array[N -
    // 1].lp_count);

    free(node_array);
    AdjMatrixFree(N, adj_matrix);

    return node_array[N - 1].lp_len;
}

void NodeInit(struct node* new_node, int is_s)
{ // создание нового узла, если ошибка, то возвращается NULL
    if (new_node != NULL) {
        if (is_s) {
            new_node->lp_len = 0;
            new_node->lp_count = 1;
        } else {
            new_node->lp_len = INT_MIN; // максимальная длина равна самому
                                        // минимальному int
            new_node->lp_count = 0;
        }
    };
}

int** AdjMatrixInit(int N)
{
    int** adj_matrix = malloc(sizeof(int*) * N);
    if (adj_matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        adj_matrix[i] = malloc(sizeof(int) * N);
        if (adj_matrix[i] == NULL) {
            free(adj_matrix);
            for (int j = 0; j < i; j++) {
                free(adj_matrix[j]);
            }
            return NULL;
        }
        for (int j = 0; j < N; j++) {
            adj_matrix[i][j] = 0;
        }
    }
    return adj_matrix;
}

void AdjMatrixFree(int N, int** adj_matrix)
{
    for (int i = 0; i < N; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);
}

// end longest path

void Print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V)
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