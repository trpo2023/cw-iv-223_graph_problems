#pragma once
#include <stdbool.h>

struct node {
        int lp_len;
        int lp_count;
};

void NodeInit(struct node* new_node, int is_s);
int** AdjMatrixInit(int N);
void AdjMatrixFree(int N, int** adj_matrix);
int LongestPath(int N, int M, int** adj_matrix);

void Bfs(int** g, int v, bool* pos, int* prev, int V);
void Dfs(int** g, bool* pos, int start, int* prev, int V);
void NumberOfPaths(int** g, int src, int dst, bool* pos, int V, int* count, int* prev);
int PriorityQueueExtractMin(int* D, bool* pos, int V);
void ShortestPathDijkstra(int** g, int src, int* D, bool* pos, int* prev, int V);
void Print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V);

