#include <libgraph/graph.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 5
#define INT_MAX 1000000000

int main()
{
    srand(time(NULL));

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
                g[i][j] = rand() % 100;
            }
        }
    }

    /*
     int g[V][V]
             = {{INT_MAX, 10, 10, 30, 100},
                {10, INT_MAX, 50, 10, 10},
                {10, 50, INT_MAX, 20, 10},
                {30, 10, 20, INT_MAX, 60},
                {100, 10, 10, 60, INT_MAX}};
                */
    /*
    int g[V][V]
            = {{INT_MAX, 1, 1, INT_MAX, 1, INT_MAX},
               {1, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
               {1, INT_MAX, INT_MAX, INT_MAX, 1, INT_MAX},
               {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, INT_MAX},
               {1, INT_MAX, 1, 1, INT_MAX, INT_MAX},
               {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}};
    */
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    int src = 1, dst = 5,
        count = 0; // v - от какой вершины делать поиск в глубину и ширину
    src--;
    dst--;         // src - от какой вершины смотрим
    print(g, D, src, prev, dst, pos, V); // dst - вершина у которой смотрим путь
    for (int i = 0; i < V; ++i) {
        pos[i] = false;
        prev[i] = -1;
    }
    printf("Количество путей из %d в %d - ", src + 1, dst + 1);
    Number_of_paths(g, src, dst, pos, V, &count);
    printf("%d\n", count);
    count = 0;
    for (int i = 0; i < V; ++i) {
        pos[i] = false;
        prev[i] = -1;
    }
    printf("Обход в глубину\n");
    dfs(g, pos, src, prev, V);
    printf("\n");
    for (int i = 0; i < V; ++i) {
        pos[i] = false;
        prev[i] = -1;
    }
    printf("Обход в ширину\n");
    bfs(g, src, pos, prev, V);
    printf("\n");
    free(D);
    free(pos);
    free(prev);
    // for (int i = 0; i < V; ++i) {
    //     free(g[i]);
    // }
    // free(g);
    return 0;
}