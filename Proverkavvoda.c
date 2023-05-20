#include "queue_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INT_MAX 1000000000
#define MAX_V 99
#define NAME_SIZE 111
int V;

/*
void bfs(int g[MAX_V][MAX_V], int v, bool* pos, int* prev,int V)
{
    struct queue* q;
    for (int i = 0; i < V; i++) {
        pos[i] = false;
        prev[i] = -1;
    }
    q = queue_create(V); // Создаём очередь
    pos[v] = true; // Обрабатываем стартовую вершину
    printf("Vertex % d\n", v + 1);
    queue_enqueue(q, v);
    while (queue_size(q) > 0) {
        int i = queue_dequeue(q);
        for (int j = 0; j < V; j++) {
            if (g[i][j] != INT_MAX && !pos[j]) {
                queue_enqueue(q, j);
                pos[j] = true;
                prev[j] = i;
                printf("Vertex % d\n", j + 1);
            }
        }
    }
    queue_free(q);
}
*/
void bfs(int g[MAX_V][MAX_V], int v, bool* pos, int* prev, int V)
{
    struct queue* q;
    for (int i = 0; i < V; i++) {
        pos[i] = false;
        prev[i] = -1;
    }
    q = queue_create(V); // Создаём очередь
    pos[v] = true; // Обрабатываем стартовую вершину
    printf("Vertex % d\n", v + 1);
    queue_enqueue(q, v);
    while (queue_size(q) > 0) {
        int i = queue_dequeue(q);
        for (int j = 0; j < V; j++) {
            if (g[i][j] != INT_MAX && !pos[j]) {
                queue_enqueue(q, j);
                pos[j] = true;
                prev[j] = i;
                printf("Vertex % d\n", j + 1);
            }
        }
    }
    queue_free(q);
}

void dfs(int** g, bool* pos, int start, int* prev, int V)
{
    pos[start] = true;
    printf("Vertex % d\n", start + 1);
    for (int i = 0; i < V; ++i) {
        if (!pos[i] && g[start][i] != INT_MAX) {
            prev[i] = start;
            dfs(g, pos, i, prev, V);
        }
    }
}

int kolvo(int** g, int src, int dst, int V)
{
    int* d = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    for (int i = 0; i < V; ++i) {
        d[i] = 0;
        pos[i] = false;
    }
    d[src] = 1;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (g[i][j] != INT_MAX && !pos[j]) {
                d[j] = d[i] + d[j];
            }
        }
        pos[i] = true;
    }
    return d[dst];
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

void my_flush(void)
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

void print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V)
{
    ShortestPathDijkstra(g, src, D, pos, prev, V);
    printf("Расстояние от вершины %d до всех остальных\n", src + 1);
    for (int i = 0; i < V; ++i) {
        printf("%d - %d : %d\n", src + 1, i + 1, D[i]);
    }
    /*for (int i = 0, z = 1; i < V; ++i) {
        printf("%d : %d\n", z++, prev[i] + 1);
    }*/
    printf("\n");
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
    printf("Путь из вершины %d в вершину %d\n%d ", src + 1, dst + 1, src + 1);
    for (int i = 0; i < count; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    /*
    int** g = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; ++i) {
        g[i] = malloc(sizeof(int) * V);
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            g[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                g[i][j] = 1 + rand() % 100;
            }
        }
    }
    */
    int src, dst, K;

    do {
        printf("Введите количество вершин : ");
        K = scanf("%d", &V);
        my_flush();
    } while (K != 1 || K <= 0);

    int** g = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; ++i) {
        g[i] = malloc(sizeof(int) * V);
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            g[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                g[i][j] = 1 + rand() % 20;
            }
        }
    }
    int N;
    int M;
    do {
        printf("Введите начальную вершину = ");
        N = scanf("%d", &src);
        my_flush();
    } while (N != 1);
    src--;

    do {
        printf("Введите конечнню вершину = ");
        M = scanf("%d", &dst);
        my_flush();
    } while (M != 1);
    dst--;

    int ch;
    int P;
    char vvod[NAME_SIZE];
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    do {
        printf("Что бы вы хотели найти, введите соответствующий символ:\n");
        printf("1. Кол-во путей между вершинами:\n");
        printf("2. Кротчайший путь между вершинами: \n");
        printf("3. длиннейший путь между вершинами: \n");
        printf("4. для выхода:\n");
        printf("Ваш выбор: ");
        P = scanf("%d", &ch);
        switch (ch) {
        case 1:
            printf("\nКоличество путей из %d в %d : %d\n",
                   src + 1,
                   dst + 1,
                   kolvo(g, src, dst, V));
            break;
        case 2:
            ShortestPathDijkstra(g, src, D, pos, prev, V);
            printf("Кротчайший путь между %d и %d:%d\n",
                   src + 1,
                   dst + 1,
                   D[dst]);
            break;
        case 3:
            printf("Длиннейший путь:\n");
            break;
        case 4:
            break;
        default:
            printf("Некорректный символ, попробуйте ещё раз.\n");
        }
        my_flush();
    } while (P != 1);
    // int src = 1, dst = 5, v = 1; // v - от какой вершины делать поиск в
    // глубину и ширину src--; dst--; v--; // src - от какой вершины смотрим
    /* int g[MAX_V][MAX_V]
            = {{INT_MAX, 10, INT_MAX, 30, 100},
               {10, INT_MAX, 50, INT_MAX, INT_MAX},
               {INT_MAX, 50, INT_MAX, 20, 10},
               {30, INT_MAX, 20, INT_MAX, 60},
             {100, INT_MAX, 10, 60, INT_MAX}};

  */
}