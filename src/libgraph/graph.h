#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int lp_len;
    int lp_count;
};

void NumberOfPaths(
        int** g,
        int src,
        int dst,
        bool* pos,
        int V,
        int* count,
        int a,
        int* prev,
        int* b);
int PriorityQueueExtractMin(int* D, bool* pos, int V);
void ShortestPathDijkstra(
        int** g, int src, int* D, bool* pos, int* prev, int V);
void Print(int** g, int* D, int src, int* prev, int dst, bool* pos, int V);
int** AdjMatrixInit(int N);
void NodeInit(struct node* new_node, int is_s);
void AdjMatrixFree(int N, int** adj_matrix);
int LongestPath(int N, int M, int** adj_matrix);