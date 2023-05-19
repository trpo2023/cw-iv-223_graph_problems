#include <libgraph/graph.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_MAX 1000000000
#define MAX_V 99
#define NAME_SIZE 111
int V;

void my_flush(void)
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int main()
{
    srand(time(NULL));
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
                g[i][j] = 1 + rand() % 100;
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
    int P, count = 0;
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
            Number_of_paths(g, src, dst, pos, V, &count);
            printf("\nКоличество путей из %d в %d : %d\n",
                   src + 1,
                   dst + 1,
                   count);
            break;
        case 2:
            print(g, D, src, prev, dst, pos, V);
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
}