#include <ctest.h>
#include <libgraph/graph.h>
#include <stdlib.h>

CTEST(graph, NumberOfPaths)
{
    int src = 0, dst = 3, V = 4;
    int** g = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; ++i) {
        g[i] = malloc(sizeof(int) * V);
    }
    g[0][0] = 0;
    g[0][1] = 2;
    g[0][2] = 15;
    g[0][3] = 7;
    g[1][0] = 2;
    g[1][1] = 0;
    g[1][2] = 10;
    g[1][3] = 8;
    g[2][0] = 15;
    g[2][1] = 10;
    g[2][2] = 0;
    g[2][3] = 1;
    g[3][0] = 7;
    g[3][1] = 8;
    g[3][2] = 1;
    g[3][3] = 0;
    int count = 0;
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    NumberOfPaths(g, src, dst, pos, V, &count);
    int expected = 5;
    ASSERT_EQUAL(expected, count);
    free(D);
    free(pos);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);
}

CTEST(graph, ShortestPathDijkstra)
{
    int src = 0, dst = 2, V = 4;
    int** g = malloc(sizeof(int*) * V);
    for (int i = 0; i < V; ++i) {
        g[i] = malloc(sizeof(int) * V);
    }
    g[0][0] = 0;
    g[0][1] = 2;
    g[0][2] = 15;
    g[0][3] = 7;
    g[1][0] = 2;
    g[1][1] = 0;
    g[1][2] = 10;
    g[1][3] = 8;
    g[2][0] = 15;
    g[2][1] = 10;
    g[2][2] = 0;
    g[2][3] = 1;
    g[3][0] = 7;
    g[3][1] = 8;
    g[3][2] = 1;
    g[3][3] = 0;
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
    ShortestPathDijkstra(g, src, D, pos, prev, V);
    int expected = 8;
    ASSERT_EQUAL(expected, D[dst]);
    free(D);
    free(pos);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);
}

CTEST(graph, PriorityQueueExtractMin)
{
    int V = 4;
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    D[0] = 0;
    D[1] = 12;
    D[2] = 14;
    D[3] = 16;
    pos[0] = true;
    pos[1] = true;
    pos[2] = true;
    pos[3] = false;
    int result = PriorityQueueExtractMin(D, pos, V);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
    free(D);
    free(pos);
}