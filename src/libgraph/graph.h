#pragma once
#include <stdbool.h>

void bfs(int** g, int v, bool* pos, int* prev, int V);
void dfs(int** g, bool* pos, int start, int* prev, int V);
void Number_of_paths(
        int** g, int src, int dst, bool* pos, int V, int* count, int* prev);
int PriorityQueueExtractMin(int* D, bool* pos, int V);
void ShortestPathDijkstra(
        int** g, int src, int* D, bool* pos, int* prev, int V);
void print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V);
