#include <libgraph/graph.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_MAX 1000000000

void MyFlush(void)
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int main()
{
    // srand(time(NULL));
    int ch, P;
    int src, dst, K, V, R, N, M;
    int count = 0;
    do {
        printf("Введите количество вершин : ");
        K = scanf("%d", &V);
        MyFlush();
    } while (K != 1 || K <= 0);
    int* D = malloc(sizeof(int) * V);
    bool* pos = malloc(sizeof(bool) * V);
    int* prev = malloc(sizeof(int) * V);
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
            int qq = 1 + rand() % 100;
            if (i != j && qq % 7 != 0 && qq % 5 != 0) {
                g[i][j] = qq;
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (g[i][j] == INT_MAX) {
                printf("0 ");
                continue;
            }
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }

    do {
        printf("Что бы вы хотели найти, введите соответствующий символ:\n");
        printf("1. Количество путей между вершинами:\n");
        printf("2. Кротчайший путь между вершинами: \n");
        printf("3. Длиннейший путь между вершинами: \n");
        printf("4. Выход:\n");
        printf("Ваш выбор: ");
        P = scanf("%d", &ch);
        switch (ch) {
        case 1:
            do {
                printf("Введите начальную вершину = ");
                N = scanf("%d", &src);
                MyFlush();
            } while (N != 1);
            src--;

            do {
                printf("Введите конечнню вершину = ");
                M = scanf("%d", &dst);
                MyFlush();
            } while (M != 1);
            dst--;
            int a = 0, b = 1;
            NumberOfPaths(g, src, dst, pos, V, &count, a, prev, &b);
            printf("Количество путей из %d в %d : %d\n",
                   src + 1,
                   dst + 1,
                   count);
            break;
        case 2:
            do {
                printf("Введите начальную вершину = ");
                N = scanf("%d", &src);
                MyFlush();
            } while (N != 1);
            src--;

            do {
                printf("Введите конечнню вершину = ");
                M = scanf("%d", &dst);
                MyFlush();
            } while (M != 1);
            dst--;
            Print(g, D, src, prev, dst, pos, V);
            break;
        case 3:
            do {
                printf("Введите количество ребер : ");
                K = scanf("%d", &R);
                MyFlush();
            } while (K != 1 || K <= 0);

            int** adj_matrix = AdjMatrixInit(V);
            for (int i = 0; i < R; i++) {
                printf("Введите начальную вершину, конечную и длину пути "
                       "(например: 1 "
                       "4 10): ");
                int l;
                scanf("%d %d %d", &src, &dst, &l);
                adj_matrix[src - 1][dst - 1] = l;
            }
            printf("Длиннейший путь: %d\n", LongestPath(V, R, adj_matrix));
            break;
        case 4:
            break;
        default:
            printf("Некорректный символ, попробуйте ещё раз.\n");
        }
        MyFlush();
    } while (P != 1);
    free(D);
    free(pos);
    free(prev);
    for (int i = 0; i < V; ++i) {
        free(g[i]);
    }
    free(g);
}